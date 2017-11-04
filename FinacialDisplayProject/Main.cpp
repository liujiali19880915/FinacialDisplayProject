#include <iostream>
#include"HttpBoost.h"




void main() {

	
	std::string str = "http://hq.sinajs.cn/list=sh204001";
 	str = get(str);
	std::cout << str.c_str() << std::endl;



}