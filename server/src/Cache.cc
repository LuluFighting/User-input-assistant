 ///
 /// @file    Cache.cc
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-12 15:35:30
 ///
#include "Cache.h" 
#include <fstream>
#include <iostream>
#include <utility>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using namespace wd;
void Cache::addElement(string querry,string result)
{
	_hashTable[querry] = result;
}
void Cache::readFromFile(string filePath)
{
	ifstream ifs(filePath);
	if(!ifs){
		cout << "Cache::readFromFile file open error" << endl;
		return;
	}
	string querry,result;
	while(ifs >> querry,!ifs.eof())
	{
		ifs >> result;
		_hashTable[querry] = result;
	}
}
void Cache::writeToFile(string filePath)
{
	ofstream ofs(filePath);
	if(!ofs){
		cout << "Cache::writeToFile file open error" << endl;
		return;
	}
	for(auto &mypair:_hashTable)
	{
		ofs << mypair.first << " ";
		ofs << mypair.second << endl;
	}
}
void Cache::update(const Cache& cache)
{
	for(auto &mypair:cache._hashTable)
	{
		auto cit = _hashTable.find(mypair.first);
		if(cit == _hashTable.end())
		{
			_hashTable.insert(std::move(mypair));
		}
	}
}
bool Cache::find(string querry)
{
	auto cit = _hashTable.find(querry);
	if(cit == _hashTable.end())
		return false;
	return true;
}
string& Cache::operator[](string key)
{
	return _hashTable[key];
}
