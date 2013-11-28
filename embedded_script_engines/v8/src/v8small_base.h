#ifndef SOME_SMALL_DB_TEST
#define SOME_SMALL_DB_TEST
// cpp
#include <string>

// other
#include "v8.h"

// app
#include "small_base.h"
using ::scenarios::SmallBase;
using namespace v8;
namespace scenarios {
class V8SmallBase {
 public:
	V8SmallBase() {}

  v8::Handle<v8::ObjectTemplate> CreateBlueprint(
      v8::Isolate* isolate);

  static void GetTemp_(v8::Local<v8::String> name,
                 const v8::PropertyCallbackInfo<v8::Value>& info);
  static void SetTemp_(v8::Local<v8::String> property, v8::Local<v8::Value> value,
                 const v8::PropertyCallbackInfo<void>& info); 
	
	static void V8Get_idx_oned_etv_(Local<String> name,
								 const PropertyCallbackInfo<Value>& info) {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		int value = static_cast<SmallBase*>(ptr)->idx_oned_etv_;
		info.GetReturnValue().Set(Integer::New(value));
	}

	static void V8Set_idx_oned_etv_(Local<String> property, Local<Value> value,
								 const PropertyCallbackInfo<void>& info) {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		static_cast<SmallBase*>(ptr)->idx_oned_etv_ = value->Int32Value();
	}

		static void V8Get_var_char(Local<String> name,
								 const PropertyCallbackInfo<Value>& info) {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		unsigned char value = static_cast<SmallBase*>(ptr)->var_char;
		info.GetReturnValue().Set(Integer::New(value));
	}

	static void V8Set_var_char(Local<String> property, Local<Value> value,
								 const PropertyCallbackInfo<void>& info) {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		static_cast<SmallBase*>(ptr)->var_char = value->Int32Value();
	}

	static void V8Get_ibRadioMode_(Local<String> name,
								 const PropertyCallbackInfo<Value>& info) {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		unsigned char value = static_cast<SmallBase*>(ptr)->ibRadioMode_;
		info.GetReturnValue().Set(Integer::New(value));
	}

	static void V8Set_ibRadioMode_(Local<String> property, Local<Value> value,
								 const PropertyCallbackInfo<void>& info) {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		static_cast<SmallBase*>(ptr)->ibRadioMode_ = value->Int32Value();
	}

 
 private:
	 SmallBase* db_;

};
}


#endif // SOME_SMALL_DB_TEST

