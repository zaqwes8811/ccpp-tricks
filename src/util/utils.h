// encoding : utf8
/**
  file : #include "utils.h" 
  
  TODO :
    РёР· СЃС‚СЂРѕРєРё РІ С‡РёСЃР»Рѕ, Р¶РµР»Р°С‚РµР»СЊРЅРѕ РЅРµ Р±РµСЂРµР· itoa
    РєР°Рє СЃРґРµР»Р°С‚СЊ РґСЂРѕР±РёР»РєСѓ СЃС‚Р°РЅРґР°СЂС‚РЅРѕР№ СЃС‚СЂРѕРєРё Р»СЋР±С‹Рј СЃРёРјРІРѕР»РѕРј?
    
*/
#ifndef _UTILS
#define _UTILS

namespace utils {
void print(int* array, int N);
void print(int, int);
void print(std::string, int, int);
void print(std::string , int);
void print(std::string);
void print(std::string , int, std::string , int);
void print(std::string , int, std::string , int, std::string , int);
void print(std::vector<std::string> content);

std::string int2string(int);
std::vector<std::string> file2list(std::string fname);
std::vector<std::string> split_spaces(std::string str);
}
#endif //_UTILS