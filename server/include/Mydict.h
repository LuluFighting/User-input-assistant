 ///
 /// @file    Mydict.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-11 20:25:02
 ///

#ifndef __MYDICT_H__
#define __MYDICT_H__
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::map;
using std::set;
using std::ifstream;
using std::istringstream;
namespace wd{
	struct MyResult
	{
		string _word;
		int _iFreq;         //词频
		int _iDist;         //最小编辑距离
	};
	class Mydict
	{
	public:
		Mydict(const string dictDir,const string indexDir)
		{
			ifstream ifs1(dictDir),ifs2(indexDir);
			if(!ifs1||!ifs2)
				cout << "Mydict open file error" << endl;
			string key;
			int value;
			ifs1 >> value; //将前面两个空格行读去
			_dict.push_back(std::make_pair(string(""),value));
			ifs1 >> value; //将前面两个空格行读去
			_dict.push_back(std::make_pair(string(""),value));
			while(ifs1 >> key)
			{
				ifs1 >> value;
				_dict.push_back(std::make_pair(key,value));
			}
			string line;
			while(std::getline(ifs2,line))
			{
				istringstream iss(line);
				string ikey;
				int ivalue;
				iss >> ikey;
				set<int> tmp;
				while(iss >> ivalue)
				{
					tmp.insert(ivalue);
				}
				_index.insert(std::make_pair(ikey,tmp));
			}
		}
		vector<pair<string,int>> & getDict()
		{ return _dict; }
		map<string,set<int>> & getIndexTable()
		{  return _index; }
	private:
		vector<pair<string,int>> _dict;
		map<string,set<int>> _index;
	};
};
#endif
