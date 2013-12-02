#pragma once

// Other
#include "v8.h"

// App
#include "point.h"

class Palette {
  public:
  int array[32];
  Point x;
  Point array[32];
};

class V8Palette {


private:

  // Все что нужно для работы с точкой.
  v8::Persistent<v8::ObjectTemplate> point_blueprint_;

  // Все что нужно для работы с массивом точек.
  v8::Persistent<v8::ObjectTemplate> point_array_blueprint_;
};

class PaletteEngine {

};