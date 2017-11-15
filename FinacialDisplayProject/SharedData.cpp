#include "SharedData.h"
#include"UserInput.h"

#include <iostream>
#include <stdio.h>  
#include<vector>

using namespace std;
SharedData::SharedData(string s): sharedData(s) {

}
SharedData::SharedData() {
	sharedData = "";
	
}
SharedData::~SharedData() {
	sharedData = "";
	if (uniqueInstance == NULL) {
		return;

	}
	delete uniqueInstance;
	uniqueInstance = 0;
}
void SharedData::writeData(string s,int type) {
	sharedDataMutex.lock();
	sharedData.clear();
	if (type == 1) {
		sharedData = s;
	}
	else {
		quereDataResult = s;
	}
	sharedDataMutex.unlock();
	displayData(type);

}


string  SharedData::stringSplit(const std::string& s,  const std::string& c) {
	std::vector<std::string> v;
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));

	string str = v.at(0) +"   "+ v.at(1) +"   "+ v.at(2) + "   " + v.at(3) + "   " + v.at(4)+ "   " +
				 v.at(5) + "   "+ v.at(6) + "   " + v.at(9) + "   " + v.at(10)  + "   " + v.at(31) + "   " + v.at(32);
	return str;
}

string&  SharedData::analyzeData( std::string& s) {
	string s1 = replace_all(s, "var hq_str_", "");
	string s2 = replace_all(s1, "=", ",");
	string s3 = replace_all(s2, "\"", "");
	string s4 = replace_all(s3, "\r", "");
	s = replace_all(s4, "\n", "");
	//按照 ，进行分割接的，选择需要显示的数据
//	cout << s << endl;
	std::vector<std::string> v;
//	stringSplit(s, v, '\\n');
	int pos1 = 0;
	int pos2 = s.find(";", pos1);
	string resultStr = "";
	while (std::string::npos != pos2)
	{
		string str = s.substr(pos1, pos2);
		resultStr += stringSplit(str, ",");
		resultStr += "\n";

		pos1 = pos2 + 1;
		pos2 = s.find(";", pos1);
	}
	if (pos1 != s.length()) {
		resultStr += stringSplit(s, ",");
		resultStr += "\n";
	}	
	s = resultStr;
	return s;
}
string SharedData::readData() {
	return sharedData;
}

void SharedData::displayData(string str) {
	sharedDataMutex.lock();
	isCout.lock();
	cout << str << endl;
	isCout.unlock();
	sharedDataMutex.unlock();
}
void SharedData::displayData(int type) {
	sharedDataMutex.lock();
	isCout.lock();
	if (type == 1) {
		if (sharedData.length() != 0) {
			sharedData = analyzeData(sharedData);
			cout << "股票编号    股票名称    开盘价    昨日收盘价    当前价    今日最高价    今日最低价    成交股票数    成交金额    日期    时间 " << endl;
			cout << sharedData << endl;
		}
	}
	else {
		if (quereDataResult.length() != 0)
		cout << quereDataResult << endl;
	}
	isCout.unlock();
	sharedDataMutex.unlock();
	if (type == 1) {
		UserInput userInput;
		userInput.getUserInputRun();
	}

}
SharedData* SharedData::uniqueInstance = NULL;

SharedData* SharedData::getInstance() {
	if (uniqueInstance == NULL) {
		uniqueInstance = new SharedData;
		return uniqueInstance;
	}
	return uniqueInstance;

}

string&  SharedData::replace_all(string&   str, const   string&   old_value, const   string&   new_value)
{
	while (true) {
		string::size_type   pos(0);
		if ((pos = str.find(old_value)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}
string&   SharedData::replace_all_distinct(string&   str, const   string&   old_value, const   string&   new_value)
{
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
		if ((pos = str.find(old_value, pos)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}
