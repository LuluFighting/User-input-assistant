 ///
 /// @file    GetIndex.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-10 11:06:47
 ///

#ifndef __GETINDEX_H__
#define __GETINDEX_H__
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <utility>
#include <unordered_set>
using std::unordered_set;
using std::vector;
using std::unordered_map;
using std::string;
using std::set;
using std::pair;
class GetIndex
{
public:
	GetIndex(const string&,const string&,const string &);
	~GetIndex() {}
	void construct_index();
	void store_index();
private:
	bool isEnglish(const string &rhs) const;
	vector<string> getOneCharacter(const string& word);

	string _sourceFilePath;
	string _goleFilePath;
	string _stopWordsFilePath;
	vector<pair<string,int>> _dict;
	unordered_set<string> _stopWords;
	unordered_map<string,set<int>> _index;
};

#endif
