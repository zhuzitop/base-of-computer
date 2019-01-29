#include <queue>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <unistd.h>

using namespace std;

//#define kDefaultChunkSize 10

template <typename T>
class ObjectPool 
{
public:
	ObjectPool(int chunkSize = kDefaultChunkSize)
		throw(invalid_argument, bad_alloc);
		
	~ObjectPool();
	
	T& acquireObject();
	
	void releaseObject(T& obj);
	
	int getCount();
	
protected:
	//m_FreeList stores the objects that are not currently in use by clients
	queue<T*> m_FreeList;
	//m_AllObjects stores pointers to all the objects, in use or not.
	//This vector is needed in order to ensure that all objects are freed properly in the destructor
	vector<T*> m_AllObjects;
	int m_ChunkSize;
	static const int kDefaultChunkSize = 10;
	
	//Allocates m_ChunkSize new objects and adds them to the m_FreeList
	void allocateChunk();
	static void arrayDeleteObject(T* obj);
	
private:
	ObjectPool(const ObjectPool<T>& src);
	ObjectPool<T>& operator=(const ObjectPool<T>& rhs);
	
};

template <typename T>
const int ObjectPool<T>::kDefaultChunkSize;

template <typename T>
ObjectPool<T>::ObjectPool(int chunkSize) 
	throw(invalid_argument, bad_alloc) : m_ChunkSize(chunkSize)
{
	if (m_ChunkSize <= 0)
	{
		throw invalid_argument("chunk size must be positive");
	}
	//create m_ChunkSize objects to start.
	allocateChunk();
}

//在连续的存储空间中分配m_ChunkSize个元素，
//它会在vector中存储对象数组的指针，并把每个对象压至queue中。
template <typename T>
void ObjectPool<T>::allocateChunk()
{
	T* newObjects = new T[m_ChunkSize];
	m_AllObjects.push_back(newObjects);
	for (int i = 0; i < m_ChunkSize; i++)
	{
		m_FreeList.push(&newObjects[i]);
	}
}

//Freeing function for use in the for_each algorithm in the destructor
template <typename T>
void ObjectPool<T>::arrayDeleteObject(T* obj)
{
	delete [] obj;
}

template <typename T>
ObjectPool<T>::~ObjectPool()
{
	for_each(m_AllObjects.begin(), m_AllObjects.end(), arrayDeleteObject);
}

//返回空闲列表中的队头对象，如果没有空闲对象则首先调用allocateChunk
template <typename T>
T& ObjectPool<T>::acquireObject()
{
	if (m_FreeList.empty())
	{
		allocateChunk();
	}
	T* obj = m_FreeList.front();
	m_FreeList.pop();
	return (*obj);
}

//将对象返回到空闲列表的队尾
template <typename T>
void ObjectPool<T>::releaseObject(T& obj)
{
	m_FreeList.push(&obj);
}

template <typename T>
int ObjectPool<T>::getCount()
{
	return m_FreeList.size();
}

//使用对象池，用户请求
class UserRequest
{
public:
	UserRequest() {}
	~UserRequest() {}
	
	//Methods to populate the request with specific information
	//Methods to retrive the request data
	
private:
	//data members
	
};

//客户
class Client
{
public:
	Client() {}
	~Client() {}
	
	UserRequest& obtainUserRequest(ObjectPool<UserRequest>& pool);
	void processUserRequest(ObjectPool<UserRequest>& pool, UserRequest& req);
private:

};

UserRequest& Client::obtainUserRequest(ObjectPool<UserRequest>& pool)
{
	cout << "Client::obtainUserRequest: " << pool.getCount() << endl;
	UserRequest& request = pool.acquireObject();
	sleep(10);
	//Populate the request with user input 
	return request;
}

void Client::processUserRequest(ObjectPool<UserRequest>& pool, UserRequest& req)
{
	//Process the request
	cout << "Client::processUserRequest: " << pool.getCount() << endl;
	pool.releaseObject(req);
}

int main()
{
	ObjectPool<UserRequest> requestPool(10);
	Client A1;
	Client A2;
	Client A3;
	Client A4;
	Client A5;
	Client A6;
	Client A7;
	Client A8;
	Client A9;
	Client A10;
	Client A11;
	Client A12;
	Client A13;
	
	//while (/*program is running*/)
	{
		UserRequest& req1 = A1.obtainUserRequest(requestPool);
		A1.processUserRequest(requestPool, req1);
	}
	{
		UserRequest& req2 = A2.obtainUserRequest(requestPool);
		A2.processUserRequest(requestPool, req2);
	}
	{
		UserRequest& req3 = A3.obtainUserRequest(requestPool);
		A3.processUserRequest(requestPool, req3);
	}
	{
		UserRequest& req4 = A4.obtainUserRequest(requestPool);
		A4.processUserRequest(requestPool, req4);
	}
	{
		UserRequest& req5 = A5.obtainUserRequest(requestPool);
		A5.processUserRequest(requestPool, req5);
	}
	{
		UserRequest& req6 = A6.obtainUserRequest(requestPool);
		A6.processUserRequest(requestPool, req6);
	}
	{
		UserRequest& req7 = A7.obtainUserRequest(requestPool);
		A7.processUserRequest(requestPool, req7);
	}
	{
		UserRequest& req8 = A8.obtainUserRequest(requestPool);
		A8.processUserRequest(requestPool, req8);
	}
	{
		UserRequest& req9 = A9.obtainUserRequest(requestPool);
		A9.processUserRequest(requestPool, req9);
	}
	{
		UserRequest& req10 = A10.obtainUserRequest(requestPool);
		A10.processUserRequest(requestPool, req10);
	}
	{
		UserRequest& req11 = A11.obtainUserRequest(requestPool);
		A11.processUserRequest(requestPool, req11);
	}
	{
		UserRequest& req12 = A12.obtainUserRequest(requestPool);
		A12.processUserRequest(requestPool, req12);
	}
	{
		UserRequest& req13 = A13.obtainUserRequest(requestPool);
		A13.processUserRequest(requestPool, req13);
	}
}
