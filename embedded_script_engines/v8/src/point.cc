#include "point.h"

using v8::Value;
using v8::Handle;
using v8::Local;
using v8::String;
using v8::External;
using v8::Object;
using v8::Integer;
using v8::PropertyCallbackInfo;
using v8::HandleScope;
using v8::Isolate;

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

// Need put env data
//Handle<Object> wrapPoint(Point *pointToWrap, Isolate* isolate) {
    //enter a handle scope
  //  HandleScope handle_scope(isolate);
 
    //create a new point instance
    //Local<Object> point_instance = point_templ->NewInstance();
 
    //set that internal field
    //point_instance->SetInternalField(0, External::New(pointToWrap));
 
    //I'm skipping some Persistent MakeWeak goodness right here
 
    //to prevent the point_instance from being destroyed when its
    //scope handle_scope is, use the Close() function
    //return handle_scope.Close(point_instance);
//}