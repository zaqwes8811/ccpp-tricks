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

using v8::Context;
using v8::Persistent;

class PointV8Engine {
 public:
  static PointV8Engine* CreateForOwn(Isolate* isolate, Handle<String> source) {
    PointV8Engine* engine = new PointV8Engine(isolate, source);
    engine->Initialize();
    return engine;
  }
  

 protected:
  PointV8Engine(Isolate* isolate, Handle<String> source) :
    isolate_(isolate), source_(source) { }

  void Initialize() {
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
    Context::Scope context_scope(context);

    //@Point
    {
      HandleScope handle_scope(GetIsolate());
    }
  }

 private:
  Isolate* GetIsolate() { return isolate_; }
  Isolate* isolate_;  // Основным является контекст
  Handle<String> source_;
  
  // "A context is an execution environment that allows separate, 
  // unrelated, JavaScript code to run in a single instance of 
  // V8. You must explicitly specify the context in which you 
  // want any JavaScript code to be run."
  //
  // При экспонировании похоже не нужно.
  Persistent<Context> context_;
};

TEST(PointEngine, Create) {
  v8::V8::InitializeICU();
  string file = "..\\scripts\\test_extended.js";
  EXPECT_NE(true, file.empty());

  Isolate* isolate = Isolate::GetCurrent();

  // Всегда нужно создать - это как бы свой стек для V8
  HandleScope scope(isolate);

  Handle<String> source = ReadFile(file);
  EXPECT_NE(true, source.IsEmpty());

  // Engine
  PointV8Engine* engine = PointV8Engine::CreateForOwn(isolate, source);

  delete engine;
}