#pragma once 

// C++
#include <string>
#include <vector>

// Other
#include <v8.h>

// Accessing to dynamic vars.
// Point x y
class Point {
  public:
  //Point() : x_(1), y_(2) { }
  //Point(int x, int y) : x_(x), y_(y) { }
  int x_;
  int y_;
  std::vector<int> rgb_;
  
  // cppclean failed here.
  //std::vector<vector<int>> rgb_add_;

  //std::string name_;  // ѕока нельз€!
  
  // cppclean failed here.
  //int rgb_[3];  // запрещено! Ёто в целом вредно
  //int rgb_empty_[10][11];
};


