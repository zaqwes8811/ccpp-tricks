/*#include <v8.h>

Local<Value> AccessorInfo::Data() const {
  return Local<Value>(reinterpret_cast<Value*>(&args_[-2]));
}

Local<Object> AccessorInfo::This() const {
  return Local<Object>(reinterpret_cast<Object*>(&args_[0]));
}

Local<Object> AccessorInfo::Holder() const {
return Local<Object>(reinterpret_cast<Object*>(&args_[-1]));
}
*/