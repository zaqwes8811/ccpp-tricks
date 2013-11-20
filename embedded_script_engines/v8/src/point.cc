// 

// Other
#include <v8.h>

using v8::Value;
using v8::Handle;
using v8::Local;
using v8::String;
using v8::External;
using v8::Object;
using v8::Integer;
using v8::PropertyCallbackInfo;

// Accessing to dynamic vars.
// Point x y
class Point {
   public:
    Point(int x, int y) : x_(x), y_(y) { }
    int x_, y_;
  };

void GetPointX(Local<String> name,
               const PropertyCallbackInfo<Value>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<Point*>(ptr)->x_;
  return Integer::New(value);
}
  
void SetPointX(Local<String> property, Local<Value> value,
                const AccessorInfo& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<Point*>(ptr)->x_ = value->Int32Value();
}