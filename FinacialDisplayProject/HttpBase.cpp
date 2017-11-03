#include "HttpBase.h"
#include "HttpErrorInfo.h"
#include<string>
#include<iostream>
using namespace std;

#define HTTP_JSON_BEGIN ("[")  
#define HTTP_JSON_END ("]")  

HttpBase::HttpBase() {

}

HttpBase::~HttpBase() {

}

//可以解析下列三种类型的URL:  
//http://yunhq.sse.com.cn:32041/v1/sh1/snap/204001?callback=jQuery_test&select=name%2Clast%2Cchg_rate%2Cchange%2Camount%2Cvolume%2Copen%2Cprev_close%2Cask%2Cbid%2Chigh%2Clow%2Ctradephase  
//http://hq.sinajs.cn/list=sh204001  
//https://www.baidu.com  
//
int HttpBase::parseURL(const std::string& url, std::string& out_server,
	 std::string& out_port,  std::string& out_path) {
	const std::string& http_ = "http://";
	const std::string& https_ = "https://";
	std::string temp_data = url;

	//截断 http协议头
	if (temp_data.find(http_) == 0) {
		temp_data = temp_data.substr(http_.length());
	}
	else if (temp_data.find(https_) == 0) {
		temp_data = temp_data.substr(https_.length());
	}
	else {
		return HTTP_ERROR_HEETP_HEAD;
	}

	//解析域名
	std::size_t idx = temp_data.find('/');
	//解析域名后的page
	if (std::string::npos == idx) {
		
		out_path = "/";;
		idx = temp_data.size();
	}
	else {
		out_path = temp_data.substr(idx);
	}
	//解析域名
	out_server = temp_data.substr(0, idx);

	//解析端口
	idx = out_server.find(':');
	if (std::string::npos == idx) {
		out_port = "80";
	}
	else {
		out_port = out_server.substr(idx + 1);
		out_server = out_server.substr(0, idx);
	}

	return HTTP_SUCCESS;

}

//建立 post请求
int HttpBase::buildPostRequest(const std::string& server,
	const std::string& path,
	 std::ostream& out_request) {

	//分割path的json数据
	std::string temp_path(path), temp_json;
	int json_pos_begin = temp_path.find(HTTP_JSON_BEGIN) + 1;
	int json_pos_end = temp_path.find(HTTP_JSON_END);
	if (json_pos_begin != std::string::npos) {
		//计算json的长度
		int temp_json_length = std::string::npos;
		if (json_pos_end != temp_json_length) {
			temp_json_length = json_pos_end - json_pos_begin;
		}
		temp_json = temp_path.substr(json_pos_begin, temp_json_length);
		temp_path = temp_path.substr(0, json_pos_begin - 1);
		
	}
	out_request << "POST " << temp_path.c_str() << "HTTP/1.0\r\n";
	out_request << "Host: " << server.c_str() << "\r\n";
	out_request << "Content-Length " << temp_json.length() << "\r\n";
	out_request << "Content-type: application/x-www-form-urlencoded\r\n";
	out_request << "Accept: */*\r\n";
	out_request << "COnnection: close\r\n\r\n";
	out_request << temp_json.c_str();
	return HTTP_SUCCESS;
	
}
int HttpBase::buildGetRequest(const std::string& server,
	const std::string& path,
	 std::ostream& out_request) {

	out_request << "Get " << path.c_str() << "HTTP/1.0\r\n";
	out_request << "Host: " << server.c_str() << "\r\n";
	out_request << "Accept: */*\r\n";
	out_request << "Connection: close\r\n\r\n";
	return HTTP_SUCCESS;
}