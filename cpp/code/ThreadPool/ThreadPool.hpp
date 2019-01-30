#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <list>
#include <thread>
#include <functional>
#include <iostream>
#include <memory>
#include <atomic>
#include "SyncQueue.hpp"

const int MaxTaskCount = 100;

class ThreadPool
{
public:
	using Task = function<void()>;
	ThreadPool(int numThread = thread::hardware_concurrency()):m_queue(MaxTaskCount)
	{
		Start(numThread);
	}
	~ThreadPool()
	{
		Stop();
	}
	
	void Stop()
	{
		call_once(m_flag, [this]{StopThreadGroup();});
	}
	
	void AddTask(Task&& task)
	{
		m_queue.Put(forward<Task>(task));
	}
	
	void AddTask(const Task& task)
	{
		m_queue.Put(task);
	}

private:
	void Start(int numThread)
	{
		m_running = true;
		for (int i = 0; i < numThread; i++)
		{
			m_threadgroup.push_back(make_shared<thread>(&ThreadPool::RunInThread, this));
		}
	}
	
	void RunInThread()
	{
		while(m_running)
		{
			list<Task>list;
			m_queue.Take(list);
			
			for(auto& task : list)
			{
				if(!m_running)
				{
					return;
				}
				task();
			}
		}
	}
	
	void StopThreadGroup()
	{
		m_queue.Stop();
		m_running = false;
		
		for(auto thread : m_threadgroup)
		{
			if(thread)
			{
				thread->join();
			}
		}
		m_threadgroup.clear();
	}	
	
private:
	list<shared_ptr<thread>> m_threadgroup;
	SyncQueue<Task> m_queue;
	atomic_bool m_running;
	once_flag m_flag;
	
};

#endif


