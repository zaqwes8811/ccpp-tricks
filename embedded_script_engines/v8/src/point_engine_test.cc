// C++
#include <string>

// Other
#include <gtest/gtest.h>
#include <v8.h>

// App
#include "process.h"
#include "point.h"
#include "point/point_engines.h"

using std::string;

using v8::Isolate;
using v8::String;
using v8::Handle;
using v8::HandleScope;

using v8::Context;
using v8::Persistent;

class PointV8EngineImplWithPersistent : public PointV8Engine {
 public:
  PointV8EngineImplWithPersistent(
    Isolate* isolate, 
    Handle<String> source,
    V8Point* point) 
      : isolate_(isolate), source_(source), v8_point_(point) { }

  virtual void RunWithRealPoint(Point* real_point);
 private:
  Isolate* GetIsolate() { return isolate_; }
  Isolate* isolate_;  // Основным является контекст
  Handle<String> source_;
  // Может и не нужно будет
  V8Point* v8_point_;
  
  // Постоянные!
  // "A context is an execution environment that allows separate, 
  // unrelated, JavaScript code to run in a single instance of 
  // V8. You must explicitly specify the context in which you 
  // want any JavaScript code to be run."
  //
  // При экспонировании похоже не нужно.
  static Persistent<Context> context_;  // Обязательно
  // Blueprints
  static Persistent<ObjectTemplate> point_template_;
};

void PointV8EngineImplWithPersistent::RunWithRealPoint(Point* real_point) {
  HandleScope handle_scope(GetIsolate());

  // Create a template for the global object where we set the
  // built-in global functions.
  Handle<ObjectTemplate> global = ObjectTemplate::New();

  // Expose logger
  global->Set(String::New("log"), 
      FunctionTemplate::New(LogCallback));

  //@Point:
  // Create context?
  // Each processor gets its own context so different processors don't
  // affect each other. Context::New returns a persistent handle which
  // is what we need for the reference to remain after we return from
  // this method. That persistent handle has to be disposed in the
  // destructor.
  v8::Handle<v8::Context> context = 
      Context::New(GetIsolate(), NULL, global);
  context_.Reset(GetIsolate(), context);

  // Enter the new context so all the following operations take place
  // within it.
  Context::Scope context_scope(GetIsolate(), context_);

  //@Point
  // Install
  Handle<Object> output_obj = v8_point_->ForgePoint(
      real_point, 
      GetIsolate(), 
      &point_template_,
      &context_);
  context->Global()->Set(String::New("point_zero"), output_obj);

  //@Point
  // Run Script
  bool success = ExecuteScript(source_, isolate_, &context_);
}

Persistent<Context> PointV8EngineImplWithPersistent::context_;
Persistent<ObjectTemplate> PointV8EngineImplWithPersistent::point_template_;

TEST(PointEngine, Create) {
  v8::V8::InitializeICU();
  string file = "..\\scripts\\point.js";
  EXPECT_NE(true, file.empty());

  Isolate* isolate = Isolate::GetCurrent();

  // Всегда нужно создать - это как бы свой стек для V8
  HandleScope scope(isolate);

  Handle<String> source = ReadFile(file);
  EXPECT_NE(true, source.IsEmpty());

  // Point
  V8Point v8_point;
  Point point_real(1, 2);

  // Engine
  PointV8Engine* engine = new PointV8EngineImplWithPersistent(
      isolate, source, &v8_point);
  engine->RunWithRealPoint(&point_real);

  EXPECT_EQ(199, point_real.x_);
  EXPECT_EQ(42, point_real.y_);

  delete engine;
}
