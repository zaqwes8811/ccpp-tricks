#ifndef ODATA_ARRAYS_H_
#define ODATA_ARRAYS_H_

// Other
#include <v8.h>

class Web {
 public:
  //$ZeroLevelAccessors
  static void ZeroLevelGetter_lengthAllParams___(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_counterDebug___(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_stringMsgsQuerySTL(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_LLTypeCodesQuerySTL(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_HLTypeCodesQuerySTL(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_typeControl_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_failsReseted_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_printPABLock_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_printPABLockEvent_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_printPABNoInPower_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_printPABNoInPowerEvent_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_printPABUnlock_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_printPABInPowerOk_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZeroLevelGetter_currentQueryIndex_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  //$LastLevelAccessors
  static void LastLevelGetterByIdx_lengthAllParams___(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_counterDebug___(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_stringMsgsQuerySTL(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_LLTypeCodesQuerySTL(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_HLTypeCodesQuerySTL(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_typeControl_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_failsReseted_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_printPABLock_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_printPABLockEvent_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_printPABNoInPower_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_printPABNoInPowerEvent_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_printPABUnlock_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_printPABInPowerOk_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LastLevelGetterByIdx_currentQueryIndex_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

};
#endif  // ODATA_ARRAYS_H_