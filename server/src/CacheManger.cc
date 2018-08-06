 ///
 /// @file    CacheManger.cc
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-12 16:05:07
 ///
#include "CacheManger.h" 
#include <iostream>
#include <fstream>
#include <utility>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using namespace wd;
CacheManger::CacheManger(string cacheFilePath)
{
	init(cacheFilePath);
}
void CacheManger::init(string cacheFilePath)
{
	_cacheFilePath = cacheFilePath;
	_cacheList.reserve(THREADNUM);
	Cache tmp;
	tmp.readFromFile(_cacheFilePath);
	for(size_t i=0;i!=THREADNUM;++i)
	{
		_cacheList.push_back(std::move(tmp));
	}
}
Cache& CacheManger::getCache(size_t number)
{
	return _cacheList[number];
}
void CacheManger::periodicUpdate()
{
	auto cit = _cacheList.begin();
	Cache lastWrite = *(cit ++);
	for(;cit < _cacheList.end();++cit)
	{
		lastWrite.update(*cit);
	}
	for(cit = _cacheList.begin()+1;cit!=_cacheList.end();++cit)
	{
		(*cit).update(lastWrite);
	}
	lastWrite.writeToFile(_cacheFilePath);
}
