#include <iostream>
#include"HttpBoost.h"




void main() {

	
	std::string str = "http://service.winic.org:8009/sys_port/gateway/[id=13695800360&pwd=13645411460&to=13695800360&content=infomation&time=]";
	str = post(str);
	std::cout << str.c_str() << std::endl;



}