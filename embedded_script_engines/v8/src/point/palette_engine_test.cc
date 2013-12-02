// Other
#include "v8.h"
#include <gtest/gtest.h>

// App
#include "process.h"
#include "palette.h"

class PaletteEngine {
 public:
  PaletteEngine(
    Isolate* isolate,
    Persistent<Context>* context,
    Handle<String> source,
    V8Palette* palette) 
    : isolate_(isolate), context_(context), source_(source), palette_(palette) { 

    HandleScope handle_scope(GetIsolate());
    // Enter the new context so all the following operations take place
    // within it.
    Context::Scope context_scope(GetIsolate(), *context_);

    //@Point
    // Install
    //Handle<Object> output_obj = WrapPoint(real_point);
    //context->Global()->Set(String::New("point_zero"), output_obj);

    //@Point
    // Run Script
    //bool success = ExecuteScript(source_, isolate_);
  }

 private:
  Isolate* GetIsolate() { return isolate_; }
  Isolate* isolate_;  // Основным является контекст
  Handle<String> source_;
  Persistent<Context>* context_;
  V8Palette* palette_;

  // Blueprints
  Persistent<ObjectTemplate> palette_template_;
};

TEST(V8, Palette) {
  /// Isolate and context be injected!
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope handle_scope(isolate);

  // Create a template for the global object where we set the
  // built-in global functions.
  Handle<ObjectTemplate> global = ObjectTemplate::New();
  global->Set(String::New("log"), FunctionTemplate::New(LogCallback));

  v8::Handle<v8::Context> context = Context::New(isolate, NULL, global);
  Persistent<Context> persistent_context(isolate, context);

  ///@Objects
  Palette palette;
  V8Palette v8_palette(&palette, isolate, &persistent_context);

  // Engine
  //PaletteEngine engine(isolate, &persistent_context, , &palette);
}