 ///
 /// @file    Configuration.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-09 17:33:10
 ///
#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__
#include "Nocopyable.h"
#include <string>
#include <map>
using std::string;
using std::map;
class Configuration
: public Nocopyable
{
public:
	Configuration(const string &filePath);
	string getEnglishDir() const
	{ return _englishDir;}
	string getChineseDir() const
	{ return _chineseDir;}
private:
	string _filePath;
	string _englishDir;
	string _chineseDir;
};
template<typename T>
class Singleton
{
public:
	template<typename ...Args>
	static T* getInstance(Args ...args)
	{
		if(!_pInstance)
			_pInstance = new T(args...);
		return _pInstance;
	}
	static void destroy()
	{
		if(_pInstance)
			delete _pInstance;
	}
private:
	Singleton();
	~Singleton();
	static T *_pInstance;
};
template<typename T>
T * Singleton<T>::_pInstance = NULL;

#endif
