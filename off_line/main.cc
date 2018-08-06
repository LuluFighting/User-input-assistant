 ///
 /// @file    main.cc
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-10 17:12:47
 ///
#include "Configuration.h"
#include "SplitTool.h"
#include "DictProducer.h"
#include "GetIndex.h"
#include <iostream>
#include <memory>
const char* const DICT_PATH = "../cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "../cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "../cppjieba/dict/stop_words.utf8";
const string GOLE_DICT_PATH = "../server/data/dict.txt";
const string GOLE_INDEX_PATH = "../server/data/index.txt";
using std::cout;
using std::endl;
using std::shared_ptr;
class SplitTool;
int main()
{
	Configuration * pconfig = Singleton<Configuration>::getInstance("configure.txt");
	//SplitTool *ptool = new SplitToolJieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH); 
	SplitToolJieba *ptool = new SplitToolJieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH);  //jieba分词工具
	DictProducer mydictProducer(pconfig ->getEnglishDir(),pconfig->getChineseDir(),GOLE_DICT_PATH,ptool);   // 构建DictProducer对象
	mydictProducer.build_dict();           //建立英文词典
	mydictProducer.build_cn_dict();        //建立中文词典
	mydictProducer.store_dict();           //存储词典
	GetIndex myindex(GOLE_DICT_PATH,GOLE_INDEX_PATH,"stop_words_zh.txt");   //构建GetIndex对象
	myindex.construct_index();           //建立索引
	myindex.store_index();               //存储索引
	Singleton<Configuration>::destroy();
	return 0;
}
