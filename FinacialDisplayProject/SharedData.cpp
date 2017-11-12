#include "SharedData.h"
#include <iostream>
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
void SharedData::writeData(string s) {
	sharedDataMutex.lock();
	sharedData = s;
	sharedDataMutex.unlock();

}
string SharedData::readData() {
	return sharedData;
}

void SharedData::displayData(string str) {
	sharedDataMutex.lock();
	cout << str << endl;
	sharedDataMutex.unlock();
}
void SharedData::displayData() {
	sharedDataMutex.lock();
	cout << sharedData << endl;
	sharedDataMutex.unlock();
}
SharedData* SharedData::uniqueInstance = NULL;

SharedData* SharedData::getInstance() {
	if (uniqueInstance == NULL) {
		uniqueInstance = new SharedData;
		return uniqueInstance;
	}
	return uniqueInstance;

}

