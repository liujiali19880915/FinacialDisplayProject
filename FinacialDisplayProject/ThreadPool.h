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
	mutex mutex_;  //������
	condition_variable_any condition_empty_;  //���������Ϊ��ʱ����������
	list<Task> tasks_; //�������
	bool running_;  //�̳߳��Ƿ�������
	int threadNum_; //�߳���
	vector<shared_ptr<thread>> threads_;  //���������̶߳���ָ�롣
											  
	void threadWork(void); //�߳�ִ�еĹ�������







};









#endif // !_THREADPOOL_H_
