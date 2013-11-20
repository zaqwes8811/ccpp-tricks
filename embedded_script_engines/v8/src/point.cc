#include "point.h"

using v8::Value;
using v8::Handle;
using v8::Local;
using v8::String;
using v8::External;
using v8::Object;
using v8::Integer;
using v8::PropertyCallbackInfo;

void GetPointX(Local<String> name,
               const PropertyCallbackInfo<Value>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<Point*>(ptr)->x_;

  // New api
  // return Integer::New(value);
  info.GetReturnValue().Set(Integer::New(value));
}
 

void SetPointX(Local<String> property, Local<Value> value,
               const PropertyCallbackInfo<void>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<Point*>(ptr)->x_ = value->Int32Value();
}

void GetPointY(Local<String> name,
               const PropertyCallbackInfo<Value>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<Point*>(ptr)->y_;

  // New api
  // return Integer::New(value);
  info.GetReturnValue().Set(Integer::New(value));
}
 

void SetPointY(Local<String> property, Local<Value> value,
               const PropertyCallbackInfo<void>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<Point*>(ptr)->y_ = value->Int32Value();
}