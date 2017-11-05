#include"ThreadPool.h"
#include<iostream>
using namespace std;

ThreadPool::ThreadPool(int threadNumber):
threadNum_(threadNumber),
running_(true),
threads_(threadNum_){

}
ThreadPool::~ThreadPool() {
	if (running_)
		stop();

}


//start thread pool
bool ThreadPool::start(void) {
	for (int i = 0; i < threadNum_; i++) {
		threads_.push_back(make_shared<thread>(bind(&ThreadPool::threadWork,this)));
	}
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	cout << "线程池开始工作" << endl;
	return true;


}

//add task into list
bool ThreadPool::append(Task task) {
	std::lock_guard<std::mutex> gard(mutex_);
	tasks_.push_front(task); //将任务加入队列
	condition_empty_.notify_one();//唤醒某个线程来执行此任务
	return true;
}

//stop thread pool
bool ThreadPool::stop(void) {
	if (running_) {
		running_ = false;
		for (auto t : threads_) {
			t->join();//循环等待线程终止
		}
	}
	return true;
}

void ThreadPool::threadWork(void) {
	Task task = NULL;
	while (running_) {
		std::lock_guard<std::mutex> gard(mutex_);
		if (tasks_.empty()) {
			condition_empty_.wait(mutex_); //等待有任务来被唤醒
		}
		if (!tasks_.empty()) {
			task = tasks_.front(); //获取可用任务
			tasks_.pop_front();  //弹出任务
		}
		else {
			continue;
		}

		task();  // 执行任务
	}
	

}

