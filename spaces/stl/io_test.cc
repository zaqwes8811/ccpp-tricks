// Скоростное чтение 
// http://easy-coding.blogspot.ru/2009/02/stl.html
//
// Benchmarks:
// https://groups.google.com/forum/?hl=en#!msg/perfo/Hs84t9fqfTg/MFAGXo6uD1MJ

#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

TEST(STL, IO) {
  std::ifstream is("testfile.txt");
  std::string v((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
}