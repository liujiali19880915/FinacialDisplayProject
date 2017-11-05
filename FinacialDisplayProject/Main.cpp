#include <iostream>
#include"HttpBoost.h"
#include"ThreadPool.h"
#include<mutex>
using namespace std;


mutex mutex_;

void func(string s) {
	mutex_.lock();
	cout << s << endl;
	mutex_.unlock();
}
void Test(int i)
{
//	printf("I love you %d time\n", i);
	mutex_.lock();
	cout << "I love you" << i << " time" << endl;
	mutex_.unlock();
}


void main() {

	/*test read data
	std::string str = "http://quotes.money.163.com/service/chddata.html?code=0000001&start=20171001&end=20171031&fields=TCLOSE;HIGH;LOW;TOPEN;LCLOSE;CHG;PCHG;VOTURNOVER;VATURNOVER";
 	str = get(str);
	std::cout << str.c_str() << std::endl;*/

	//test thread pool
	ThreadPool threadPool;
	threadPool.setMaxQueueSize(10);
	threadPool.start(2);
	string s = "hello, world!";
	for (int i = 0; i < 10; ++i)
	{
		auto task = bind(func, s);
		threadPool.run(task);
	}

	getchar();

}