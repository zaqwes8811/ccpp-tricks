#pragma once

// Other
#include "v8.h"

// App
#include "point.h"

class PointV8Engine {
 public:
   virtual ~PointV8Engine() {}

public:
  virtual void RunWithRealPoint(Point* real_point) = 0;

 protected:
  v8::Isolate* GetIsolate() { return isolate_; }
  v8::Isolate* isolate_;
  virtual v8::Handle<v8::Object> WrapPoint(Point* point) = 0;
};
