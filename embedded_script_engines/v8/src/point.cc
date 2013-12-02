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
using v8::Context;

using v8::ObjectTemplate;

void V8Point::GetPointX(Local<String> name,
                        const PropertyCallbackInfo<Value>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<Point*>(ptr)->x_;
  info.GetReturnValue().Set(Integer::New(value));
}

void V8Point::SetPointX(Local<String> property, Local<Value> value,
                        const PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<Point*>(ptr)->x_ = value->Int32Value();
}

void V8Point::GetPointY(Local<String> name, 
                        const PropertyCallbackInfo<Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<Point*>(ptr)->y_;
  info.GetReturnValue().Set(Integer::New(value));
}

void V8Point::SetPointY(Local<String> property, Local<Value> value, 
                        const PropertyCallbackInfo<void>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<Point*>(ptr)->y_ = value->Int32Value();
}

v8::Handle<v8::ObjectTemplate> V8Point::CreateBlueprint(
    v8::Isolate* isolate, v8::Persistent<v8::Context>* context) 
  {
  HandleScope handle_scope(isolate);

  Context::Scope scope(isolate, *context);

  Handle<ObjectTemplate> result = ObjectTemplate::New();
  result->SetInternalFieldCount(1);

  // Connect getter/setter
  result->SetAccessor(String::New("x"), GetPointX, SetPointX);
  result->SetAccessor(String::New("y"), GetPointY, SetPointY);
  result->SetAccessor(String::New("internal_point"), GetPointY, SetPointY);

  return handle_scope.Close(result);
}