#ifndef _USERINTERFACE_H_
#define _USERINTERFACE_H_

//
#include<iostream>
#include<string>
#include"ThreadPool.h"
#include"SharedData.h"
#include "HttpBoost.h"
#include "UserInput.h"
using namespace std;

class UserInterface {
private:
	string queryStr = "http://quotes.money.163.com/service/chddata.html?code=0000001&start=20171001&end=20171031&fields=TCLOSE;HIGH;LOW;TOPEN;LCLOSE;CHG;PCHG;VOTURNOVER;VATURNOVER";
	ThreadPool* threadPool;
	SharedData* sharedData;
	UserInput userInput;
public:
	UserInterface();
	~UserInterface();
	void startThread();
	void refreshData();//refreshdata every 1 minutes
	string getQueryPathFromUser(string queryStr);
	string getQueryPathForAllData();
	void run(); //
	void handleUserQueryTask(std::vector<std::string>& v);
	void  UserInterface::handleUserInputTask();


};








#endif // !_USERINTERFACE_H_
