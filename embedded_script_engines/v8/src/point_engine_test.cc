// C++
#include <string>

// Other
#include <gtest/gtest.h>
#include <v8.h>

// App
#include "process.h"

using std::string;

using v8::Isolate;
using v8::String;
using v8::Handle;
using v8::HandleScope;

class PointV8Engine {
public:
  PointV8Engine(Isolate* isolate, Handle<String> source) :
    isolate_(isolate), source_(source) { }

protected:

private:
  Isolate* isolate_;
  Handle<String> source_;
};

TEST(PointEngine, Create) {
  v8::V8::InitializeICU();
  string file = "..\\scripts\\test_extended.js";
  EXPECT_NE(true, file.empty());

  Isolate* isolate = Isolate::GetCurrent();

  // ¬сегда нужно создать - это как бы свой стек дл€ V8
  HandleScope scope(isolate);

  Handle<String> source = ReadFile(file);
  EXPECT_NE(true, source.IsEmpty());

  // Engine
}