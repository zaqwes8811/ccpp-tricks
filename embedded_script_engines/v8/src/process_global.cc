#include <v8.h>

#include <string>
#include <map>

// App
#include "process_classes.h"

#ifdef COMPRESS_STARTUP_DATA_BZ2
#error Using compressed startup data is not supported for this sample
#endif

using namespace std;
using namespace v8;



// --- Test ---


void HttpRequestProcessor::Log(const char* event) {
  printf("Logged: %s\n", event);
}

StringHttpRequest::StringHttpRequest(const string& path,
                                     const string& referrer,
                                     const string& host,
                                     const string& user_agent)
    : path_(path),
      referrer_(referrer),
      host_(host),
      user_agent_(user_agent) { }


///@Functions
