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
	//�������̣߳�һֱ�ڿ���̨�ȴ��û����룬�����û����룬�����û�����������
	userInput.getUserInputRun();

	//����һ���̣߳���ʾ���մ�����Ϣ Ϊ�˼򻯣�Ŀǰֻ��ʾ��Ʊ��Ϣ
	

	

}


void  UserInterface::handleUserQueryTask(std::vector<std::string>& v){
	
}

//bind ����󶨵���ʵ���ķ���������ֱ������ķ���
void  UserInterface::handleUserInputTask() {
	//auto task = bind(&userInput.getUserInput,void());
	//threadPool->run(task);
}
