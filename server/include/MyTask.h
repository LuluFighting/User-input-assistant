///
/// @file    MyTask.h
/// @author  Borix(244303237@qq.com)
/// @date    2018-07-11 17:15:00
///
#ifndef __MYTASK_H__
#define __MYTASK_H__
#include "TcpConnection.h"
#include "Configuration.h"
#include "Mydict.h"
#include "Cache.h"
#include <string>
#include <queue>
using std::string;
using std::priority_queue;
class MyCompare{
public:
	bool operator()(const wd::MyResult & lhs, const wd::MyResult & rhs)
	{
		if(lhs._iDist != rhs._iDist)
			return lhs._iDist < rhs._iDist;
		else 
			return lhs._iFreq > rhs._iFreq;
	}
};
using Character = string;
class MyTask
{
public:
	MyTask(const string &querry,const wd::TcpConnectionPtr conn)
		:_querry(std::move(querry))
		,_conn(conn)
	{}
	void execute();
private:
	void queryIndexTable();   //查询索引
	void statistic(set<int> &iset);  //进行计算
	int distance(const string&  rhs); //计算最小编辑距离
	bool response(wd::Cache &cache);           //响应客户端的请求
	vector<Character> getOneCharacter(const string& word);    //获取字符数组
	string _querry;
	wd::TcpConnectionPtr _conn;
	priority_queue<wd::MyResult,vector<wd::MyResult>,MyCompare> _resultQue;
};


#endif
