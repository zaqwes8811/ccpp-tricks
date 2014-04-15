#include "v8small_base.h"
//#include <iostream>

namespace scenarios {
v8::Handle<v8::ObjectTemplate> V8SmallBase::CreateBlueprint(v8::Isolate *isolate) {

	HandleScope handle_scope(isolate);
	
  Handle<ObjectTemplate> result = ObjectTemplate::New();
  result->SetInternalFieldCount(1);

  // Connect getter/setter
 // result->SetAccessor(String::New("temp"), GetTemp_, SetTemp_);   
	result->SetAccessor(String::New("idx_oned_etv_"), V8Get_idx_oned_etv_, V8Set_idx_oned_etv_); 
//result->SetAccessor(String::New("var_char"), V8Get_var_char, V8Set_var_char); 
	result->SetAccessor(String::New("ibRadioMode_"), V8Get_ibRadioMode_, V8Set_ibRadioMode_); 
	// Ïåðåìåííûå, "ÑÊÎËÜÊÎ ÂÑÅÃÎ"
	result->SetAccessor(String::New("PABTotal_"), v8_get_PABTotal_, v8_set_PABTotal_);
	result->SetAccessor(String::New("total_bcl_"), v8_get_total_bcl_, v8_set_total_bcl_);
	result->SetAccessor(String::New("excitersTotal_"), v8_get_excitersTotal_, v8_set_excitersTotal_);
	result->SetAccessor(String::New("DBTotal_"), v8_get_DBTotal_, v8_set_DBTotal_);
	result->SetAccessor(String::New("transmitterID___"), v8_get_transmitterID___, v8_set_transmitterID___);
	result->SetAccessor(String::New("terminal_amps_per_block___"), v8_get_terminal_amps_per_block___, v8_set_terminal_amps_per_block___);
	result->SetAccessor(String::New("sizeBlockPreampParams_"), v8_get_sizeBlockPreampParams_, v8_set_sizeBlockPreampParams_);
	result->SetAccessor(String::New("sizeBlockTerminalAmpParams_"), v8_get_sizeBlockTerminalAmpParams_, v8_set_sizeBlockTerminalAmpParams_);
	result->SetAccessor(String::New("sizeBlockBCNParams_"), v8_get_sizeBlockBCNParams_, v8_set_sizeBlockBCNParams_);
	result->SetAccessor(String::New("sizeBlockDBParams_"), v8_get_sizeBlockDBParams_, v8_set_sizeBlockDBParams_);

  return handle_scope.Close(result);  
}
/*
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
*/




}