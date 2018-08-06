 ///
 /// @file    TimerThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-07-06 16:43:53
 ///
 
#ifndef __WD_TIMERTHREAD_H__
#define __WD_TIMERTHREAD_H__

#include "Timer.h"
#include "Thread.h"

#include <functional>

namespace wd
{
	
class TimerThread
{
public:
	using TimerCallback = std::function<void()>;
	TimerThread(int, int, TimerCallback && cb);
	~TimerThread();

	void start();
	void stop();


private:
	Timer _timer;
	Thread _subThread;
	bool _isStarted;
};
}//end of namespace wd

#endif
