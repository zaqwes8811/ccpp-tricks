#pragma once

#ifndef CC_JS_V8_SCENARIOS
#define CC_JS_V8_SCENARIOS

#include <map>
#include <string>
#include <vector>

// Other
//#include <boost/shared_ptr.hpp>
#include <v8.h>

// App
// #include "in_memory_storage/sampler.h" 
#include "process_classes.h"

using namespace std;
using namespace v8;

namespace scenarios {

class dblite
{
 public:
	bool open(const char* name) { return 0; }
	void close() { }
	bool execute(const char* sql) { return 0; }
	int error_code() { return 3;}

	static dblite* unwrap_dblite(Handle<Object> obj);

	Handle<v8::Value> SomeProperty(Local<v8::String> name, const const PropertyCallbackInfo<void>& info);

	static std::string to_string(Local<Value> v);

	static void Open(const FunctionCallbackInfo<Value>& args);

	v8::Handle<v8::FunctionTemplate> CreateDbLiteTemplate();		


	


};

/*
class ScriptsV8 {
 public:  
	 virtual void runScript(std::string)=0;  
};

class ScriptsV8Impl : public ScriptsV8 {
 public:
	explicit ScriptsV8Impl(
		boost::shared_ptr<::tmitter_web_service::DataBase> database) 
			: db_(database) { }

	virtual void runScript(std::string scriptFile);

	virtual ~ScriptsV8Impl() { }

 private:
	boost::shared_ptr<::tmitter_web_service::DataBase> db_;

};
*/

} // namespace

#endif // CC_JS_V8_SCENARIOS