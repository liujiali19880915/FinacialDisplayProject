#include "UserInput.h"
#include "SharedData.h"
#include<boost\thread\thread.hpp>
#include<vector>


UserInput::UserInput(){
	threadPool = ThreadPool::getInstance();

}

UserInput::~UserInput()
{
}

//主程序，等待用户输入
void UserInput::getUserInputRun() {
		getUserInput();
		cout << "test cout1" << endl;
		boost::this_thread::sleep(boost::posix_time::seconds(3));
		SharedData *shareData = SharedData::getInstance();
		shareData->displayData();
		cout << "Press 1 continue query, 0 exit" << endl;
		int choose;
		cin >> choose; //0表示退出程序
		while (1) {
			
			if (choose != 0) {
				getUserInput();
				cin >> choose;
			}
			else {
				exit(0);
			}
			
		}

}
std::string gets(std::string url) {
	try {

		boost::asio::io_service io;
		HttpBoost c(io);
		boost::asio::io_service::work work(io);
		//	std::cout << "[test_asio_work]" << "ioser before" << endl;
		c.get(url);
		io.run();
		//	std::cout << "[test_asio_work]" << "ioser after" << endl;

		std::string s = c.getResponse();
		cout << "test cout3" << endl;
		cout <<"run over" <<s.c_str() << endl;
		return s;

	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return NULL;
	}


}
//获取用户输入
void UserInput::getUserInput(void) {


	cout << "please input your interestred stock code" << endl;
	cout << "Format:   stockecode,StartDate,EndDate" << endl;
	cout << "Example:  0000001, 20171101, 20171112" << endl;
	cin >> queryStr;

	while (!CheckQueryFormat()) {
		cout << "invalid inpout, please input again" << endl;
		cin >> queryStr;
	}
	auto task = bind(gets, getQueryString());
	threadPool->run(task);

	
	
}

//检查输入格式
bool UserInput::CheckQueryFormat() {
	if (queryStr.length() == 0)
		return false;
	queryVector.clear();
	stringSplit(queryStr, queryVector, splitStr);
	if (queryVector.size() < 3)
		return false;
	return true;


}

//分割用户输入信息
void  UserInput::stringSplit(const std::string& s, std::vector<std::string>& v, const std::string& c) {
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
}

//构造查询语句
 string UserInput::getQueryString(){
	 
	 string code_ = queryVector.at(0);
	 string start_ = queryVector.at(1);
	 string end_ = queryVector.at(2);
	 string queryPath_ = queryHead_ + queryCode+code_ + startDate + start_ + endDate + end_ + queryTail;
	 cout << queryPath_ << endl;
	 return queryPath_;
}