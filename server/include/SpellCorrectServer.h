///
/// @file    SpellCorrectServer.h
/// @author  Borix(244303237@qq.com)
/// @date    2018-07-11 16:57:56
///
#ifndef __SPELLCORRECTSERVER_H__
#define __SPELLCORRECTSERVER_H__
#include "TcpServer.h"
#include "Threadpool.h"
using namespace wd;
namespace wd{
	class SpellCorrectServer
	{
		public:
			SpellCorrectServer(const string& ip,
							   unsigned short port,
							   size_t threadNUM,
							   size_t queSize);
			void start();
		private:
			void onConnection(const TcpConnectionPtr &);
			void onMessage(const TcpConnectionPtr&);
			void onClose(const TcpConnectionPtr&);
			TcpServer _tcpserver;
			Threadpool _threadpoll;
	};
};



#endif
