#include"HttpBoost.h"
#include"HttpErrorInfo.h"
#include<boost/bind.hpp>

HttpBoost::HttpBoost(boost::asio::io_service& io_service):
resolver_(io_service),socket_(io_service){

}

HttpBoost::~HttpBoost() {

}
int HttpBoost::post(const std::string& url) {
	handle_request_resolve(url, HttpBase::buildPostRequest);
	return HTTP_SUCCESS;

}
int  HttpBoost::get(const std::string& url) {
	handle_request_resolve(url, HttpBase::buildGetRequest);
	return HTTP_SUCCESS;

}


void  HttpBoost::handle_request_resolve(const std::string& url, pBuildRequest fun) {

	try {
		responseData_.clear();
		//����URL
		std::string server, port, path;
		parseURL(url, server, port, path);
		std::ostream request_stream(&request_);

		//�ϳ�����
	//	func(server, path, request_stream);

		//���������ַ\�˿�
		boost::asio::ip::tcp::resolver::query query_(server, port);
		resolver_.async_resolve(
				query_,
				boost::bind(&HttpBoost::handle_resolve,
				this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::iterator));
	}
	catch(std::exception& e){
		socket_.close();
		std::cout << "Exception: " << e.what() << endl;
	}
	return;
}

//����
void HttpBoost::handle_resolve(const boost::system::error_code& err,
	boost::asio::ip::tcp::resolver::iterator endpointer_iterator){
	if (err) {
		std::cout << "Error: " << err << endl;
		return;
	}
	//��������
	boost::asio::async_connect(
		socket_, 
		endpointer_iterator,
		boost::bind( &HttpBoost::handle_connect,this,boost::asio::placeholders::error));
}
	//����
void HttpBoost::handle_connect(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << endl;
		return;
	}
	boost::asio::async_write(socket_, request_,
		boost::bind(&HttpBoost::handle_connect, this, boost::asio::placeholders::error));

}
	//��������
void HttpBoost::handle_write_request(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << endl;
		return;
	}
	//�첽������ȡ���ݵ�response,ֱ������Э����� \r\n
	boost::asio::async_read_until(socket_, response_, "\r\n",
		boost::bind(&HttpBoost::handle_read_status_line, this, boost::asio::placeholders::error));

}
	//��ȡ��Ӧ
void HttpBoost::handle_read_status_line(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << endl;
		return;
	}

	std::istream response_stream(&response_);
	unsigned int status_code;
	std::string http_version, status_message;
	response_stream >> http_version;
	response_stream >> status_code;
	std::getline(response_stream, status_message);

	//����Ƿ���ȷ����
	if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
		std::cout << "�������Ӧ����\n";
		return;

	}
	if (status_code != 200) {
		std::cout << "��������Ӧ��״̬��"<<status_code<<endl;

	}
	//��ȡ��Ӧͷ��ֱ�����յ�Э�����Ϊֹ\r\n\r\n
	boost::asio::async_read_until(socket_, response_, "\r\n\r\n",
		boost::bind(&HttpBoost::handle_read_head, this, boost::asio::placeholders::error));

}

	//��ȡ��Ӧͷ
void HttpBoost::handle_read_head(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << endl;
		return;
	}
	std::istream response_stream(&response_);
	std::string header;
	while (std::getline(response_stream, header) && header != "\r") {
		std::cout << header << "\n";
	}
	cout << endl;
	//д����������
	if (response_.size() > 0) {
		boost::asio::streambuf::const_buffers_type cbt = response_.data();
		responseData_ += std::string(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
		std::cout << &responseData_;

	}

	//��ȡ��������
	boost::asio::async_read(socket_, response_, boost::asio::transfer_at_least(1),
		boost::bind(&HttpBoost::handle_read_content, this, boost::asio::placeholders::error));

}

	//��ȡ����
void HttpBoost::handle_read_content(const boost::system::error_code& err) {

	if (!err) {
		boost::asio::streambuf::const_buffers_type cbt = response_.data();
		responseData_ += std::string(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
		cout << &response_;
			 
		boost::asio::async_read(socket_, response_, boost::bind(&HttpBoost::handle_read_content, this, boost::asio::placeholders::error));
	}
	else if (err != boost::asio::error::eof) {
		std::cout << "error: " << err << endl;

	}
	else {
		socket_.close();
		resolver_.cancel();
		std::cout << "��ȡ�������!" << endl;
	}

}


std::string post(std::string url) {
	boost::asio::io_service io;
	HttpBoost c(io);
	c.post(url);
	io.run();
	return c.getResponse();
}

std::string get(std::string url) {
	boost::asio::io_service io;
	HttpBoost c(io);
	c.get(url);
	io.run();
	return c.getResponse();
}








