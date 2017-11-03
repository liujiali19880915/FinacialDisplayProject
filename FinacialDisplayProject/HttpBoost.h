#ifndef _HTTPBOOST_H_
#define _HTTPBOOST_H_

#include "HttpBase.h"
#include<boost/asio.hpp>


class HttpBoost: public HttpBase {
private:
	boost::asio::ip::tcp::resolver resolver_;	//������
	boost::asio::ip::tcp::socket socket_;		//�׽���
	boost::asio::streambuf request_;			//���󻺴���
	boost::asio::streambuf response_;			//��ȡ������
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
	//��������
	void handle_request_resolve(const std::string& url, pBuildRequest fun);
	//����
	void handle_resolve(const boost::system::error_code& err,
		boost::asio::ip::tcp::resolver::iterator endpointer_iterator);
	//����
	void handle_connect(const boost::system::error_code& err);
	//��������
	void handle_write_request(const boost::system::error_code& err);
	//��ȡ��Ӧ
	void handle_read_status_line(const boost::system::error_code& err);

	//��ȡ��Ӧͷ
	void handle_read_head(const boost::system::error_code& err);

	//��ȡ����
	void handle_read_content(const boost::system::error_code& err);
};

std::string post(std::string url);
std::string get(std::string url);

#endif // !1