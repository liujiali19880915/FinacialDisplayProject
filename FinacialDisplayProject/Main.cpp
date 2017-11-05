#include <iostream>
#include"HttpBoost.h"
#include"ThreadPool.h"

void fun(string s) {
	cout << s << endl;
}

void main() {

	//test data get

	/*
	std::string str = "http://quotes.money.163.com/service/chddata.html?code=0000001&start=20171001&end=20171031&fields=TCLOSE;HIGH;LOW;TOPEN;LCLOSE;CHG;PCHG;VOTURNOVER;VATURNOVER";
 	str = get(str);
	std::cout << str.c_str() << std::endl;
	*/

	//test thread pool
	ThreadPool threadPool(5);
	threadPool.start();
	int task = 10;
	while (task) {
		threadPool.append(bind(fun, string("hello world")));
		task--;
	}
}