 ///
 /// @file    main.cc
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-13 11:01:15
 ///
#include "SpellCorrectServer.h"
#include "Configuration.h"
#include "CacheManger.h"
#include "TimerThread.h"
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using namespace wd;
int main()
{
	wd::CacheManger * mycacheManger = Singleton<CacheManger>::getInstance( Singleton<Configuration>::getInstance(CONFPATH)->getCache());
	TimerThread timer(5,600,std::bind(&CacheManger::periodicUpdate,mycacheManger));
	timer.start();
	SpellCorrectServer myspell(Singleton<Configuration>::getInstance(CONFPATH)->getIp(),
							   Singleton<Configuration>::getInstance(CONFPATH)->getPort(),
							   4,10);
	myspell.start();
	return 0;
}
