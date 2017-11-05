/* ��������ݣ�֧�ֶ�д��������Ҫ������д���ݵİ�ȫ*/

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

