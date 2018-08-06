 ///
 /// @file    Configuration.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-09 17:33:10
 ///
#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__
#include "Noncopyable.h"
#include <string>
#include <map>
#define CONFPATH "./conf/configure.txt"
using std::string;
using std::map;
namespace wd{
	class Configuration
	: public Noncopyable
	{
	public:
		Configuration(const string &filePath);
		~Configuration() = default;
		string getDictDir() const;
		string getIndexDir() const;
		string getIp() const;
		string getCache() const;
		unsigned short getPort() const;
	private:
		string _filePath;
		map<string,string> _conf;
	};
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
