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
		void start(int numThreads);//设置线程数，创建numThreads个线程  
		void stop();//线程池结束  
		void run(const Task& f);//任务f在线程池中运行  
		void setMaxQueueSize(int maxSize) { _maxQueueSize = maxSize; }//设置任务队列可存放最大任务数  
		static ThreadPool* getInstance();
	private:
		bool isFull();//任务队列是否已满  
		void runInThread();//线程池中每个thread执行的function  
		Task take();//从任务队列中取出一个任务  

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
