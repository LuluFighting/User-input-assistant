 ///
 /// @file    SplitTool.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-09 19:21:03
 ///
#ifndef __SPLITTOOL_H__
#define __SPLITTOOL_H__
#include "Configuration.h"
#include "../cppjieba/include/cppjieba/Jieba.hpp"
#include <string>
#include <vector>
using std::string;
using std::vector;
using namespace cppjieba;
class SplitToolJieba
{
public:
	SplitToolJieba(const string& dict_path,const string& model_path,const string& user_dict_path,const string& idfPath,const string& stopWordPath)
		:_jieba(dict_path,model_path,user_dict_path,idfPath,stopWordPath)
	{}
	~SplitToolJieba()
	{}
	void Cut(const string & sentence) 
	{
		vector<string> tmp;
		_jieba.Cut(sentence,tmp);
		_result.insert(_result.end(),tmp.begin(),tmp.end());
	}
	vector<string>& getResult()
	{
		return _result;
	}
private:
	vector<string> _result;
	cppjieba::Jieba _jieba;
};
#endif
