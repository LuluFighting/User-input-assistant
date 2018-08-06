 ///
 // @file    SpellCorrectServer.cc
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-11 16:58:26
 ///
#include "SpellCorrectServer.h"
#include "MyTask.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <functional>
using std::cout;
using std::endl;
using std::string;
void SpellCorrectServer::onConnection(const wd::TcpConnectionPtr& conn)
{
	cout << conn->toString() << endl;
	conn -> send("hello,welcome to Chat Server.\r\n");
}
void SpellCorrectServer::onMessage(const wd::TcpConnectionPtr& conn)
{
	string s(conn -> receive());
	//cout << s << endl;
	MyTask task(s,conn);
	_threadpoll.addTask(std::bind(&MyTask::execute,&task));
	cout << "> add task to threadpool" << endl;
}
void SpellCorrectServer::onClose(const wd::TcpConnectionPtr& conn)
{
	::printf("%s close\n",conn -> toString().c_str());
}
SpellCorrectServer::SpellCorrectServer(const string& ip,
							unsigned short port,
							size_t threadNUM,
							size_t queSize)
	:_tcpserver(ip,port)
	,_threadpoll(threadNUM,queSize)
{}
void SpellCorrectServer::start()
{
	_threadpoll.start();
	_tcpserver.setConnectionCallback(std::bind(&SpellCorrectServer::onConnection,this,std::placeholders::_1));
	_tcpserver.setMessageCallback(std::bind(&SpellCorrectServer::onMessage,this,std::placeholders::_1));
	_tcpserver.setCloseCallback(std::bind(&SpellCorrectServer::onClose,this,std::placeholders::_1));
	_tcpserver.start();
}


