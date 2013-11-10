// C++
#include <string>
#include <map>

// Other
#include <v8.h>
#include <gtest/gtest.h>

// App
#include "process_classes.h"


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
  if (file.empty()) {
    fprintf(stderr, "No script was specified.\n");
    return;// 1;
  }

  //> V8
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Handle<String> source = ReadFile(file);
  if (source.IsEmpty()) {
    fprintf(stderr, "Error reading '%s'.\n", file.c_str());
    return;// 1;
  }

  //> Own
  JsHttpRequestProcessor processor(isolate, source);
  
  map<string, string> output;
  if (!processor.Initialize(&options, &output)) {
    fprintf(stderr, "Error initializing processor.\n");
    return;// 1;
  }

  if (!ProcessEntries(&processor, kSampleSize, kSampleRequests))
    return;// 1;
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
  v8::Isolate* isolate = v8::Isolate::GetCurrent();

  // We will be creating temporary handles so we use a handle scope.
  HandleScope handle_scope(isolate);

  // Create a new empty array.
  // FAIL!!!
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
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Handle<Array> array = ::NewPointArray(0, 1, 2);
}