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
#include <loki/ScopeGuard.h>

using namespace std;
using namespace Loki;

// замена static. И все равно... не похоже норм. Можно пихать сюда функторы.
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

namespace {
  
// Можно похоже только указатели передавать
void restore_stream_flags(ostream& o, ios::fmtflags old_flags) {
  o.flags(old_flags);
}
  
}
    
int main() {
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
    cout.setf(ios::internal, ios::adjustfield);
    cout << hex << 9 << endl;  // не очень - хотелось бы выводить число нулей
  }
  

}