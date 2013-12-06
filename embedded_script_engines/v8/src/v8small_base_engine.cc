#include "v8small_base_engine.h"

namespace scenarios {

V8SmallBaseEngine* V8SmallBaseEngine::CreateForOwn(
    Isolate* isolate, 
    Handle<String> source,
		::tmitter_web_service::DataBase* database,
    V8SmallBase* v8_database) {
  V8SmallBaseEngine* engine = new V8SmallBaseEngine(isolate, source, database, v8_database);
  engine->Initialize();
	
  return engine;
}

void V8SmallBaseEngine::Log(const char* event) {
  printf("Logged: %s\n", event);
}

bool V8SmallBaseEngine::InstallVars(::tmitter_web_service::DataBase* database,
																		::tmitter_web_service::DataBase* database_output) {
  HandleScope handle_scope(GetIsolate());

  // Wrap the map object in a JavaScript wrapper
  Handle<Object> database_obj = WrapVar(database);

  v8::Local<v8::Context> context =
      v8::Local<v8::Context>::New(GetIsolate(), context_);

  // Set the options object as a property on the global object.
  context->Global()->Set(String::New("database"), database_obj);

  // ! Нужно получить новую форму для объекта
  Handle<Object> output_obj = WrapVar(database_output);
  context->Global()->Set(String::New("database_output"), output_obj);

  return true;
}


Handle<Object> V8SmallBaseEngine::WrapVar(::tmitter_web_service::DataBase* obj) {
  // Handle scope for temporary handles.
  HandleScope handle_scope(GetIsolate());

  // Fetch the template for creating JavaScript map wrappers.
  // It only has to be created once, which we do on demand.
	if (point_template_.IsEmpty()) {
    // lazy!
    Handle<ObjectTemplate> raw_template = temp_->CreateBlueprint(GetIsolate());
    point_template_.Reset(GetIsolate(), raw_template);
  }
  Handle<ObjectTemplate> templ =
      Local<ObjectTemplate>::New(GetIsolate(), point_template_);

  // Create an empty map wrapper.
  Handle<Object> result = templ->NewInstance();

  // Wrap the raw C++ pointer in an External so it can be referenced
  // from within JavaScript.
  Handle<External> map_ptr = External::New(obj);

  // Store the map pointer in the JavaScript wrapper.
  result->SetInternalField(0, map_ptr);

  // Return the result through the current handle scope.  Since each
  // of these handles will go away when the handle scope is deleted
  // we need to call Close to let one, the result, escape into the
  // outer handle scope.
  return handle_scope.Close(result);
}



bool V8SmallBaseEngine::ExecuteScript(Handle<String> script) {
  HandleScope handle_scope(GetIsolate());

  // We're just about to compile the script; set up an error handler to
  // catch any exceptions the script might throw.
  TryCatch try_catch;

  // Compile the script and check for errors.
  Handle<Script> compiled_script = Script::Compile(script);
  if (compiled_script.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    Log(*error);
    // The script failed to compile; bail out.
    return false;
  }

  // Run the script!
  Handle<Value> result = compiled_script->Run();
  if (result.IsEmpty()) {
    // The TryCatch above is still in effect and will have caught the error.
    String::Utf8Value error(try_catch.Exception());
    Log(*error);
    // Running the script failed; bail out.
    return false;
  }
  return true;
}
//vamp
Handle<ObjectTemplate> V8SmallBaseEngine::MakeRequestTemplate(
    Isolate* isolate) {
  HandleScope handle_scope(isolate);

  Handle<ObjectTemplate> result = ObjectTemplate::New();
  result->SetInternalFieldCount(1);

  // Add accessors for each of the fields of the request.
  //result->SetAccessor(String::NewSymbol("path"), GetPath);
  //result->SetAccessor(String::NewSymbol("referrer"), GetReferrer);
  //result->SetAccessor(String::NewSymbol("host"), GetHost);
  //result->SetAccessor(String::NewSymbol("userAgent"), GetUserAgent);

  // Again, return the result through the current handle scope.
  return handle_scope.Close(result);
}
Handle<Object> V8SmallBaseEngine::WrapRequest() {
  // Handle scope for temporary handles.
  HandleScope handle_scope(GetIsolate());

  // Fetch the template for creating JavaScript http request wrappers.
  // It only has to be created once, which we do on demand.
  if (request_template_.IsEmpty()) {
    Handle<ObjectTemplate> raw_template = MakeRequestTemplate(GetIsolate());
    request_template_.Reset(GetIsolate(), raw_template);
  }
  Handle<ObjectTemplate> templ =
      Local<ObjectTemplate>::New(GetIsolate(), request_template_);

  // Create an empty http request wrapper.
  Handle<Object> result = templ->NewInstance();
	//std::string requestt = " ";
	//std::string* request = request;

  // Wrap the raw C++ pointer in an External so it can be referenced
  // from within JavaScript.
  // "JS not handle!"
  //Handle<External> request_ptr = External::New(request);

  // Store the request pointer in the JavaScript wrapper.
//  result->SetInternalField(0, request_ptr);

  // Return the result through the current handle scope.  Since each
  // of these handles will go away when the handle scope is deleted
  // we need to call Close to let one, the result, escape into the
  // outer handle scope.
  return handle_scope.Close(result);
}


bool V8SmallBaseEngine::Process() {
  // Create a handle scope to keep the temporary object references.
  HandleScope handle_scope(GetIsolate());

  v8::Local<v8::Context> context =
      v8::Local<v8::Context>::New(GetIsolate(), context_);

  // Enter this processor's context so all the remaining operations
  // take place there
  Context::Scope context_scope(context);

  // Wrap the C++ request object in a JavaScript wrapper
	Handle<Object> request_obj = WrapRequest();

  // Set up an exception handler before calling the Process function
  TryCatch try_catch;

  // TOTH: in JavaScript function may be connected to exist objects
  // Invoke the process function, giving the global object as !!'this'!!
  // and one argument, the request.
  const int argc = 1;
  Handle<Value> argv[argc] = { request_obj };
  v8::Local<v8::Function> process =
      v8::Local<v8::Function>::New(GetIsolate(), process_);
  Handle<Value> result = process->Call(context->Global(), argc, argv);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    Log(*error);
    return false;
  } else {
    return true;
  }	
}

// main func
bool V8SmallBaseEngine::Initialize() {
	//vamp
	
	::tmitter_web_service::DataBase* database_output = new ::tmitter_web_service::DataBase();

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
	
	// test log
	//cout << "value in C++ to run " << database_->temp_ << endl;

	// Run...
	if (!InstallVars(database_, database_output))
    return false;

  // Compile and run the script
  if (!ExecuteScript(source_))
    return false;

	// test log
//	cout << "value in C++ after run " << database_->temp_ << endl;

	Handle<String> process_name = String::New("Process");

	Handle<Value> process_val = context->Global()->Get(process_name);

	if (!process_val->IsFunction()) return false;

	Handle<Function> process_fun = Handle<Function>::Cast(process_val);

//	Process();

	process_.Reset(GetIsolate(), process_fun);



}

Persistent<ObjectTemplate> V8SmallBaseEngine::request_template_;
Persistent<ObjectTemplate> V8SmallBaseEngine::point_template_;

}