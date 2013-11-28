#include "v8small_base_engine.h"

namespace scenarios {

V8SmallBaseEngine* V8SmallBaseEngine::CreateForOwn(
    Isolate* isolate, 
    Handle<String> source,
    V8SmallBase* point) {
  V8SmallBaseEngine* engine = new V8SmallBaseEngine(isolate, source, point);
  engine->Initialize();
  return engine;
}

void V8SmallBaseEngine::Log(const char* event) {
  printf("Logged: %s\n", event);
}

bool V8SmallBaseEngine::InstallVars(SmallBase* database,
																		SmallBase* database_output) {
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


Handle<Object> V8SmallBaseEngine::WrapVar(SmallBase* obj) {
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



// main func
bool V8SmallBaseEngine::Initialize() {
	//vamp
	SmallBase* database = new SmallBase(0); 
	SmallBase* database_output = new SmallBase(0);

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
	cout << "value in C++ to run " << database->temp_ << endl;

	// Run...
	if (!InstallVars(database, database_output))
    return false;

  // Compile and run the script
  if (!ExecuteScript(source_))
    return false;

	// test log
	cout << "value in C++ after run " << database->temp_ << endl;

}


Persistent<ObjectTemplate> V8SmallBaseEngine::point_template_;

}