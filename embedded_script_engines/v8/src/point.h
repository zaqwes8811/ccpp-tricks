#pragma once 

// Other
#include <v8.h>

// Accessing to dynamic vars.
// Point x y
class Point {
   public:
    Point(int x, int y) : x_(x), y_(y) { }
    int x_, y_;
  };

void GetPointX(v8::Local<v8::String> name,
               const v8::PropertyCallbackInfo<v8::Value>& info);
void SetPointX(v8::Local<v8::String> property, v8::Local<v8::Value> value,
               const v8::PropertyCallbackInfo<v8::Value>& info);
