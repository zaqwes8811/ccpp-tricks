#pragma once 

// C++
#include <string>

// Other
#include <v8.h>

// Accessing to dynamic vars.
// Point x y
class Point {
  public:
  Point() : x_(1), y_(2) { }
  Point(int x, int y) : x_(x), y_(y) { }
  int x_;
  int y_;
  //std::string name_;  // Пока нельзя!
};


