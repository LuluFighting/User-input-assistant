 ///
 /// @file    Configuration.cc
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-09 17:38:54
 ///
#include "Configuration.h"
#include <stdlib.h>
#include <utility>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::ifstream;
using namespace wd;
wd::Configuration::Configuration(const string &filePath)
	:_filePath(std::move(filePath))
{
	ifstream ifs(_filePath);
	if(!ifs)
		cout << "file open error" << endl;
	string key,value;
	while(ifs >> key)
	{
		ifs >> value;
		_conf.insert(std::make_pair(key,value));
	}
	ifs.close();
}
string wd::Configuration::getDictDir() const
{
	auto cit = _conf.find("mydict");
	if(cit == _conf.end())
		return "";
	else
		return cit -> second;
}
string wd::Configuration::getIndexDir() const
{
	auto cit = _conf.find("myindex");
	if(cit == _conf.end())
		return "";
	else
		return cit -> second;
}
string wd::Configuration::getIp() const
{
	auto cit = _conf.find("myip");
	if(cit == _conf.end())
		return "";
	else
		 return cit -> second;
}
unsigned short wd::Configuration::getPort() const
{
	auto cit = _conf.find("myport");
	if(cit == _conf.end())
		return 0;
	else
		return atoi(cit ->second.c_str());
}
string wd::Configuration::getCache() const
{
	auto cit = _conf.find("mycache");
	if(cit == _conf.end())
		return "";
	else 
		return cit->second;
}
