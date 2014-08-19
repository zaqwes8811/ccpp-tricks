
#include <vector>
#include <algorithm>
#include <ostream>

#include <adobe/algorithm/generate.hpp>
//#include <adobe/algorithm/generate_n.hpp>

#include <gtest/gtest.h>

// Inner 
#include "reuse/view.h"

using namespace std;
using view::operator<<;

// copy(... inserter/back_inserter/front_ins) -> должны заменяться интервальными функциями, insert, например

namespace {
  
struct LinearGen {
  LinearGen() : val(1) { }
  
  int operator()() {
    return val++;
  }
  
  int val;
};
  
  
//ostream& 

}  // names..

TEST(STL, RemoveInsertErase) 
{
  vector<int> v2;
  v2.assign(10, 1);
  //adobe::fill(v2  // одинаковые элементы в готовый контейнер
  generate_n(v2.begin(), 7, LinearGen());
  cout << v2;
  
  // Это лучше чем copy! важна семантика
  vector<int> v1;
  //v1.assign(v2.begin() + v2.end() / 2, v2.end());
  v1.assign(v2.begin() + v2.size() / 2, v2.end());
  v1.insert(v1.end(), v2.begin() + v2.size() / 2, v2.end());  // вставка
  v1.insert(v1.begin(), v2.begin() + v2.size() / 2, v2.end());  // вставка
  cout << v1;
  
}