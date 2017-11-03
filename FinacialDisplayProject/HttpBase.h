/* 利用boost发送http 的Post和Get请求*/

#ifndef _HTTPBASE_H_
#define _HTTPBASE_H_


#include<iostream>
using namespace std;

class HttpBase {
public:
	HttpBase();
	virtual ~HttpBase();

	//发送post 请求
	virtual int post(const std::string& url) = 0;

	//发送get请求
	virtual int get(const std::string& url) = 0;
	virtual std::string getResponse(void) = 0;

protected:
	typedef int(*pBuildRequest)(const std::string&, const std::string&, std::ostream&);

	/*解析URL
	parseURL
	url：		 待解析的url   
	out_server： 服务器名  
	out_port：	 端口号 
	out_path：	 服务器子页
	*/
	static int parseURL(const std::string& url, std::string& out_server,
		 std::string& out_port,  std::string& out_path);


	//建立 post 请求
	static int buildPostRequest(const std::string& server,
		const std::string& path,
		 std::ostream& out_request);

	//建立 get 请求
	static int buildGetRequest(const std::string& server,
		const std::string& path,
		 std::ostream& out_request);
};



#endif // !_HTTPBASE_H_
