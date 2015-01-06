#include <typeinfo>

#include "visuality/view.h"

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/unordered_set.hpp>
#include <gtest/gtest.h>
#include <loki/ScopeGuard.h>
//#include <ext/hash_set>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>


using namespace std;
using namespace Loki;
using namespace view;
using boost::begin;
using boost::end;

// замена static. И все равно... не похоже норм. Можно пихать сюда функторы.
/*
namespace {
 // https://www.securecoding.cert.org/confluence/display/cplusplus/DCL15-CPP.+Declare+file-scope+objects+or+functions+that+do+not+need+external+linkage+in+an+unnamed+namespace
template<typename T>
static ostream& operator<<(ostream& os, const vector<T>& v) 
{
  for_each(begin(v), end(v), 
    [&os](const T& item) {
      os << item << '/';});
  os << endl;
  return os;
}
}

*/
namespace {
  
// Можно похоже только указатели передавать
void restore_stream_flags(ostream& o, ios::fmtflags old_flags) {
  o.flags(old_flags);
}
  
}

TEST(STL, _StreamIterators) {
  vector<int> a(5, 8);
  copy(a.begin(), a.end(), std::ostream_iterator<int>(cout, " "));
  cout << endl;
}

    
TEST(STL, StreamsTest) {
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
  
  // Point: форматирование
  // TODO: на консоль и в файл
  vector<int> vi;
  int a[] = {3, 8, 9, 0, 9};
  vi.insert(vi.begin(), a, a+5);
  cout << vi;
  
  {
    // И как тут применить guard?
    // http://www.codeproject.com/Articles/18453/Automatic-resource-cleanup-a-lightweight-scope-gua
    ios::fmtflags old_flags =  cout.flags();
    ScopeGuard g1 = MakeGuard(&restore_stream_flags, ByRef(cout), old_flags);

    cout.setf(ios::showpos | ios::showbase);// | ios::uppercase);
    cout.setf(ios::right, ios::adjustfield);
    cout << setw(6) << hex << 9;
    cout << 9 << endl;  // не очень - хотелось бы выводить число нулей
    
    // float
    cout << scientific << showpoint << setprecision(8) << 0.1234567 << endl;
    cout << scientific << showpoint << setprecision(8) << 490.0 << endl;
  }
  
  // Buffers
  {
    // деструктор не удаляет буффер
    ostream hexout(cout.rdbuf());  // TRICK: можно свой создать и настроить
    // на буффер не влияет, так что можно передать буффер в функции, а потом настраивать поток
    // это влияние на буффер не окажет
    hexout.setf(ios::hex, ios::basefield);
    hexout.setf(ios::showbase);
    
    hexout << 10 << endl;
    hexout << 10 << endl;
  }
  
  {
    // если читать и писать, то можно fstream, а можно i and o
    ofstream out("testfile.txt", ios::in | ios::out);  // но откр. для чтения И записи
    istream in(out.rdbuf());
  }

}

// Скоростное чтение 
// http://easy-coding.blogspot.ru/2009/02/stl.html
//
// Benchmarks:
// https://groups.google.com/forum/?hl=en#!msg/perfo/Hs84t9fqfTg/MFAGXo6uD1MJ
TEST(STL, IO) {
  std::ifstream is("testfile.txt");
  std::string v((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
}