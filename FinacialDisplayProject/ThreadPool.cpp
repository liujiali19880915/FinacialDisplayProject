#include "ThreadPool.h"
#include<iostream>
#include <cassert>  

using namespace std;

ThreadPool::ThreadPool(const string &name) :
	_name(name),
	_maxQueueSize(0),
	_running(false)
{

}

ThreadPool::~ThreadPool()
{
	if (_running)
	{
		stop();
	}
}

void ThreadPool::start(int numThreads)
{
	assert(_threads.empty());
	_running = true;
	_threads.reserve(numThreads);

	for (int i = 0; i < numThreads; ++i)
	{
		_threads.push_back(thread(&ThreadPool::runInThread, this));
	}
}

void ThreadPool::stop()
{
	{
		unique_lock<mutex>  lock(_mutex);
		_running = false;
		_notEmpty.notify_all();
	}

	for (size_t i = 0; i < _threads.size(); ++i)
	{
		_threads[i].join();
	}
}

void ThreadPool::run(const Task& task_)
{
	if (_threads.empty())
	{
		task_();
	}
	else
	{
		unique_lock<mutex> lock(_mutex);
		while (isFull())
		{
			_notFull.wait(lock);
		}

		assert(!isFull());
		_queue.push_back(task_);
		_notEmpty.notify_one();
	}
}

ThreadPool::Task ThreadPool::take()
{
	unique_lock<mutex> lock(_mutex);

	while (_queue.empty() && _running)
	{
		_notEmpty.wait(lock);
	}

	Task task;
	if (!_queue.empty())
	{
		task = _queue.front();
		_queue.pop_front();

		if (_maxQueueSize > 0)
		{
			_notFull.notify_one();
		}
	}
	return task;
}

bool ThreadPool::isFull()
{
	return _maxQueueSize > 0 && _queue.size() >= _maxQueueSize;
}


void ThreadPool::runInThread()
{
	try
	{
		while (_running)
		{
			Task task = take();
			if (task)
			{
				task();
			}
		}
	}
	catch (const exception& ex)
	{
		cerr << _name.c_str() << endl;
		cerr << ex.what() << endl;
		abort();
	}
	catch (...)
	{
		cerr << _name.c_str() << endl;
		
	}
}