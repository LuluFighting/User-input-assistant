///
/// @file    DictProducer.cc
/// @author  Borix(244303237@qq.com)
/// @date    2018-07-09 20:40:21
///
#include "DictProducer.h"

#include <cctype>
#include <utility>
#include <fstream>
#include <iostream>
#define FIRSTSIZE 10000
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
DictProducer::DictProducer(const string englishDir,const string chineseDir,const string &goleFilePath,SplitToolJieba *splitToolPtr)
	:_englishDir(englishDir)
	,_chineseDir(chineseDir)
	,_goleFilePath(goleFilePath)
{
	_splitTool.reset(splitToolPtr);
	std::ifstream ifsEnglish(_englishDir);
	ifstream ifsChinese(_chineseDir);
	string filePath;
	if(!ifsEnglish||!ifsChinese)
		cout << "Dict file open error" << endl;
	while(ifsEnglish >> filePath)
	{
		_englishFiles.push_back(filePath);
	}
	while(ifsChinese >> filePath)
	{
		_chineseFiles.push_back(filePath);
	}
	_indict.reserve(FIRSTSIZE);

}
void DictProducer::processEnglishWord(string &word)
{
	auto cit = word.begin();
	for(;cit != word.end(); ++cit)
	{
		if(!isalpha(*cit))   //剔除标点符号或数字
		{
			word.erase(cit);
			--cit;    //调整迭代器的位置
		}else if(isupper(*cit))  //将所有大写字母改为小写
		{
			*cit = tolower(*cit);
		}
	}
}
void DictProducer::processChineseWord(string &word)
{
	auto cit = word.begin();
	for(;cit != word.end(); ++cit)
	{
		if(isalnum(*cit))             //将数字去掉
		{
			word.erase(cit);
			-- cit;
		}
	}
}
void DictProducer::build_dict()  //建立英文词典
{
	for(auto &filePath:_englishFiles)
	{
		ifstream ifs(filePath);
		if(!ifs)
			cout << "English File open error" << endl;
		string word;
		while(ifs >> word)
		{
			processEnglishWord(word);
			auto cit = _dict.find(word);
			if(word.size() > 0 && cit == _dict.end())
				_dict.insert(std::make_pair(word,1));
			else if( cit != _dict.end())
				++ cit -> second;
		}
	}
}
void DictProducer::build_cn_dict()
{
	vector<string> words;
	for(auto filePath:_chineseFiles)
	{
		ifstream ifs(filePath);
		if(!ifs)
			cout << "Chinese file open error" << endl;
		string sentence;
		while(std::getline(ifs,sentence))
		{
			_splitTool -> Cut(sentence);
		}
	}
	vector<string>& results = _splitTool -> getResult();
	for(auto &res: results)
	{
		processChineseWord(res);
		auto cit = _dict.find(res);
		if(cit == _dict.end())
		{
			_dict.insert(std::make_pair(res,1));
		}else{
			++ cit -> second;
		}
	}
}
void DictProducer::store_dict()
{
	construct_indict();
	ofstream ofs(_goleFilePath);
	if(!ofs)
		std::cout << "Store_dict open file error" << endl;
	for(auto &mypair:_indict)
	{
		ofs << mypair.first << " " << mypair.second << std::endl;
	}
	ofs.close();
}
void DictProducer::construct_indict()
{
	for(auto dictpair:_dict)
	{
		_indict.push_back(dictpair);
	}
}

