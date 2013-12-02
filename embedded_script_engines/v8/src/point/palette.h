#pragma once

// Other
#include "v8.h"

// App
#include "point.h"

class Palette {
 public:
  Palette() {}
  Point point_;
  Point array[32];
};

using namespace v8;

class V8Palette {
public:
  // Args:
  //   Похоже должен знать о Isolate and Context.
  //   Или все-таки контекст должен быть свой.
  V8Palette(
      Palette* palette,  
      Isolate* isolate,
      Persistent<Context>* context);

  static void GetPointX(Local<String> name,
                 const PropertyCallbackInfo<Value>& info) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();

    // Вот как вернуть объект!?
    info.GetReturnValue().Set<v8::Object>(static_cast<V8Palette*>(ptr)->point_field_);
  }

  v8::Handle<v8::ObjectTemplate> MakeBlueprint(
      v8::Isolate* isolate, v8::Persistent<v8::Context>* context) 
    {
    HandleScope handle_scope(isolate);

    Context::Scope scope(isolate, *context);

    Handle<ObjectTemplate> result = ObjectTemplate::New();
    result->SetInternalFieldCount(1);

    // Connect getter/setter
    result->SetAccessor(String::New("point"), GetPointX);

    return handle_scope.Close(result);
  }

  Handle<Object> ForgePalette(
      Palette* palette,
      Isolate* isolate, 
      Persistent<Context>* context,
      Persistent<ObjectTemplate>* blueprint) 
    {
    HandleScope handle_scope(isolate);
    Context::Scope scope(isolate, *context);

    if (blueprint->IsEmpty()) {
      Handle<ObjectTemplate> raw_template = 
          this->MakeBlueprint(isolate, context);

      // Сохраняем, но похоже можно и текущим пользоваться
      blueprint->Reset(isolate, raw_template);
    }

    // Можно оборачивать реальный объект
    // Сперва нужно сделать пустую обертку
    // Create an empty map wrapper.
    Handle<ObjectTemplate> templ =
        Local<ObjectTemplate>::New(isolate, *blueprint);
    Handle<Object> result = templ->NewInstance();

    // Wrap the raw C++ pointer in an External so it can be referenced
    // from within JavaScript.
    Handle<External> map_ptr = External::New(palette);

    // Store the map pointer in the JavaScript wrapper.
    result->SetInternalField(0, map_ptr);
    return handle_scope.Close(result);
  }

//private:
  Isolate* isolate_;
  Persistent<Context>* context_;

  // Real data
  Palette* palette_;

  // Все что нужно для работы с точкой.
  v8::Persistent<v8::ObjectTemplate> point_blueprint_;
  v8::Persistent<v8::Object> point_field_;

  // Все что нужно для работы с массивом точек.
  //v8::Persistent<v8::ObjectTemplate> point_array_blueprint_;
};
