/* 共享的数据，支持读写操作，需要保护读写数据的安全*/

#ifndef _SHAREDDATA_H_
#define _SHAREDDATE_H_

#include<mutex>
#include<string>
using namespace std;

class SharedData{
public:
	string sharedData;
	void writeData(string s);
	string readData();
	void displayData(string s);
	static SharedData* getInstance();
	void displayData();
private:
	mutex sharedDataMutex;
	static SharedData* uniqueInstance;
	SharedData(string s);
	SharedData();
	~SharedData();
};


#endif // !_SHAREDDATA_H_

