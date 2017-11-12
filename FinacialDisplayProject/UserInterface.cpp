#include "UserInterface.h"

using namespace std;
UserInterface::UserInterface() {
	sharedData = SharedData::getInstance();
	threadPool = ThreadPool::getInstance();

}
UserInterface::~UserInterface() {

}
void UserInterface::startThread() {

}
void UserInterface::refreshData() {

}
string UserInterface::getQueryPathFromUser(string queryStr) {
	return NULL;
}
string UserInterface::getQueryPathForAllData() {
	return NULL;
}
void UserInterface::run(){
	//启动主线程，一直在控制台等待用户输入，若有用户输入，处理用户的输入请求
	userInput.getUserInputRun();

	//启动一个线程，显示当日大盘信息 为了简化，目前只显示股票信息
	

	

}


void  UserInterface::handleUserQueryTask(std::vector<std::string>& v){
	
}

//bind 必须绑定的是实例的方法，不能直接是类的方法
void  UserInterface::handleUserInputTask() {
	//auto task = bind(&userInput.getUserInput,void());
	//threadPool->run(task);
}
