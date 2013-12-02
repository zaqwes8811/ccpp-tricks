// C++
#include <string>

// Other
#include <gtest/gtest.h>
#include <v8.h>

// App
#include "process.h"
#include "small_base.h"
#include "v8small_base.h"
#include "v8small_base_engine.h"
// C++
#include <string>

// Other
#include <gtest/gtest.h>
#include <v8.h>

using std::string;

using v8::Isolate;
using v8::String;
using v8::Handle;
using v8::HandleScope;

using v8::Context;
using v8::Persistent;
using std::string;

using v8::Isolate;
using v8::String;
using v8::Handle;
using v8::HandleScope;

using v8::Context;
using v8::Persistent;

using ::scenarios::SmallBase;
using ::scenarios::V8SmallBase;
using ::scenarios::V8SmallBaseEngine;

TEST(SmallBaseEngine, Create) {
  v8::V8::InitializeICU();
  //string file = "..\\scripts\\test_extended.js";
	string file = "..\\scripts\\script_small_base_engine_test.js";
  EXPECT_NE(true, file.empty());
	SmallBase* database = new SmallBase(0);
  Isolate* isolate = Isolate::GetCurrent();

  // ¬сегда нужно создать - это как бы свой стек дл€ V8
  HandleScope scope(isolate);

  Handle<String> source = ReadFile(file);
  EXPECT_NE(true, source.IsEmpty());

  // Point
  V8SmallBase v8_smalldb;
	//Point point;

  // Engine
  V8SmallBaseEngine* engine = V8SmallBaseEngine::CreateForOwn(

		isolate, source, database, &v8_smalldb);

	StringHttpRequest request("/", "localhost", "google.net", "firefox");

	//EXPECT_NE(true, engine->Process(NULL));
	engine->Process();
	engine->Process();
	

  delete engine;
}