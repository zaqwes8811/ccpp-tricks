#include "v8small_base.h"
//#include <iostream>

namespace scenarios {
v8::Handle<v8::ObjectTemplate> V8SmallBase::CreateBlueprint(v8::Isolate *isolate) {

		//vamp
		db_ = new SmallBase(10);
		
    HandleScope handle_scope(isolate);
		
    Handle<ObjectTemplate> result = ObjectTemplate::New();
    result->SetInternalFieldCount(1);

    // Connect getter/setter
    result->SetAccessor(String::New("temp"), GetTemp_, SetTemp_);    
  
    return handle_scope.Close(result);  
}

void V8SmallBase::GetTemp_(Local<String> name,
               const PropertyCallbackInfo<Value>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
	int value = static_cast<SmallBase*>(ptr)->temp_;
  info.GetReturnValue().Set(Integer::New(value));
}

void V8SmallBase::SetTemp_(Local<String> property, Local<Value> value,
               const PropertyCallbackInfo<void>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
	static_cast<SmallBase*>(ptr)->temp_ = value->Int32Value();
}
// @DEPR
void V8SmallBase::GetTempConstr_(Local<String> name,
               const PropertyCallbackInfo<Value>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
	int value = static_cast<SmallBase*>(ptr)->temp_;
  info.GetReturnValue().Set(Integer::New(value));
}
// @DEPR
void V8SmallBase::SetTempConstr_(Local<String> property, Local<Value> value,
               const PropertyCallbackInfo<void>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
	static_cast<SmallBase*>(ptr)->temp_ = value->Int32Value();
}


}