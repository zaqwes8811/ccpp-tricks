#ifndef ODATA_ARRAYS_H_
#define ODATA_ARRAYS_H_

// Other
#include <v8.h>

class V8DataBase {
 public:
  //$ZeroLevelAccessors
  static void ZLGetter_printPABLock_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_printPABLockEvent_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_printPABNoInPower_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_printPABNoInPowerEvent_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_printPABUnlock_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_printPABInPowerOk_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  //$LastLevelAccessors
  static void LLGetterByIdx_printPABLock_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_printPABLockEvent_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_printPABNoInPower_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_printPABNoInPowerEvent_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_printPABUnlock_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_printPABInPowerOk_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

};
#endif  // ODATA_ARRAYS_H_