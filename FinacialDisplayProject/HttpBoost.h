#ifndef _HTTPBOOST_H_
#define _HTTPBOOST_H_

#include "HttpBase.h"
#include<boost/asio.hpp>


class HttpBoost: public HttpBase {
private:
	boost::asio::ip::tcp::resolver resolver_;	//解析器
	boost::asio::ip::tcp::socket socket_;		//套接字
	boost::asio::streambuf request_;			//请求缓存区
	boost::asio::streambuf response_;			//读取缓存区
	std::string responseData_;
public:
	HttpBoost(boost::asio::io_service& io_service);
	virtual ~HttpBoost();
	virtual int post(const std::string& url);
	virtual int get(const std::string& url);
	virtual std::string getResponse(void) {
		return responseData_;
	}
private:
	//建立请求
	void handle_request_resolve(const std::string& url, pBuildRequest fun);
	//解析
	void handle_resolve(const boost::system::error_code& err,
		boost::asio::ip::tcp::resolver::iterator endpointer_iterator);
	//连接
	void handle_connect(const boost::system::error_code& err);
	//发送请求
	void handle_write_request(const boost::system::error_code& err);
	//获取响应
	void handle_read_status_line(const boost::system::error_code& err);

	//获取响应头
	void handle_read_head(const boost::system::error_code& err);

	//获取数据
	void handle_read_content(const boost::system::error_code& err);
};

std::string post(std::string url);
std::string get(std::string url);

#endif // !1