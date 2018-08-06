 ///
 /// @file    CacheManger.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-12 15:47:06
 ///
#ifndef __CACHEMANGER_H__
#define __CACHEMANGER_H__
#include "Cache.h"
#include <vector>
#define THREADNUM 4
using std::vector;
namespace wd
{
	class CacheManger
	{
	public:
		CacheManger(string filePath);
		void init(string);
		Cache& getCache(size_t);
		void periodicUpdate();
	private:
		string _cacheFilePath;
		vector<Cache> _cacheList;
	};
};



#endif
