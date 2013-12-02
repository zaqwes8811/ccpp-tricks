#pragma once

// Other
#include "v8.h"

// App
#include "point.h"

class Palette {
 public:
  static const int MAX_SIZE = 32;
  Palette() {}
  int array_[MAX_SIZE];
  Point point_;
  Point point_array[MAX_SIZE];
};

using namespace v8;

//@NoThreadSafe
class V8Palette {
public:
  // Args:
  //   Похоже должен знать о Isolate and Context.
  //   Или все-таки контекст должен быть свой.
  V8Palette(Isolate* isolate, Persistent<Context>* context);

  // About:
  //   Getters complex objects.
  static void GetPointValue(
      Local<String> name,
      const PropertyCallbackInfo<Value>& info);

  static void GetIntArrayValue(
      Local<String> name,
      const PropertyCallbackInfo<Value>& info);

  static void GetPointsArrayValue(
      Local<String> name,
      const PropertyCallbackInfo<Value>& info);

  // Работа с конечным массивом
  static void ArrayIndexGetter(
      uint32_t index,
      const PropertyCallbackInfo<Value>& info);

  static void ArrayIndexSetter(
      uint32_t index,
      Local<Value> value,
      const PropertyCallbackInfo<Value>& info);

  static void PointArrayIndexGetter(
      uint32_t index,
      const PropertyCallbackInfo<Value>& info);

  static void PointArrayIndexSetter(
      uint32_t index,
      Local<Value> value,
      const PropertyCallbackInfo<Value>& info) 
    {
  
  }

  // Работа с массивом точек.

  // About:
  //   Make this root object.
  Handle<Object> ForgePalette(
      Palette* palette,
      Isolate* isolate, 
      Persistent<Context>* context,
      Persistent<ObjectTemplate>* blueprint);

public:
  // Все что нужно для работы с точкой.
  static v8::Persistent<v8::ObjectTemplate> point_blueprint_;

  // Просто массив int.
  static v8::Persistent<v8::ObjectTemplate> int_array_blueprint_;

  // Массив точек.
  static v8::Persistent<v8::ObjectTemplate> point_array_blueprint_;

//private:  
  // Тоже будит видимым - нужно для композиции.
  v8::Handle<v8::ObjectTemplate> MakeBlueprint(
      v8::Isolate* isolate, 
      v8::Persistent<v8::Context>* context);
};
