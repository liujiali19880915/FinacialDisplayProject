#ifndef _USERINPUT_H_
#define _USERINPUT_H_

#include<iostream>
#include<string>
#include<vector>

#include"ThreadPool.h"
#include"HttpBoost.h"

using namespace std;

class UserInput
{
public:
	UserInput();
	~UserInput();
	void getUserInput(void);
	bool CheckQueryFormat();
	void stringSplit(const std::string& s, std::vector<std::string>& v, const std::string& c);
	string getQueryString();
	void getUserInputRun();

private:
	ThreadPool *threadPool;
	
	string queryStr;
	vector<string> queryVector;
	string splitStr = ",";
	string queryHead_ = "http://quotes.money.163.com/service/chddata.html?";
	string queryCode = "code=";
	string startDate = "&start=";
	string endDate = "&end=";
	string queryTail = "&fields=TCLOSE;HIGH;LOW;TOPEN;LCLOSE;CHG;PCHG;VOTURNOVER;VATURNOVER";
};




#endif


