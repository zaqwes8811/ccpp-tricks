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

