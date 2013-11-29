#pragma once

// Other
#include "v8.h"

// App
#include "point.h"

class PointV8Engine {
 public:
  virtual ~PointV8Engine() {}
  virtual void RunWithRealPoint(Point* real_point) = 0;
};
