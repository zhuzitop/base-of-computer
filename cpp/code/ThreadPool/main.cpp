#include "SyncQueue.hpp"
#include "ThreadPool.hpp"
#include <iostream>
using namespace std;

void TestThreadPool()
{
	ThreadPool pool;
	
	thread thd1([&pool]{
		for(int i = 0; i < 10; i++)
		{
			auto thdId = this_thread::get_id();
			pool.AddTask([thdId]{
				cout << "Sync thread 1 Id: " << thdId << endl;
			});
		}
	});
	
	thread thd2([&pool]{
		for(int i = 0; i < 10; i++)
		{
			auto thdId = this_thread::get_id();
			pool.AddTask([thdId]{
				cout << "Sync thread 1 Id: " << thdId << endl;
			});
		}
	});
	
	this_thread::sleep_for(std::chrono::seconds(2));
	getchar();
	pool.Stop();
	thd1.join();
	thd2.join();
}

int main()
{
	TestThreadPool();
}

