#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include<boost/thread.hpp>
#include<mutex>
#include<condition_variable>
#include<list>
#include<vector>
#include<memory>
#include<functional>
using namespace std;
class ThreadPool {

public:
	
	typedef  std::function<void(void)> Task;
	ThreadPool(int threadNumber);
	~ThreadPool();

	//add task into list
	bool append(Task task);

	//start thread pool
	bool start(void);

	//sto thread pool
	bool stop(void);
private:
	mutex mutex_;  //互斥锁
	condition_variable_any condition_empty_;  //当任务队列为空时的条件变量
	list<Task> tasks_; //任务队列
	bool running_;  //线程池是否在运行
	int threadNum_; //线程数
	vector<shared_ptr<thread>> threads_;  //用来保存线程对象指针。
											  
	void threadWork(void); //线程执行的工作函数







};









#endif // !_THREADPOOL_H_
