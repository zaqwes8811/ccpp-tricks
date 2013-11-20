// C++
#include <string>
#include <map>

// Other
#include <v8.h>
#include <gtest/gtest.h>

// App
#include "v8/src/scripts/virtual_machine.h"

TEST(V8, Scenarios) {
	using ::scenarios::ScriptsV8Impl;
	using ::scenarios::ScriptsV8;
	using ::boost::shared_ptr;
	using ::tmitter_web_service::DataBase;
	shared_ptr<DataBase> database(new DataBase);
	shared_ptr<ScriptsV8> scripter(new ScriptsV8Impl(database));
	
	scripter->runScript("");


}