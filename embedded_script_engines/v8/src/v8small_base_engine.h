#ifndef SOME_DB_SMALL_ENGINE
#define SOME_DB_SMALL_ENGINE
// cpp
#include <string>
#include <iostream>

// other
#include "v8.h"
#include "process.h"

// app
#include "v8small_base.h"
#include "small_base.h"

using namespace v8;
using ::scenarios::SmallBase;
using ::scenarios::V8SmallBase;
using ::std::cout;
using std::endl;

namespace scenarios {



class V8SmallBaseEngine {

 public:
  static V8SmallBaseEngine* CreateForOwn(
      Isolate* isolate, 
      Handle<String> source,
      V8SmallBase* point);
  

 protected:
  V8SmallBaseEngine(
    Isolate* isolate, 
    Handle<String> source,
    V8SmallBase* temp) 
				: isolate_(isolate), source_(source), temp_(temp) { }

	bool Initialize();

	void Log(const char* event);
	bool ExecuteScript(Handle<String> script);
	Handle<Object> WrapVar(SmallBase* obj);
	bool InstallVars(SmallBase* opts, SmallBase* output);

 private:
  Isolate* GetIsolate() { return isolate_; }
  Isolate* isolate_;  // Основным является контекст
  Handle<String> source_;
	SmallBase* smdb_;
  
  // "A context is an execution environment that allows separate, 
  // unrelated, JavaScript code to run in a single instance of 
  // V8. You must explicitly specify the context in which you 
  // want any JavaScript code to be run."
  //
  // При экспонировании похоже не нужно.
  Persistent<Context> context_;

  // Может и не нужно будет
  V8SmallBase* temp_;

  // Blueprints
  static Persistent<ObjectTemplate> point_template_;
};

//Persistent<ObjectTemplate> V8SmallBaseEngine::point_template_;

}

#endif // SOME_DB_SMALL_ENGINE