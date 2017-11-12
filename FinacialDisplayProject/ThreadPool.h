#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <thread>  
#include <mutex>  
#include <functional>  
#include <string>  
#include <condition_variable>  
#include <deque>  
#include <vector>  
#include <memory>  

#include "nocopyable.h"  

class ThreadPool :public nocopyable
	{
	public:
		typedef std::function<void()> Task;
		void start(int numThreads);//�����߳���������numThreads���߳�  
		void stop();//�̳߳ؽ���  
		void run(const Task& f);//����f���̳߳�������  
		void setMaxQueueSize(int maxSize) { _maxQueueSize = maxSize; }//����������пɴ�����������  
		static ThreadPool* getInstance();
	private:
		bool isFull();//��������Ƿ�����  
		void runInThread();//�̳߳���ÿ��threadִ�е�function  
		Task take();//�����������ȡ��һ������  

		std::mutex _mutex;
		std::condition_variable _notEmpty;
		std::condition_variable _notFull;
		std::string _name;
		std::vector<std::thread> _threads;
		std::deque<Task> _queue;
		size_t _maxQueueSize;
		bool _running;
		static ThreadPool* uniqueInstance;
		explicit ThreadPool(const std::string &name = std::string());
		~ThreadPool();
	};
#endif 
