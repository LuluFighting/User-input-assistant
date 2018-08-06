 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-07-02 10:13:04
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include "Noncopyable.h"

#include <pthread.h>
#include <functional>
using std::function;

namespace wd
{
class Thread;
struct ThreadPtr
{
	int _number;
	Thread *_pThread;
};
class Thread
: Noncopyable // 表达语义
{
	using ThreadCallback = function<void()>;
public:
	Thread(ThreadCallback && cb);
	~Thread();

	void start(int number);
	void join();
	
	bool isRunning() const {	return _isRunning;	}

private:
	static void * threadFunc(void *);//采用静态成员函数，就是为了去掉this的影响
private:
	pthread_t _pthid;
	bool _isRunning;
	ThreadCallback _cb;
};
}//end of namespace wd
 

#endif
