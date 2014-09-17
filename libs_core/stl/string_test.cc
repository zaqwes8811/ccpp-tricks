#include <gtest/gtest.h>

#include <cassert>
#include <string>
#include <vector>

using namespace std;
  
TEST(STL, Strings) {
  /// std::string
  // TODO: что с юникодом?
  // string, wstring, C-string
  string filename("hello.tmp");
  string::size_type idx = filename.find('.');  // возвращает позицию первого совпадения
  assert(idx != string::npos);
  //assert(distance(idx, string::npos) == 4);  // не компилируется
  assert(typeid(idx) == typeid(string::size_type));  // !!
  
  string base_name = filename.substr(/*1000 - std::out_of_range*/0, (idx+1)-1);  // второй аргумент - количество символов!
  assert(base_name == "hello");
  //base_name = filename.substr(filename.find('x'));  // exception
  string tmp_name = filename;
  tmp_name.replace(idx+1, string::npos, "h");  // похоже убирает лишние символы
  assert(tmp_name == "hello.h");
  assert(tmp_name.size() < filename.size());
  
  // поиск в обратном направлении
  const string delims("\t ");
  string for_tream = "h.\t \t no way";  // разбить на слова
  string::size_type beg_idx = for_tream.find_first_not_of(delims);  // поиск с начала?
  
  vector<string> words;
  
  // TODO: интервалы в строках - открытые, закрытые?
  while (beg_idx != string::npos) {
    // ищем первый разделительный символ
    string::size_type end_idx = for_tream.find_first_of(delims, beg_idx);
    if (end_idx == string::npos)
      end_idx = for_tream.length();
    
    words.push_back(for_tream.substr(beg_idx, end_idx-beg_idx));  // [begin, N штук
    
    // Но кажется лучше не испоьзовать npos and size_type
    //for (int i = end_idx-1; i >= static_cast<int>(beg_idx);  // приведение типов обязательно!!

    // Next interval
    beg_idx = for_tream.find_first_not_of(delims, end_idx);
  }
  
  // C-strings
  //string s;
  //const char* p = s.c_str();
  //s += "ext";
  // !!! p is invalid!!!
  
  // capacity() - как у вектора 
  //   - нужно учитывать, если используются ссылки, указатели или итераторы или если важна производительность
  // [] - работает по разному для const and non-const string
  //
  // TODO: WTF?
  // https://www.sgi.com/tech/stl/basic_string.html - "has very unusual iterator invalidation semantics"
  // begin, end для неконстант могут стать невалидной!!
  // http://www.cplusplus.com/forum/general/29533/ - похоже ошибка перевода
  // https://www.securecoding.cert.org/confluence/pages/viewpage.action?pageId=29032683
  
  // std::string someStringReturningFunction();
  /* ... */
  //const char* str = someStringReturningFunction().c_str();  // tmp object
  //  CERT C++ Secure Coding Standard
  //
  // DANGER: в c++98 не поддерживаются регулярные выражения, but in C++11 - yes
  // DANGER: смена регистра 
  //   http://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case - Boost
  // LIBRARY: http://site.icu-project.org/ ICU
  // ICU in embedded world - http://thebugfreeblog.blogspot.ru/2013/05/cross-building-icu-for-applications-on.html
}