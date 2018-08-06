 ///
 /// @file    MyTask.cc
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-12 16:36:01
 ///

#include "MyTask.h"
#include "Configuration.h"
#include "Mydict.h"
#include "CacheManger.h"
#include "json/json.h"
#include <string.h>
#include <algorithm>
extern __thread int t_number;
bool MyTask::response(wd::Cache &cache)
{
	//cout << "In MyTask::response() " << endl;
	if(cache.find(_querry))
	{
		_conn ->sendInLoop(cache[_querry]);
		return true;
	}
	return false;
}
int MyTask::distance(const string &rhs)
{
	//
	//cout << ">> distance() start..." << endl;
	vector<Character> querryCharacter = getOneCharacter(_querry);
	vector<Character> indexCharacter = getOneCharacter(rhs);
	//cout << " >>>>> get two vector" << endl;
	int len1,len2;
	len1 = querryCharacter.size();
	len2 = indexCharacter.size();
	int edit[len1+1][len2+1] ;
	int i,j;
	for(i=0;i<=len1;++i)
		for(j=0;j<=len2;++j)
			edit[i][j] = 0;
	for(i=0;i<=len1;++i)
		edit[i][0] = i;
	for(j=0;j<=len2;++j)
		edit[0][j] = j;
	for(i=1;i<=len1;++i)
		for(j=1;j<=len2;++j)
		{
			int cost = ((querryCharacter[i-1]== indexCharacter[j-1])?0:1);
			int deletion = edit[i-1][j] +1;
			int insertion = edit[i][j-1] + 1;
			int substitution = edit[i-1][j-1] + cost;
			edit[i][j] =  std::min(deletion,std::min(insertion,substitution));	
		}
	//cout << ">>>>>> distance() end..." << endl;
	return edit[len1][len2];
}
void MyTask::statistic(set<int> &iset)
{
	//cout << "In MyTask::statistic()" << endl;
	vector<pair<string,int>> dict = (Singleton<wd::Mydict>::getInstance(Singleton<wd::Configuration>::getInstance(CONFPATH)->getDictDir(),
																   Singleton<wd::Configuration>::getInstance(CONFPATH)->getIndexDir())
									)->getDict();
	for(auto &idx:iset)
	{
		string key = dict[idx].first;
		//cout << key << endl;
		int iDist = distance(key);
		if(iDist <= 3)
		{
			//cout << "Before _resultQue push" << endl;
			wd::MyResult res;
			res._word = key;
			res._iDist = iDist;
			res._iFreq = dict[idx].second;
			_resultQue.push(res);
		}
	}
}
vector<Character> MyTask::getOneCharacter(const string& word)
{
	//cout << "In MyTask::getOneCharacter()" << endl;
	auto cit = word.begin();
	vector<Character> ret;
	while(cit < word.end())
	{
		if( (*cit & 224) == 224){
			Character oneCharacter;
			oneCharacter.append(cit,cit+3);
			ret.push_back(oneCharacter);
			cit += 3;
		}else if( (*cit & 240) == 240){
			Character oneCharacter;
			oneCharacter.append(cit,cit+4);
			ret.push_back(oneCharacter);
			cit += 4;
		}else{
			Character oneCharacter(1,*cit);   //为一个字母，一个字节占一个字符
			ret.push_back(oneCharacter);
			cit ++;
		}
	}
	//cout << "before return" << endl;
	return ret;
}
void MyTask::queryIndexTable()
{
	//cout << "In MyTask::querryIndexTable()" << endl;
	map<string,set<int>> index = (Singleton<wd::Mydict>::getInstance(Singleton<wd::Configuration>::getInstance(CONFPATH)->getDictDir(),
																   Singleton<wd::Configuration>::getInstance(CONFPATH)->getIndexDir())
									)->getIndexTable();
	vector<Character> oneCharacter = getOneCharacter(_querry);
	set<int> allRally;
	for(auto myCharacter:oneCharacter)
	{
		auto cit = index.find(myCharacter);
		if(cit != index.end())
		{
			for(auto &idx:cit->second)
				allRally.insert(idx);
		}
	}
	statistic(allRally);
}
void MyTask::execute()
{
	wd::Cache& mycache = (Singleton<wd::CacheManger>::getInstance(
									Singleton<wd::Configuration>::getInstance(CONFPATH)->getCache() ))
									->getCache(t_number);
	if(response(mycache))
		return;
	else{
		queryIndexTable();
		Json::FastWriter writerinfo;
		Json::Value arrayObj;
		while(!_resultQue.empty())
		{
			Json::Value new_item;
			new_item[""] = _resultQue.top()._word;
			_resultQue.pop();
			arrayObj.append(new_item);
		}
		string strEmail = writerinfo.write(arrayObj);
		mycache.addElement(_querry,strEmail);
		_conn -> sendInLoop(strEmail);
	}	
}
