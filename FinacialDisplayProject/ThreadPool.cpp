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
	cout << "�̳߳ؿ�ʼ����" << endl;
	return true;


}

//add task into list
bool ThreadPool::append(Task task) {
	std::lock_guard<std::mutex> gard(mutex_);
	tasks_.push_front(task); //������������
	condition_empty_.notify_one();//����ĳ���߳���ִ�д�����
	return true;
}

//stop thread pool
bool ThreadPool::stop(void) {
	if (running_) {
		running_ = false;
		for (auto t : threads_) {
			t->join();//ѭ���ȴ��߳���ֹ
		}
	}
	return true;
}

void ThreadPool::threadWork(void) {
	Task task = NULL;
	while (running_) {
		std::lock_guard<std::mutex> gard(mutex_);
		if (tasks_.empty()) {
			condition_empty_.wait(mutex_); //�ȴ���������������
		}
		if (!tasks_.empty()) {
			task = tasks_.front(); //��ȡ��������
			tasks_.pop_front();  //��������
		}
		else {
			continue;
		}

		task();  // ִ������
	}
	

}

