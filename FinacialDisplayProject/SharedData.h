/* ��������ݣ�֧�ֶ�д��������Ҫ������д���ݵİ�ȫ*/

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

