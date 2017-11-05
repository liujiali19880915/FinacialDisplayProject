#include <iostream>
#include"HttpBoost.h"




void main() {

	
	std::string str = "http://quotes.money.163.com/service/chddata.html?code=0000001&start=20171001&end=20171031&fields=TCLOSE;HIGH;LOW;TOPEN;LCLOSE;CHG;PCHG;VOTURNOVER;VATURNOVER";
 	str = get(str);
	std::cout << str.c_str() << std::endl;



}