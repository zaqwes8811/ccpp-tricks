
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

// istream - in
// ostream - out
// Это спецификации шаблонов для char - узкие потоковые классы
//
// TODO: как с буфферизацией? flush() как-то связан с этим?
// TODO: а как с потоками?
// TODO: потоковые буфферы как-то ускоряют, но как?
//
// Есть флаги состояния. Похоже при ощибках устанавливаются они, а не бросаются исключения.
//  Есть обертки проверки условий operator!(), например

int main() {
  
}