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

	static void GetTempConstr_(v8::Local<v8::String> name,
                 const v8::PropertyCallbackInfo<v8::Value>& info);
  static void SetTempConstr_(v8::Local<v8::String> property, v8::Local<v8::Value> value,
                 const v8::PropertyCallbackInfo<void>& info);  
 
 private:
	 SmallBase* db_;

};
}


#endif // SOME_SMALL_DB_TEST

