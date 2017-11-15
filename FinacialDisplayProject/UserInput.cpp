#include "UserInput.h"

#include<boost\thread\thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include<vector>


UserInput::UserInput(){
	threadPool = ThreadPool::getInstance();
}

UserInput::~UserInput()
{
}

//主程序，等待用户输入
void UserInput::getUserInputRun() {
	
		string queryAgainStr = "Do you want to query some stock information you are interested, Yes 1, No 0";
		cout << queryAgainStr << endl;
	
		int choose;
		cin >> choose; //0表示退出程序
		if (choose == 1)
			getUserInput();
		
}


std::string gets(std::string url) {
	try {

		boost::asio::io_service io;
		HttpBoost c(io);
		boost::asio::io_service::work work(io);
		c.get(url);
		c.setQueryType(2);
		io.run();
	
		return NULL;

	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return NULL;
	}


}

//获取用户输入
void UserInput::getUserInput(void) {
	string inputFormatStr1 = "please input your interestred stock code \n";
	string inputFormatStr2 = "Format:   stockecode,StartDate,EndDate\n";
	string inputFormatStr3 = "Example: 0000001,20171101,20171102\n";
	string inputFormatStr = inputFormatStr1 + inputFormatStr2 + inputFormatStr3;
	cout << inputFormatStr ;
	cin >> queryStr;

	while (!CheckQueryFormat()) {
		cout<<"invalid inpout, please input again\n";
	
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
	 return queryPath_;
}