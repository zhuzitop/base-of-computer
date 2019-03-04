#include <string>
#include <functional>
#include <memory>
#include <map>
#include "noncopyable.hpp"

using namespace std;

const int MaxObjectNum = 10;

template<typename T>
class ObjectPool : noncopyable
{
	template<typename... Args>
	using Constructor = function<shared_ptr<T>(Args...)>;
public:
	/*ObjectPool():needClear(false){}
	~ObjectPool()
	{
		needClear = true;
	}*/
	
	template<typename... Args>
	void Init(size_t num, Args&&... args)
	{
		if (num <= 0 || num > MaxObjectNum)
			throw logic_error("object num out of range");
		
		auto constructName = typeid(Constructor<Args...>).name();
		for (size_t i = 0; i < num; i++)
		{
			m_object_map.emplace(constructName, shared_ptr<T>(new T(forward<Args>(args)...), [this, constructName](T* p)
			{
				//return createPtr<T>(string(constructName), args...);
				m_object_map.emplace(move(constructName), shared_ptr<T>(p));
			}));
		}
	}
	
	/*
	//template<typename T, typename... Args>
	template<typename... Args>
	shared_ptr<T> createPtr(string& constructName, Args... args)
	{
		return shared_ptr<T>(new T(args...), [constructName, this](T* t)
		{
			if(needClear)
				delete []t;
			else
				m_object_map.emplace(constructName, shared_ptr<T>(t));
		});
	}
	*/
	
	template<typename... Args>
	shared_ptr<T> Get()
	{
		string constructName = typeid(Constructor<Args...>).name();
		
		auto range = m_object_map.equal_range(constructName);
		for (auto it = range.first; it != range.second; ++it)
		{
			auto ptr = it->second;
			m_object_map.erase(it);
			return ptr;
			
		}
		return nullptr;
	}

private:
	multimap<string, shared_ptr<T>> m_object_map;
	//bool needClear;
	
};

int main()
{
	
}
