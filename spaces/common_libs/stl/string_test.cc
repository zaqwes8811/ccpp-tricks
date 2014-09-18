#include "visuality/view.h"

#include <gtest/gtest.h>

#include <boost/unordered_set.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using namespace boost;
using namespace view;
  
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


//equal_to<string::value_type>()  // удаляет все
//bind2nd(equal_to<char>(), ' ');  // нужен был бинарный предикат
struct spaces_purger
{
  bool operator()(string::value_type f, string::value_type n) const {
    return isspace(f) && isspace(n);
  }
};


// distance(s.begin()+offset, s.end())) 
// substr не катит - возвращает копию
// http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

/*
{
  //Idx offset = 0;
  Idx end_it = string::npos;

  while (true) {
    Idx endpos = s.rfind(" ");

    if (endpos != end_it) 
      break;

    string tmp(s.begin() + (endpos + 1), end_it);
    tmp.append(" ");

    // найденный итерато не действителен
    cout << s << "<" << endl;
    break;
  }

  //s.insert(s.begin(), tmp.begin(), tmp.end());
  //s.erase(s.begin() + endpos + tmp.size(), s.end());
}
*/
//typedef string::size_type Idx;
// http://stackoverflow.com/questions/1011790/why-does-stdstring-findtext-stdstringnpos-not-return-npos
//
// In place
//   http://stackoverflow.com/questions/12065774/why-does-cache-locality-matter-for-array-performance
TEST(OJ, Reverse) {
  // O(n) но с несколькими константами

  string s("  the   skyy is  blue   ");
  s = "a";
  s = "   ";
  const char splitter(' ');
  
  // убираем повторяющиеся пробелы
  s.erase(
      unique(s.begin(), s.end(), spaces_purger()), 
      s.end());  // O(n)

  if (s == " ") s = "";
  
  {
    // trim - no copy
    string::size_type startpos = s.find_first_not_of(splitter);
    if( string::npos != startpos ) s.erase(s.begin(), s.begin()+startpos);

    string::size_type endpos = s.find_last_not_of(splitter);  // size_t нельзя!!!
    // раз не равно, то можно еще прибавить
    if (string::npos != endpos) s.erase(s.begin()+endpos+1, s.end()); 
  }

  // Real work
  // нарезать слишком долго
  // чтобы не искать с конца вращаем всю строку
  reverse(s.begin(), s.end());  // O(n)
  
  {
    // вращает отдельные слова
    string::size_type offset = 0;
    while (true) {
      // если превышает, то просто не найдет
      string::size_type space_pos = s.find(splitter, offset);  
      if (space_pos == string::npos) {
        reverse(s.begin()+offset, s.end());  // последнюю не найдет
        break;
      }
      reverse(s.begin()+offset, s.begin()+space_pos);
      offset = space_pos+1;  // раз мы здесь, то +1 максимум станет концом строки
    }
  }
}

/*
// tooo much code
class acc {
public:
  explicit acc(const string& _rest) : rest(_rest), it(0) {}
  string summary;
  string current;

  string::size_type it;
  const string rest;  // raw rest

  ass split() {
    commit_();
    ass a(" ");
    return a;
  }

private:
  // слово была найдено
  void commit_() {
    summary += current;
    summary += " ";
    string().swap(current);
  }
};
*/

// а если d, d, no-d, d - склеит вместе - похоже все последовательность не валидна
//
// Dyn. progr. по идее должна решаться рекурсивно, но нам нужны все валиные треки
// 
// Похоже реально нужно копить в дерево - или вектор списков
//
// FIXME: time limit
//
// all word wariants
// будет похоже на дерево
// нужно как-то делиться
TEST(OJ, WordBreak2) {
  string s("catsanddog");
  //s = "dogsand";

  unordered_set<string> dict;
  //dict.insert("b");
  ///*
  dict.insert("cat");
  dict.insert("cats");
  dict.insert("and");
  dict.insert("sand");
  dict.insert("dog");
  //*/

  vector<string> r;
  for (int i = 0; i < 100000; ++i) {
    vector<string> store;

    store.push_back(s);

    // one word
    //string::size_type idx = 0;
    //while (true) {
    for (vector<string>::iterator elem = store.begin(); ; ) {
      // много на себя берет - и вставляет и удаляет

      if (elem == store.end())
        break;

      string value = *elem;//store[idx];
      cout << value << endl;
      // можно удалять путь, копия уже есть    

      string tail;
      string first_part;
      string::size_type i = value.rfind(" ");

      if (i == string::npos) { 
        tail = value; 
      } else {
        tail = value.substr(i+1, string::npos);
        first_part = value.substr(0, i+1);
      }

      // calc
      {
        string::size_type offset = 0;
        string tmp;
        while (true) {
          if (tail.begin()+offset == tail.end())
            break;

          tmp += tail.at(offset);
          if (dict.find(tmp) != dict.end()) {
            string new_record = tail;
            new_record.insert(offset+1, " ");  // сдвигает всю строку
            store.push_back(first_part + new_record);
          } 
          ++offset;
        }
      }

      // remove
      // elem уже не валидный
      if (dict.find(tail) == dict.end()) {
        //store.begin()+idx
        //cout << store << *elem << endl;
        elem = store.erase(elem);  // строка тупиковая
        cout << store << endl;
      } else {
        ++elem;
      }
    }
    r = store;
  }

  // prost-processing
  // удяляем строчки с невалидными записями
  cout << "Result: ";
  cout << r;
}

// gcc4.7 - строки похоже с подсчетом ссылок!
TEST(O_J, WordBreak2) {
  string s("catsanddog");
  //s = "dogsand";

  unordered_set<string> dict;
  //dict.insert("b");
  ///*
  dict.insert("cat");
  dict.insert("cats");
  dict.insert("and");
  dict.insert("sand");
  dict.insert("dog");
  //*/

  vector<
  shared_ptr<
  string
  > 
  > r;
  for (int i = 0; i < 100000; ++i) {
    // all word wariants
    // будет похоже на дерево
    // нужно как-то делиться
    //vector<string> store;
    vector<shared_ptr<string> > store;

    // много вставляем и удаляем, может список

    //store.reserve(1000);
    //vector<string::size_type> spaces;
    //spaces.reserve(1000);
    shared_ptr<string> ptr = make_shared<string>(s);

    store.push_back(ptr);
    //spaces.push_back(string::npos);

    // one word
    string::size_type idx = 0;
    while (true) {
    
      if (idx >= store.size())
        break;

      string value = *store[idx];
      // можно удалять путь, копия уже есть    

      string tail;
      string begin;
      string::size_type i = 
          //spaces[idx];  // принципиально скорости не прибыло
          value.rfind(" ");

      if (i == string::npos) { 
        tail = value; 
      } else {
        tail = value.substr(i+1, string::npos);
        begin = value.substr(0, i+1);
      }

      // calc
      {
        string::size_type offset = 0;
        string tmp;
        while (true) {
          if (tail.begin()+offset == tail.end())
            break;

          tmp += tail.at(offset);
          if (dict.find(tmp) != dict.end()) {
            string new_record = tail;
            new_record.insert(offset+1, " ");  // сдвигает всю строку

            // not correct
            //begin.insert(begin.end(), new_record.begin(), new_record.end());  // no speed up

            shared_ptr<string> ptr = make_shared<string>(begin+new_record);
            store.push_back(ptr);

            //spaces.push_back(begin.size()+(offset+1));  // нужно с конца
          } 
          ++offset;
        }
      }

      if (dict.find(tail) == dict.end()) {
        store.erase(store.begin()+idx);  // строка тупиковая
        //spaces.erase(spaces.begin()+idx);
      } else {
        ++idx;
      }
      
    }
    r = store;
  }

  // prost-processing
  // удяляем строчки с невалидными записями
  cout << "Result: ";
  cout << r;
}