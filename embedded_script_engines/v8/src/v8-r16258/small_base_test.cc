// C++
#include <string>
#include <iostream>

// Other
#include <gtest/gtest.h>
#include <v8.h>

// App
#include "process.h"
#include "small_base.h"
#include "v8small_base.h"
#include "v8small_base_engine.h"
//#include "app-server-linux/in_memory_storage/emitter/emitter.h"
#include "in-memory-storages/linux_version/abstract_in_memory_storage.h"
#include "in-memory-storages/linux_version/sampler.h" 
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
using ::in_memory_storages::InMemoryStorage;
//using ::emitter::EmitterImpl;
typedef ::tmitter_web_service::InMemoryStorageImpl DataBase;

using ::tmitter_web_service::InMemoryStorageImpl;
typedef ::tmitter_web_service::InMemoryStorageImpl EmitterImpl;
TEST(SmallBaseEngine, Create) {
  v8::V8::InitializeICU();
  //string file = "..\\scripts\\test_extended.js";
	string file = "..\\scripts\\script_small_base_engine_test.js";
  EXPECT_NE(true, file.empty());
	//SmallBase* database = new SmallBase(0);
	//DataBase* database = new DataBase();
	InMemoryStorageImpl database;
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

		isolate, source, &database, &v8_smalldb);

	StringHttpRequest request("/", "localhost", "google.net", "firefox");

	//EXPECT_NE(true, engine->Process(NULL));
	engine->Process();
	engine->Process();

//	DataBase database;
	
	EmitterImpl emitter(database);
	//emitter.emitCfg();
	//emitter.emitAll();

	ASSERT_NO_THROW(emitter.emitConfiguration());	
	
	ASSERT_NO_THROW(emitter.emitAllParams());
	//std::cout << database->PABTotal_ << std::endl;
	/*database.total_bcl_ = 4;
	database.excitersTotal_ = 3;
	database.DBTotal_ = 2;
	database.transmitterID___ = 4;
	database.terminal_amps_per_block___=2;
	database.sizeBlockPreampParams_ = 2;
	database.sizeBlockTerminalAmpParams_ = 3;
	database.sizeBlockBCNParams_ = 3;
	database.sizeBlockDBParams_ = 2;	
	database.sizeBlockModParams_ = 2;*/
	

  delete engine;
}