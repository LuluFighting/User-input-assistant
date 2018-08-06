 ///
 /// @file    Configuration.cpp
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-09 17:38:54
 ///
#include "Configuration.h"
#include <utility>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::ifstream;
Configuration::Configuration(const string &filePath)
	:_filePath(std::move(filePath))
{
	ifstream ifs(_filePath);
	if(!ifs)
		cout << "file open error" << endl;
	ifs >> _englishDir;
	ifs >> _chineseDir;
	ifs.close();
}
