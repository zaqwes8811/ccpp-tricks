// Inner 
#include "visuality/view.h"



#include <gtest/gtest.h>

#include <vector>
#include <algorithm>
#include <ostream>
#include <list>

#include <adobe/algorithm/generate.hpp>
//#include <adobe/algorithm/generate_n.hpp>
#include <adobe/algorithm/remove.hpp>
#include <adobe/algorithm/random_shuffle.hpp>

#include <boost/range/end.hpp>
#include <boost/range/begin.hpp>

using namespace std;
using view::operator<<;
//using boost::end;
//using boost::begin;

// copy(... inserter/back_inserter/front_ins) -> должны заменяться интервальными функциями, insert, например

namespace {
  
struct LinearGen {
  LinearGen() : val(1) { }
  
  int operator()() {
    return val++;
  }
  
  int val;
};
  
bool bad_value(int x) 
{
    return x < 4;
}

  
bool rm_bad_value(int x) 
{
    return x == 7;
}

}  // names..

TEST(STL, RemoveInsertErase) 
{
  vector<int> v2;
  v2.assign(10, 1);
  //adobe::fill(v2  // одинаковые элементы в готовый контейнер
  generate_n(v2.begin(), 8, LinearGen());
  cout << v2;
  
  // Это лучше чем copy! важна семантика
  vector<int> v1;
  //v1.assign(v2.begin() + v2.end() / 2, v2.end());
  v1.assign(v2.begin() + v2.size() / 2, v2.end());
  v1.insert(v1.end(), v2.begin() + v2.size() / 2, v2.end());  // вставка
  v1.insert(v1.begin(), v2.begin() + v2.size() / 2, v2.end());  // вставка
  adobe::random_shuffle(v1);
  cout << v1;
  
  // удаление
  // для списка лучше использовать собственное удаление
  v1.erase(adobe::remove(v1, 1), boost::end(v1)); // что-то не то
  cout << v1;
  
  //
  v1.erase(adobe::remove_if(v1, bad_value), boost::end(v1));
  cout << v1;
  
  /// List
  list<int> l;
  l.assign(boost::begin(v2), boost::end(v2));
  cout << l;
  l.remove(1);  // реально удаляет
  cout << l;
  // http://cppstudio.com/post/282/
  l.erase(++l.begin());  // ++op - возвращает уже новое значение
  cout << l;
  
  // DANGER: удаление с выводом в лог - Eff. STL_9
  vector<int> v1_copy = v1;
  cout << v1_copy;
  for (vector<int>::iterator i = v1_copy.begin(); i != v1_copy.end(); ) {
    if (rm_bad_value(*i)) {
      cout << "Log: " << *i << endl;
      i = v1_copy.erase(i);
      cout << "Current it: " << *i << endl;
    } else {
      ++i;
    }
  }
  
}






