 ///
 /// @file    DictProducer.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-09 18:59:59
 ///
#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__
#include "Nocopyable.h"
#include "SplitTool.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>
using std::shared_ptr;
using std::vector;
using std::map;
using std::string;
using std::pair;
class DictProducer
:public Nocopyable
{
public:
	DictProducer(const string ,const string ,const string &,SplitToolJieba *);
	~DictProducer() {}
	void build_dict();
	void build_cn_dict();
	void store_dict();
	vector<pair<string,int>>&  getIndict()
	{
		return _indict;
	}
private:
	void processEnglishWord(string &word);
	void processChineseWord(string &word);  //将中文中的数字去除
	void construct_indict();

	string _englishDir;
	string _chineseDir;
	string _goleFilePath;
	vector<string> _englishFiles;
	vector<string> _chineseFiles;
	map<string,int> _dict;
	vector<pair<string,int>> _indict;
	shared_ptr<SplitToolJieba> _splitTool;
};

#endif
