#include"HttpBoost.h"
#include"HttpErrorInfo.h"
#include "SharedData.h"
#include<boost/bind.hpp>

HttpBoost::HttpBoost(boost::asio::io_service& io_service):
resolver_(io_service),socket_(io_service){

}

HttpBoost::~HttpBoost() {

}
void HttpBoost::setQueryType(int type) {
	queryType = type;
}
string HttpBoost::getResponse() {
//	string s = &response_;
	return responseData_;
}

int HttpBoost::post(const std::string& url) {
	handle_request_resolve(url, HttpBase::buildPostRequest);
	return HTTP_SUCCESS;
}


int HttpBoost::get(const std::string& url) {
	handle_request_resolve(url, HttpBase::buildGetRequest);
	return HTTP_SUCCESS;
}


void HttpBoost::handle_request_resolve(const std::string& url, pBuildRequest func) {
	try {
		responseData_.clear();
		// ����URL  
		std::string server, port, path;
		parseURL(url, server, port, path);

		std::ostream request_stream(&request_);

		// �ϳ�����  
		func(server, path, request_stream);

		// ���������ַ\�˿�  
		boost::asio::ip::tcp::resolver::query query(server, port);
		resolver_.async_resolve(query,
			boost::bind(&HttpBoost::handle_resolve, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::iterator));
	}
	catch (std::exception& e) {
		socket_.close();
		std::cout << "Exception: " << e.what() << "\n";
	}
	return;
}


void HttpBoost::handle_resolve(const boost::system::error_code& err,
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
	if (err) {
		std::cout << "Error: " << err << "\n";
		return;
	}

	// ��������  
	boost::asio::async_connect(socket_, endpoint_iterator,
		boost::bind(&HttpBoost::handle_connect, this,
			boost::asio::placeholders::error));
}


void HttpBoost::handle_connect(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << "\n";
		return;
	}

	// ����request����  
	boost::asio::async_write(socket_, request_,
		boost::bind(&HttpBoost::handle_write_request, this,
			boost::asio::placeholders::error));
}


void HttpBoost::handle_write_request(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << "\n";
		return;
	}

	// �첽���������ݵ�response_��ֱ������Э����� \r\n Ϊֹ  
	boost::asio::async_read_until(socket_, response_, "\r\n",
		boost::bind(&HttpBoost::handle_read_status_line, this,
			boost::asio::placeholders::error));
}


void HttpBoost::handle_read_status_line(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << "\n";
		return;
	}

	// ����buff  
	std::istream response_stream(&response_);
	unsigned int status_code;
	std::string http_version, status_message;
	response_stream >> http_version;
	response_stream >> status_code;
	std::getline(response_stream, status_message);

	// �˶��Ƿ�����ȷ����  
	if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
		std::cout << "�������Ӧ����\n";
		return;
	}
	if (status_code != 200) {
		std::cout << "��������Ӧ��״̬��: " << status_code << "\n";
		return;
	}

	// ��ȡ��Ӧͷ,ֱ������Э����� \r\n\r\n Ϊֹ  
	boost::asio::async_read_until(socket_, response_, "\r\n\r\n",
		boost::bind(&HttpBoost::handle_read_headers, this,
			boost::asio::placeholders::error));
}


void HttpBoost::handle_read_headers(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << "\n";
		return;
	}
	// �����Ӧͷ  
	std::istream response_stream(&response_);
	std::string header;
		while (std::getline(response_stream, header) && header != "\r") {
#ifdef _DEBUG  
			;
		//std::cout << header << "\n";
#endif   
	}
#ifdef _DEBUG  
	//std::cout << "\n";
#endif   

	// д������ʣ�������  
	if (response_.size() > 0) {

		boost::asio::streambuf::const_buffers_type cbt = response_.data();
		string s = std::string(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt)).c_str();
		responseData_ += s;
#ifdef _DEBUG  
		//cout << endl;
		//std::cout << "1" << endl;
		//std::cout << s;
#endif   
	}
	response_.consume(response_.size());
	// ��ʼ��ȡʣ����������  
	boost::asio::async_read(socket_, response_,
		boost::asio::transfer_at_least(1),
		boost::bind(&HttpBoost::handle_read_content, this,
			boost::asio::placeholders::error));
}

void HttpBoost::handle_read_content(const boost::system::error_code& err) {
	if (!err) {
		// �������������  

		boost::asio::streambuf::const_buffers_type cbt = response_.data();
		responseData_ += std::string(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));

#ifdef _DEBUG  

//		cout << endl;
//		std::cout <<"1"<<endl;
//		std::cout << s;
#endif   
		response_.consume(response_.size());
		// ������ȡʣ�����ݣ�ֱ������EOF  
		boost::asio::async_read(socket_, response_,
			boost::asio::transfer_at_least(1),
			boost::bind(&HttpBoost::handle_read_content, this,
				boost::asio::placeholders::error));
	}
	else if (err != boost::asio::error::eof) {
		std::cout << "Error: " << err << "\n";
	}
	else {
		socket_.close();
		resolver_.cancel();
		SharedData *shareData = SharedData::getInstance();
		shareData->writeData(responseData_, queryType);
	
#ifdef _DEBUG
	//	std::cout << "2" << endl;
		//std::cout << "��ȡ��Ӧ�������." << std::endl;
		//cout << responseData_ << endl;
#endif
	}
}



std::string post(std::string url) {
	try {
		boost::asio::io_service io;
		HttpBoost c(io);
		c.post(url);
		io.run();
		return c.getResponse();
	}
	catch (exception& e) {
		cout << "error" << endl;
		cerr << e.what() << endl;
		return NULL;
	}
}


std::string get(std::string url) {
	try{
	
		boost::asio::io_service io;	
		HttpBoost c(io);
		boost::asio::io_service::work work(io);

		std::cout << "[test_asio_work]" << "ioser before" << endl;
		c.get(url);
		io.run();
		
		std::cout << "[test_asio_work]" << "ioser after" << endl;
		std::string s = c.getResponse();
		return s;
	
	}
	catch(exception& e){
		cerr << e.what() << endl;
		return NULL;
	}
	
	
}









