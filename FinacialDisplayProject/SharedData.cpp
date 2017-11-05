#include "SharedData.h"
#include <iostream>
SharedData::SharedData(string s): sharedData(s) {

}
SharedData::~SharedData() {
	sharedData = "";
}
void SharedData::writeData(string s) {
	sharedDataMutex.lock();
	sharedData = s;
	sharedDataMutex.unlock();

}
string SharedData::readData() {
	return sharedData;
}

void SharedData::displayData() {
	sharedDataMutex.lock();
	cout << sharedData << endl;
	sharedDataMutex.unlock();
}
