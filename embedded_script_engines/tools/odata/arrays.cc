#include "arrays.h"
#include "process.h"

using v8::String;
using v8::ObjectTemplate;
using v8::Object;
using v8::HandleScope;
using v8::Handle;
using v8::Local;
using v8::Value;
using v8::External;
using v8::Isolate;
using v8::Number;
using v8::Undefined;

v8::Handle<v8::ObjectTemplate> V8DataBase::CreateOwnBlueprint(
      v8::Isolate* isolate) 
  {
  HandleScope handle_scope(isolate);

  Handle<ObjectTemplate> result = ObjectTemplate::New();
  result->SetInternalFieldCount(1);
  result->SetAccessor(
      String::New("printPABLock_"), 
      ZLGetter_printPABLock_);
  result->SetAccessor(
      String::New("printPABLockEvent_"), 
      ZLGetter_printPABLockEvent_);
  result->SetAccessor(
      String::New("printPABNoInPower_"), 
      ZLGetter_printPABNoInPower_);
  result->SetAccessor(
      String::New("printPABNoInPowerEvent_"), 
      ZLGetter_printPABNoInPowerEvent_);
  result->SetAccessor(
      String::New("printPABUnlock_"), 
      ZLGetter_printPABUnlock_);
  result->SetAccessor(
      String::New("printPABInPowerOk_"), 
      ZLGetter_printPABInPowerOk_);

  return handle_scope.Close(result);
}
//$LastLevelAccessors
void V8DataBase::LLGetterByIdx_printPABLock_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* array = static_cast<bool*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLGetterByIdx_printPABLockEvent_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* array = static_cast<bool*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLGetterByIdx_printPABNoInPower_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* array = static_cast<bool*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLGetterByIdx_printPABNoInPowerEvent_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLGetterByIdx_printPABUnlock_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLGetterByIdx_printPABInPowerOk_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* array = static_cast<bool*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

//$ZeroLevelAccessors
void V8DataBase::ZLGetter_printPABLock_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  DataBase* danger_real_ptr = static_cast<DataBase*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_printPABLock_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->printPABLock_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void V8DataBase::ZLGetter_printPABLockEvent_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  DataBase* danger_real_ptr = static_cast<DataBase*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_printPABLockEvent_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->printPABLockEvent_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void V8DataBase::ZLGetter_printPABNoInPower_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  DataBase* danger_real_ptr = static_cast<DataBase*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_printPABNoInPower_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->printPABNoInPower_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void V8DataBase::ZLGetter_printPABNoInPowerEvent_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  DataBase* danger_real_ptr = static_cast<DataBase*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_printPABNoInPowerEvent_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->printPABNoInPowerEvent_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void V8DataBase::ZLGetter_printPABUnlock_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  DataBase* danger_real_ptr = static_cast<DataBase*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_printPABUnlock_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->printPABUnlock_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void V8DataBase::ZLGetter_printPABInPowerOk_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  DataBase* danger_real_ptr = static_cast<DataBase*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_printPABInPowerOk_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->printPABInPowerOk_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}
