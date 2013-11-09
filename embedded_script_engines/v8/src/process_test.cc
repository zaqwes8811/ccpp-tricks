// C++
#include <string>
#include <map>

// Other
#include <v8.h>
#include <gtest/gtest.h>

// App
#include "process_classes.h"

// Reads a file into a v8 string.
Handle<String> ReadFile(const string& name) {
  FILE* file = fopen(name.c_str(), "rb");
  if (file == NULL) return Handle<String>();

  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  rewind(file);

  char* chars = new char[size + 1];
  chars[size] = '\0';
  for (int i = 0; i < size;) {
    int read = static_cast<int>(fread(&chars[i], 1, size - i, file));
    i += read;
  }
  fclose(file);
  Handle<String> result = String::New(chars, size);
  delete[] chars;
  return result;
}

void PrintMap(map<string, string>* m) {
  for (map<string, string>::iterator i = m->begin(); i != m->end(); i++) {
    pair<string, string> entry = *i;
    printf("%s: %s\n", entry.first.c_str(), entry.second.c_str());
  }
}

const int kSampleSize = 1;//6;
StringHttpRequest kSampleRequests[kSampleSize] = {
  //StringHttpRequest("/process.cc", "localhost", "google.com", "firefox"),
  StringHttpRequest("/", "localhost", "google.net", "firefox")//,
  //StringHttpRequest("/", "localhost", "google.org", "safari"),
  //StringHttpRequest("/", "localhost", "yahoo.com", "ie"),
  //StringHttpRequest("/", "localhost", "yahoo.com", "safari"),
  //StringHttpRequest("/", "localhost", "yahoo.com", "firefox")
};

bool ProcessEntries(HttpRequestProcessor* processor, int count,
                    StringHttpRequest* reqs) {
  for (int i = 0; i < count; i++) {
    if (!processor->Process(&reqs[i]))
      return false;
  }
  return true;
}

void ParseOptions(int argc,
                  char* argv[],
                  map<string, string>& options,
                  string* file) {
  for (int i = 1; i < argc; i++) {
    string arg = argv[i];
    size_t index = arg.find('=', 0);
    if (index == string::npos) {
      *file = arg;
    } else {
      string key = arg.substr(0, index);
      string value = arg.substr(index+1);
      options[key] = value;
    }
  }
}

TEST(V8, ProcessTop) {
//int main(int argc, char* argv[]) {
  int argc = 2;
  char* argv[] = {"", "test.js"};

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