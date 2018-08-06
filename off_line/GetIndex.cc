///
/// @file    GetIndex.cc
/// @author  Borix(244303237@qq.com)
/// @date    2018-07-10 11:17:13
///
#include "GetIndex.h"
#include <fstream>
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::getline;
GetIndex::GetIndex(const string &sourceFilePath,const string &goleFilePath,const string& stopWordsFilePath)
	:_sourceFilePath(std::move(sourceFilePath))
	,_goleFilePath(std::move(goleFilePath))
	,_stopWordsFilePath(std::move(stopWordsFilePath))
{
	ifstream ifs(_sourceFilePath);
	if(!ifs){
		cout << "GetIndex file open error" << endl;
	}
	string line;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		string key;
		int value;
		iss >> key >> value;
		_dict.push_back(std::make_pair(key,value));	
	}
	ifstream ifs1(_stopWordsFilePath);
	if(!ifs1)
		cout << "file open error" << endl;
	string stopWord;
	while(ifs1 >> stopWord,!ifs1.eof())
	{
		//cout << stopWord << endl;
		_stopWords.insert(stopWord);
	}
}
vector<string> GetIndex::getOneCharacter(const string &word)
{
	vector<string> tmp;
	auto cit = word.begin();
	while( cit < word.end())
	{
		if((*cit & 224) == 224)
		{
			//string oneCharacter = ""+ *cit + *(cit+1) + *(cit +2);
			string oneCharacter;
			oneCharacter.append(cit,cit+3);
			tmp.push_back(oneCharacter);
			cit += 3;
		}else if( (*cit & 240) == 240){
			string oneCharacter;
			oneCharacter.append(cit,cit+4);
			tmp.push_back(oneCharacter);
			cit += 4;
		}else
			break;
	}
	return tmp;
}
bool GetIndex::isEnglish(const string &rhs) const 
{
	char ch = *(rhs.begin());
	if(ch < 0)
		return false;
	return true;
}
void GetIndex::construct_index()
{
	for(size_t i = 0 ; i!=_dict.size() ; ++i)
	{
		string tmp = _dict[i].first;
		//cout << tmp << endl;
		if(isEnglish(tmp))
		{
			for(auto ch:tmp)
			{
				string charactor(1,ch);
				if(isalpha(ch))
				{
					auto cit = _index.find(charactor);
					if(cit == _index.end())
					{
						set<int> smp;
						smp.insert(i);
						_index.insert(std::make_pair(charactor,smp));
					}else { //已经存在了该字母的索引
						cit -> second.insert(i);
					}
				}
			}
		}else{   //处理中文
			vector<string> oneCharacterRally = getOneCharacter(tmp);
			for( auto oneCharacter:oneCharacterRally)
			{
				//cout << oneCharacter << " ";
				if(_stopWords.find(oneCharacter) == _stopWords.end()){   //stop_words中不存在该单词，则加入索引
					auto it = _index.find(oneCharacter);
					if(it == _index.end()){
						set<int> tmp;
						tmp.insert(i);
						_index.insert(std::make_pair(oneCharacter,tmp));
					}else 
						it -> second.insert(i);
				}
			}
		}
	}
}

void GetIndex::store_index()
{
	std::ofstream ofs(_goleFilePath); //ofs存储索引的内容
	if(!ofs){
		cout << "file open error " << endl;
		return;
	}
	for(auto data:_index)
	{
		ofs << data.first << " ";
		for(auto linenum:data.second)
		{
			ofs << linenum << " ";
		}
		ofs << endl;
	}
	ofs.close();
}
