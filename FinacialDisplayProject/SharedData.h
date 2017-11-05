/* 共享的数据，支持读写操作，需要保护读写数据的安全*/

#ifndef _SHAREDDATA_H_
#define _SHAREDDATE_H_

#include<mutex>
#include<string>
using namespace std;

class SharedData{
public:
	string sharedData;
	SharedData(string s);
	~SharedData();
	void writeData(string s);
	string readData();
	void displayData();
private:
	mutex sharedDataMutex;
};


#endif // !_SHAREDDATA_H_

