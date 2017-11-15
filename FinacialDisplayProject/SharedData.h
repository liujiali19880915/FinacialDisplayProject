/* 共享的数据，支持读写操作，需要保护读写数据的安全*/

#ifndef _SHAREDDATA_H_
#define _SHAREDDATE_H_

#include<mutex>
#include<string>
using namespace std;


class SharedData{
public:
	string sharedData;
	string quereDataResult;
	void writeData(string s,int type);
	string readData();
	void displayData(string s);
	static SharedData* getInstance();
	void displayData(int type);
	string& analyzeData( std::string& s);
	string&  replace_all(string&   str, const   string&   old_value, const   string&   new_value);
	string&  replace_all_distinct(string&   str, const   string&   old_value, const   string&   new_value);
	string  stringSplit(const std::string& s, const std::string& c);
private:
	mutex sharedDataMutex;
	mutex isCout;
	static SharedData* uniqueInstance;
	SharedData(string s);
	SharedData();
	~SharedData();
};


#endif // !_SHAREDDATA_H_

