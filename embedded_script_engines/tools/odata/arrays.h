#ifndef ODATA_ARRAYS_H_
#define ODATA_ARRAYS_H_

// Other
#include <v8.h>

#include "real_test_file.h"
class V8DataBase {
 public:
  static v8::Handle<v8::ObjectTemplate> CreateOwnBlueprint(
      v8::Isolate* isolate);

  static v8::Handle<v8::Object> New(DataBase* database, v8::Isolate *isolate);

  //$ZeroLevelGetters
  static void ZLGetter_locks_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_lock_events_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_no_in_powers_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_no_in_power_events_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_unlocks_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_power_is_ok_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  //$LastLevelSetters
  static void LLSetterByIdx_locks_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLSetterByIdx_lock_events_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLSetterByIdx_no_in_powers_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLSetterByIdx_no_in_power_events_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLSetterByIdx_unlocks_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLSetterByIdx_power_is_ok_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info);

  //$LastLevelAccessors
  static void LLGetterByIdx_locks_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_lock_events_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_no_in_powers_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_no_in_power_events_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_unlocks_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_power_is_ok_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

};
#endif  // ODATA_ARRAYS_H_