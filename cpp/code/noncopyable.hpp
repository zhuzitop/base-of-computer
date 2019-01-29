#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

class noncopyable
{
public:
	noncopyable(const noncopyable&) = delete;
	void operator=(const noncopyable&) = delete;
	
protected:
	noncopyable() = default;
	~noncopyable() = default;
};

#endif //NONCOPYABLE_HPP