#include "v8small_base.h"
//#include <iostream>

namespace scenarios {
v8::Handle<v8::ObjectTemplate> V8SmallBase::CreateBlueprint(v8::Isolate *isolate) {

		HandleScope handle_scope(isolate);
		
    Handle<ObjectTemplate> result = ObjectTemplate::New();
    result->SetInternalFieldCount(1);

    // Connect getter/setter
    result->SetAccessor(String::New("temp"), GetTemp_, SetTemp_);   
		result->SetAccessor(String::New("idx_oned_etv_"), V8Get_idx_oned_etv_, V8Set_idx_oned_etv_); 
		result->SetAccessor(String::New("var_char"), V8Get_var_char, V8Set_var_char); 
		result->SetAccessor(String::New("ibRadioMode_"), V8Get_ibRadioMode_, V8Set_ibRadioMode_); 

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





}