// C++
#include <string>
#include <map>

// Other
#include <v8.h>
#include <gtest/gtest.h>

// App
#include "process_classes.h"
#include "point.h"


TEST(V8, ProcessTop) {
  const int kSampleSize = 6;
  StringHttpRequest kSampleRequests[kSampleSize] = {
    StringHttpRequest("/process.cc", "localhost", "google.com", "firefox"),
    StringHttpRequest("/", "localhost", "google.net", "firefox"),
    StringHttpRequest("/", "localhost", "google.org", "safari"),
    StringHttpRequest("/", "localhost", "yahoo.com", "ie"),
    StringHttpRequest("/", "localhost", "yahoo.com", "safari"),
    StringHttpRequest("/", "localhost", "yahoo.com", "firefox")
  };
  int argc = 2;
  char* argv[] = {"", "..\\scripts\\count-hosts.js"};

  v8::V8::InitializeICU();
  map<string, string> options;
  string file;
  ParseOptions(argc, argv, options, &file);
  EXPECT_NE(true, file.empty());

  //> V8
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Handle<String> source = ReadFile(file);
  EXPECT_NE(true, source.IsEmpty());

  //> Own
  JsHttpRequestProcessor processor(isolate, source);
  
  map<string, string> output;
  EXPECT_EQ(true, processor.Initialize(&options, &output));
  EXPECT_EQ(true, ProcessEntries(&processor, kSampleSize, kSampleRequests));
  PrintMap(&output);
}


TEST(V8, ProcessTopOne) {
  const int kSampleSize = 1;
  StringHttpRequest kSampleRequests[kSampleSize] = {
    StringHttpRequest("/process.cc", "localhost", "google.com", "firefox")
  };
  int argc = 2;
  char* argv[] = {"", "..\\scripts\\count-hosts.js"};

  v8::V8::InitializeICU();
  map<string, string> options;
  string file;
  ParseOptions(argc, argv, options, &file);
  EXPECT_NE(true, file.empty());

  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Handle<String> source = ReadFile(file);
  EXPECT_NE(true, source.IsEmpty());

  //> Own
  JsHttpRequestProcessor processor(isolate, source);
  
  // Похоже передаем объект для заполнения
  map<string, string> output;
  EXPECT_EQ(true, processor.Initialize(&options, &output));
  EXPECT_EQ(true, ProcessEntries(&processor, kSampleSize, kSampleRequests));
  PrintMap(&output);
}

TEST(V8, ProcessOne) {
  int argc = 2;
  char* argv[] = {"", "..\\scripts\\test.js"};

  v8::V8::InitializeICU();
  map<string, string> options;

  string file;
  ParseOptions(argc, argv, options, &file);
  EXPECT_NE(true, file.empty());

  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Handle<String> source = ReadFile(file);
  EXPECT_NE(true, source.IsEmpty());

  JsHttpRequestProcessor processor(isolate, source);
  
  map<string, string> output;
  EXPECT_EQ(true, processor.Initialize(&options, &output));

  StringHttpRequest request("/", "localhost", "google.net", "firefox");

  EXPECT_EQ(true, processor.Process(&request));
  PrintMap(&output);
}

// This function returns a new array with three elements, x, y, and z.
Handle<Array> NewPointArray(int x, int y, int z) {
  // Get the default Isolate created at startup.
  Isolate* isolate = Isolate::GetCurrent();

  // Create a stack-allocated handle scope.
  // Create handle STACK!!
  HandleScope handle_scope(isolate);

  // Create a new context. Локальный!
  Handle<Context> context = Context::New(isolate);
  
  // Enter the created context for compiling and
  // running the hello world script. 
  // Создать нужно обязательно.
  Context::Scope context_scope(context);

  // Create a new empty array.
  // FAIL!!!
  // http://stackoverflow.com/questions/7015068/why-does-creating-new-v8array-before-v8scope-cause-segmentation-fault-but-v?rq=1
  //Handle<Array> array = Array::New(3);
  Local<Array> array = Array::New(3);

  // Return an empty result if there was an error creating the array.
  if (array.IsEmpty())
    return Handle<Array>();

  // Fill out the values
  array->Set(0, Integer::New(x));
  array->Set(1, Integer::New(y));
  array->Set(2, Integer::New(z));

  // Return the value through Close.
  return handle_scope.Close(array);
}

TEST(V8, ReturnArray) {
  // Get the default Isolate created at startup.
  Isolate* isolate = Isolate::GetCurrent();

  // Create a stack-allocated handle scope.
  // Create handle STACK!!
  HandleScope handle_scope(isolate);

  /// "!! You must explicitly specify the context 
  //    in which you want any JavaScript code to be run."

  // Create a new context. Локальный!
  Handle<Context> context = Context::New(isolate);
  
  /// !!Enter!! the created context for compiling and
  // running the hello world script. 
  // Создать нужно обязательно.
  Context::Scope context_scope(context);

  Handle<Array> array = NewPointArray(0, 1, 2);

  Local<Value> value = array->Get(0);
  int out_value = value->ToObject()->Int32Value ();
  ASSERT_EQ(0, out_value);
}

TEST(V8, ReturnArrayUnroll) {
// Get the default Isolate created at startup.
  Isolate* isolate = Isolate::GetCurrent();

  // Create a stack-allocated handle scope.
  // Create handle STACK!!
  HandleScope handle_scope(isolate);

  // Create a new context. Локальный!
  Handle<Context> context = Context::New(isolate);
  
  // Enter the created context for compiling and
  // running the hello world script. 
  // Создать нужно обязательно.
  Context::Scope context_scope(context);

  Local<Array> array = Array::New(3);

  // Return an empty result if there was an error creating the array.
  ASSERT_NE(true, array.IsEmpty());

  array->Set(0, Integer::New(1));
  array->Set(1, Integer::New(2));
  array->Set(2, Integer::New(3));

  Local<Value> value = array->Get(0);
  int out_value = value->ToObject()->Int32Value();
	std::cout << "out value : " <<out_value << endl;
  ASSERT_EQ(1, out_value);
}

TEST(V8, HelloWorld) {
  // Get the default Isolate created at startup.
  Isolate* isolate = Isolate::GetCurrent();

  // Create a stack-allocated handle scope.
  HandleScope handle_scope(isolate);

  // Create a new context.
  Handle<Context> context = Context::New(isolate);

  // Here's how you could create a Persistent handle to the context, if needed.
  Persistent<Context> persistent_context(isolate, context);
  
  // Enter the created context for compiling and
  // running the hello world script. 
  Context::Scope context_scope(context);

  // Create a string containing the JavaScript source code.
  Handle<String> source = String::New("'Hello' + ', World!'");

  // Compile the source code.
  Handle<Script> script = Script::Compile(source);
  
  // Run the script to get the result.
  Handle<Value> result = script->Run();
  
  // The persistent handle needs to be eventually disposed.
  persistent_context.Dispose();

  // Convert the result to an ASCII string and print it.
  String::AsciiValue ascii(result);
  printf("%s\n", *ascii);
}

TEST(V8, RunFreeFuncFromJS) {
  // Get the default Isolate created at startup.
  Isolate* isolate = Isolate::GetCurrent();

  // Create a handle scope to hold the temporary references.
  HandleScope handle_scope(isolate);

  // Create a template for the global object where we set the
  // built-in global functions.
  Handle<ObjectTemplate> global = ObjectTemplate::New();
  global->Set(String::New("log"), FunctionTemplate::New(LogCallback));

  // Each processor gets its own context so different processors don't
  // affect each other. Context::New returns a persistent handle which
  // is what we need for the reference to remain after we return from
  // this method. That persistent handle has to be disposed in the
  // destructor.
  v8::Handle<v8::Context> context = Context::New(isolate, NULL, global);

  // Enter the new context so all the following operations take place
  // within it.
  Context::Scope context_scope(context);

  // Можно запускать скрипт
  string file = "..\\scripts\\free_fuc_call_test.js";

  Handle<String> source = ReadFile(file);
  EXPECT_NE(true, source.IsEmpty());

  TryCatch try_catch;

  // Compile the script and check for errors.
  Handle<Script> compiled_script = Script::Compile(source);
  if (compiled_script.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    ::HttpRequestProcessor::Log(*error);
    // The script failed to compile; bail out.
    return;
  }

  // Run the script!
  Handle<Value> result = compiled_script->Run();
  if (result.IsEmpty()) {
    // The TryCatch above is still in effect and will have caught the error.
    String::Utf8Value error(try_catch.Exception());
    ::HttpRequestProcessor::Log(*error);
    // Running the script failed; bail out.
    return;
  }
}

int x = 0;
void XGetter(Local<String> property, 
             const PropertyCallbackInfo<Value>& info) {
  info.GetReturnValue().Set(Integer::New(x));
}
    
void XSetter(Local<String> property, Local<Value> value,
              const PropertyCallbackInfo<void>& info) {
  x = value->Int32Value();
}

TEST(V8, GlobalXetter) {
  // Get the default Isolate created at startup.
  Isolate* isolate = Isolate::GetCurrent();

  // Create a handle scope to hold the temporary references.
  HandleScope handle_scope(isolate);

  // YGetter/YSetter are so similar they are omitted for brevity
  Handle<ObjectTemplate> global_templ = ObjectTemplate::New();
  global_templ->SetAccessor(String::New("x"), XGetter, XSetter);
  global_templ->Set(String::New("loge"), FunctionTemplate::New(LogCallback));	
	
  // Only now create context? Local handle!
  Handle<Context> context = Context::New(isolate, NULL, global_templ);
  Context::Scope context_scope(context);

  // Run
  // Можно запускать скрипт
  string file = "..\\scripts\\free_var_xet_test.js";

  Handle<String> source = ReadFile(file);
  EXPECT_NE(true, source.IsEmpty());

  TryCatch try_catch;

  // Compile the script and check for errors.
  Handle<Script> compiled_script = Script::Compile(source);
  if (compiled_script.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    ::HttpRequestProcessor::Log(*error);
    // The script failed to compile; bail out.
    return;
  }

  // Run the script!
  Handle<Value> result = compiled_script->Run();
  if (result.IsEmpty()) {
    // The TryCatch above is still in effect and will have caught the error.
    String::Utf8Value error(try_catch.Exception());
    ::HttpRequestProcessor::Log(*error);
    // Running the script failed; bail out.
    return;
  }
}



/*
TEST(V8, CallJSFuncReturnArraySlots) {
  // Return Array<Slot>. Slot - u_int/u_char
  EXPECT_EQ(true, false);
}*/

TEST(V8, WrapRequest) {
  int argc = 2;
  char* argv[] = {"", "..\\scripts\\test.js"};

  v8::V8::InitializeICU();
  map<string, string> options;

  string file;
  ParseOptions(argc, argv, options, &file);
  EXPECT_NE(true, file.empty());

  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Handle<String> source = ReadFile(file);
  EXPECT_NE(true, source.IsEmpty());

  JsHttpRequestProcessor processor(isolate, source);

  // Wrap
  // !! Simple in-stack object!

  // FAILED
  //StringHttpRequest request("/", "localhost", "google.net", "firefox");
  //processor.WrapRequest(&request);
}


// http://create.tpsitulsa.com/blog/2009/01/29/v8-objects/
// ! 
TEST(V8, CreateCppObjectInsideJS) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  //create your function template. Why? After use object?
  Handle<FunctionTemplate> point_template = FunctionTemplate::New();
 
  //get the point's instance template
  Handle<ObjectTemplate> point_instance_template = point_template->InstanceTemplate();
 
  //set its internal field count to one (we'll put references to the C++ point here later)
  point_instance_template->SetInternalFieldCount(1);
 
  //add some properties (x and y)
  point_instance_template->SetAccessor(String::New("x"), GetPointX, SetPointX);
  point_instance_template->SetAccessor(String::New("y"), GetPointY, SetPointY);

  // Look like context not used now!
  // Template Created! 
  // "A template is a blueprint for JavaScript functions and objects in a context"
}

// Conect free function to obj in JS. What be with "this".
TEST(V8, ConnectFreeFunctionToObject) {

}

// new in JS https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/new
TEST(V8, AddFunctionToObject) {

}

TEST(V8, IfFieldIsArray) {

}

