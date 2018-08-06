 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-07-02 10:15:38
 ///
 

#include "Thread.h"
#include <iostream>

using std::cout;
using std::endl;
using namespace wd; 

__thread int t_number;
//右值引用本身到底是左值还是右值，取决于其是否有名字
Thread::Thread(ThreadCallback && cb)
: _pthid(0)
, _isRunning(false)
, _cb(std::move(cb))
{
	cout << "Thread(cb)" << endl;
}

void Thread::start(int number)
{
	ThreadPtr *threadPtr = new ThreadPtr();
	threadPtr->_number = number;
	threadPtr->_pThread = this;
	pthread_create(&_pthid, NULL, threadFunc, threadPtr);
	_isRunning = true;
}

void * Thread::threadFunc(void * arg)
{
	ThreadPtr * threadPtr = static_cast<ThreadPtr*>(arg);
	Thread *pthread = threadPtr ->_pThread;
	t_number = threadPtr -> _number;
	if(pthread)
		pthread->_cb();// 执行任务
	delete threadPtr;
	return NULL;
}

void Thread::join()
{
	pthread_join(_pthid, NULL);
	_isRunning = false;
}

Thread::~Thread()
{
	if(_isRunning)	
	{
		pthread_detach(_pthid);// 将运行的线程交给系统进行托管
		_isRunning = false;
	}
	cout << "~Thread()" << endl;
}



