#include "UserInterface.h"
#include<boost\thread\thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
UserInterface::UserInterface() {

	threadPool = ThreadPool::getInstance();

}
UserInterface::~UserInterface() {

}


string getQueryPathForAllData() {

	string queryPath_ = "http://hq.sinajs.cn/list=sh000001,sh000002,sh000003,sh000004,sh000005,sh000006,sh000007,sh000008,sh000009,sh000010,sh000011,sh000012,sh000013,sh000015,sh000016,sh000017,sh000018,sh000019,sh000020,sh000021,sh000022,sh000028,sh000029,sh000031,sh000032,sh000033";
	return queryPath_;

}

void handleRefreshData(string url) {
	try {
		
			boost::asio::io_service io;
			HttpBoost c(io);
			boost::asio::io_service::work work(io);
			c.setQueryType(1);
			c.get(url);
			io.run();
	}
	catch (exception& e) {
		cerr << e.what() << endl;

	}

}
void RefreshData(const boost::system::error_code&) {

		auto task = bind(handleRefreshData, getQueryPathForAllData());
		ThreadPool *threadPool = ThreadPool::getInstance();
		threadPool->run(task);

		boost::asio::io_service io;
		boost::asio::io_service::work work(io);
		boost::asio::deadline_timer timer(io, boost::posix_time::seconds(30));
		timer.async_wait(RefreshData);
		io.run();
		
	
}
void UserInterface::run() {
	//启动主线程，一直在控制台等待用户输入，若有用户输入，处理用户的输入请求
	
	cout << "数据加载中，请稍候..................." << endl;
	while (true) {	
		boost::asio::io_service io;
		boost::asio::io_service::work work(io);
		boost::asio::deadline_timer timer(io, boost::posix_time::seconds(3));
		timer.async_wait(RefreshData);
		io.run();
	}	
}
