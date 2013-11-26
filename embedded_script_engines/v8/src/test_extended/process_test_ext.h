//#include "config.h"
#include "process_classes.h"

class JsHttpRequestProcessorTestExt : 
    public JsHttpRequestProcessor 
  {
  public:
    JsHttpRequestProcessorTestExt(Isolate* isolate, Handle<v8::String> script) : 
      JsHttpRequestProcessor(isolate, script) { }

};