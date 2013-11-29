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

class V8Point {
public:
  V8Point() {}

  v8::Handle<v8::ObjectTemplate> CreateBlueprint(
      v8::Isolate* isolate, v8::Persistent<v8::Context>* context);

  static void GetPointX(v8::Local<v8::String> name,
                 const v8::PropertyCallbackInfo<v8::Value>& info);
  static void SetPointX(v8::Local<v8::String> property, v8::Local<v8::Value> value,
                 const v8::PropertyCallbackInfo<void>& info);
  static void GetPointY(v8::Local<v8::String> name,
                 const v8::PropertyCallbackInfo<v8::Value>& info);
  static void SetPointY(
     v8::Local<v8::String> property, 
     v8::Local<v8::Value> value,
     const v8::PropertyCallbackInfo<void>& info);
};