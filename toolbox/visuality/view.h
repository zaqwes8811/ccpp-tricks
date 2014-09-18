#ifndef REUSE_VIEW_H_
#define REUSE_VIEW_H_

#include <vector>
#include <list>

#include <ostream>
#include <iostream>
#include <algorithm>

namespace view {
template <typename T>
class Action {
public:
  explicit Action(std::ostream* o_) : o(o_) { }
  void operator()(const T& elem) const {
    *o << elem << ", ";
  }
  std::ostream* const o;
}; 
 
template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& a) 
{
  std::for_each(a.begin(), a.end(), Action<T>(&o));
  o << std::endl;
  return o;
}

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::list<T>& a) 
{
  std::for_each(a.begin(), a.end(), Action<T>(&o));
  o << std::endl;
  return o;
}

template<class T>
inline void print_elems(const T& coll, const char* optcstr="") {
  typename T::const_iterator pos;
  std::cout << optcstr;
  for (pos = coll.begin(); pos != coll.end(); ++pos)
    std::cout << *pos << ' ';
  std::cout << std::endl;
}

template<class T>
inline void insert_elems(T& coll, int first, int last) {
  for (int i = first; i <= last; ++i)
    coll.insert(coll.end(), i);
}


}

#endif  // REUSE_VIEW_H_