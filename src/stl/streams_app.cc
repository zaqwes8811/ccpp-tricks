#include <typeinfo>


#include <cassert>

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

// no standart now
//#include <ext/hash_set>
#include <boost/unordered_set.hpp>

// 3rdpary
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) 
{
  for_each(begin(v), end(v), 
    [&os](const T& item) {
      os << item << '/';});
  os << endl;
  return os;
}

int main() {
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
  cout << words;
  
  // DANGER: в c++98 не поддерживаются регулярные выражения, but in C++11 - yes

  /// std::streams
  // istream - in
  // ostream - out
  // Это спецификации шаблонов для char - узкие потоковые классы
  //
  // TODO: как с буфферизацией? flush() как-то связан с этим?
  // TODO: а как с потоками?
  // TODO: потоковые буфферы как-то ускоряют, но как?
  //
  // TODO: обработка ошибок - классы разработаны до появл. искл. в станд., но можно сделать так
  //   чтобы при установке флагов генерировались исключения. Лучше пусть не генерят, а генерить пользовательские.
  // Генерить исключения при установке любого флага.
  // stream.exceptions(std::ios::eofbit | ios::failbit | ios::bacbit);
  //
  // Есть флаги состояния. Похоже при ощибках устанавливаются они, а не бросаются исключения.
  //  Есть обертки проверки условий operator!(), например, или operator void*() - но вообще вроде бы это не хорошо
  //
  // TODO: есть какие-то пропуски. в чем суть?
    

  
}