//#include "config.h"
#include "v8/src/virtual_machine.h"

namespace scenarios {

void ScriptsV8Impl::runScript(std::string file) {
	
	Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Handle<v8::String> source = ReadFile(file);

	Local<Integer> value = Integer::New(1);
	int out_value = value->ToObject()->Int32Value();
	cout << "value : " << out_value << endl;

}


}
