v8::Handle<v8::ObjectTemplate> CreateBlueprint(
      v8::Isolate* isolate) 
  {
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
void V8IMS::LLGetterByIdx_printPABLock_(
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

void V8IMS::LLGetterByIdx_printPABLockEvent_(
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

void V8IMS::LLGetterByIdx_printPABNoInPower_(
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

void V8IMS::LLGetterByIdx_printPABNoInPowerEvent_(
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

void V8IMS::LLGetterByIdx_printPABUnlock_(
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

void V8IMS::LLGetterByIdx_printPABInPowerOk_(
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
