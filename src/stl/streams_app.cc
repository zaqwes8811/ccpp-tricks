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



int main() {
  /// std::string
  // TODO: что с юникодом?
  // string, wstring, C-string
  string filename("hello.tmp");
  string::size_type idx = filename.find('.');  // возвращает позицию первого совпадения
  assert(idx != string::npos);
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
  while (beg_idx != string::npos) {
    
  }
  

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