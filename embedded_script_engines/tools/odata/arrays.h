#ifndef ODATA_ARRAYS_H_
#define ODATA_ARRAYS_H_

// Other
#include <v8.h>

class Web {
 public:
  //$ZeroLevelAccessors
  static void ZLGetter_lengthAllParams___(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_counterDebug___(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_stringMsgsQuerySTL(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_LLTypeCodesQuerySTL(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_HLTypeCodesQuerySTL(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_typeControl_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_failsReseted_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_printPABLock_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_printPABLockEvent_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_printPABNoInPower_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_printPABNoInPowerEvent_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_printPABUnlock_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_printPABInPowerOk_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void ZLGetter_currentQueryIndex_(
      v8::Local<String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  //$LastLevelAccessors
  static void LLGetterByIdx_lengthAllParams___(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_counterDebug___(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_stringMsgsQuerySTL(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_LLTypeCodesQuerySTL(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_HLTypeCodesQuerySTL(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_typeControl_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void LLGetterByIdx_failsReseted_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

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

  static void LLGetterByIdx_currentQueryIndex_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info);

};
#endif  // ODATA_ARRAYS_H_