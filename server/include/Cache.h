 ///
 /// @file    Cache.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-12 15:29:57
 ///

#ifndef __CACHE_H__
#define __CACHE_H__
#include <unordered_map>
#include <string>
using namespace std;
namespace wd
{
	class Cache
	{
	public:
		void addElement(string,string);
		void readFromFile(string);
		void writeToFile(string);
		void update(const Cache&);
		bool find(string querry);
		string& operator[](string key);
	private:
		unordered_map<string,string> _hashTable;
	};
};


#endif
