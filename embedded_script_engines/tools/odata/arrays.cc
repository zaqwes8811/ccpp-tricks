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
      String::New("locks_"), 
      ZLGetter_locks_);
  result->SetAccessor(
      String::New("lock_events_"), 
      ZLGetter_lock_events_);
  result->SetAccessor(
      String::New("no_in_powers_"), 
      ZLGetter_no_in_powers_);
  result->SetAccessor(
      String::New("no_in_power_events_"), 
      ZLGetter_no_in_power_events_);
  result->SetAccessor(
      String::New("unlocks_"), 
      ZLGetter_unlocks_);
  result->SetAccessor(
      String::New("power_is_ok_"), 
      ZLGetter_power_is_ok_);

  return handle_scope.Close(result);
}

Handle<Object> V8DataBase::New(DataBase* database, v8::Isolate *isolate) {
  HandleScope handle_scope(isolate);
  Context::Scope scope(isolate->GetCurrentContext());

  Handle<ObjectTemplate> raw_template = 
      CreateOwnBlueprint(isolate);    

  Handle<ObjectTemplate> templ =
      Local<ObjectTemplate>::New(isolate, raw_template);

  Handle<Object> result = templ->NewInstance();
  Handle<External> map_ptr = External::New(database);

  result->SetInternalField(0, map_ptr);
  return handle_scope.Close(result);
}

//$LastLevelGetters
void V8DataBase::LLGetterByIdx_locks_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLGetterByIdx_lock_events_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLGetterByIdx_no_in_powers_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLGetterByIdx_no_in_power_events_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLGetterByIdx_unlocks_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLGetterByIdx_power_is_ok_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

//$LastLevelSetters
void V8DataBase::LLSetterByIdx_locks_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLSetterByIdx_lock_events_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLSetterByIdx_no_in_powers_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLSetterByIdx_no_in_power_events_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLSetterByIdx_unlocks_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8DataBase::LLSetterByIdx_power_is_ok_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

//$ZeroLevelGetters
void V8DataBase::ZLGetter_locks_(
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
          LLGetterByIdx_locks_,
          LLSetterByIdx_locks_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->locks_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void V8DataBase::ZLGetter_lock_events_(
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
          LLGetterByIdx_lock_events_,
          LLSetterByIdx_lock_events_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->lock_events_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void V8DataBase::ZLGetter_no_in_powers_(
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
          LLGetterByIdx_no_in_powers_,
          LLSetterByIdx_no_in_powers_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->no_in_powers_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void V8DataBase::ZLGetter_no_in_power_events_(
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
          LLGetterByIdx_no_in_power_events_,
          LLSetterByIdx_no_in_power_events_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->no_in_power_events_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void V8DataBase::ZLGetter_unlocks_(
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
          LLGetterByIdx_unlocks_,
          LLSetterByIdx_unlocks_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->unlocks_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void V8DataBase::ZLGetter_power_is_ok_(
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
          LLGetterByIdx_power_is_ok_,
          LLSetterByIdx_power_is_ok_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->power_is_ok_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}
