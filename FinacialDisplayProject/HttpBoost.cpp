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
		//解析URL
		std::string server, port, path;
		parseURL(url, server, port, path);
		std::ostream request_stream(&request_);

		//合成请求
	//	func(server, path, request_stream);

		//解析服务地址\端口
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

//解析
void HttpBoost::handle_resolve(const boost::system::error_code& err,
	boost::asio::ip::tcp::resolver::iterator endpointer_iterator){
	if (err) {
		std::cout << "Error: " << err << endl;
		return;
	}
	//尝试连接
	boost::asio::async_connect(
		socket_, 
		endpointer_iterator,
		boost::bind( &HttpBoost::handle_connect,this,boost::asio::placeholders::error));
}
	//连接
void HttpBoost::handle_connect(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << endl;
		return;
	}
	boost::asio::async_write(socket_, request_,
		boost::bind(&HttpBoost::handle_connect, this, boost::asio::placeholders::error));

}
	//发送请求
void HttpBoost::handle_write_request(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << endl;
		return;
	}
	//异步持续读取数据到response,直到接收协议符号 \r\n
	boost::asio::async_read_until(socket_, response_, "\r\n",
		boost::bind(&HttpBoost::handle_read_status_line, this, boost::asio::placeholders::error));

}
	//获取响应
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

	//检查是否正确返回
	if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
		std::cout << "错误的响应数据\n";
		return;

	}
	if (status_code != 200) {
		std::cout << "服务器响应的状态码"<<status_code<<endl;

	}
	//读取响应头，直到接收到协议符号为止\r\n\r\n
	boost::asio::async_read_until(socket_, response_, "\r\n\r\n",
		boost::bind(&HttpBoost::handle_read_head, this, boost::asio::placeholders::error));

}

	//获取响应头
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
	//写完所有内容
	if (response_.size() > 0) {
		boost::asio::streambuf::const_buffers_type cbt = response_.data();
		responseData_ += std::string(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
		std::cout << &responseData_;

	}

	//读取所有内容
	boost::asio::async_read(socket_, response_, boost::asio::transfer_at_least(1),
		boost::bind(&HttpBoost::handle_read_content, this, boost::asio::placeholders::error));

}

	//获取数据
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
		std::cout << "读取数据完毕!" << endl;
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








