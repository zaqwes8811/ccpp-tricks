#include "palette.h"

// App
#include "process.h"

v8::Persistent<v8::ObjectTemplate> V8Palette::point_blueprint_;

V8Palette::V8Palette(
    Isolate* isolate,
    Persistent<Context>* context) 
  { 
  // Нужно создать Persistent!
  HandleScope handle_scope(isolate);
  Context::Scope scope(isolate, *context);
  
  // Инициализируем шаблоны
  // Шаблон точки
  if (point_blueprint_.IsEmpty()) {
    Handle<ObjectTemplate> raw_template = 
        V8Point().CreateBlueprint(isolate, context);

    // Сохраняем, но похоже можно и текущим пользоваться
    point_blueprint_.Reset(isolate, raw_template);
  }

  // Шаблон массива

}

v8::Handle<v8::ObjectTemplate> V8Palette::MakeBlueprint(
    v8::Isolate* isolate, 
    v8::Persistent<v8::Context>* context) 
  {
  HandleScope handle_scope(isolate);

  Context::Scope scope(isolate, *context);

  Handle<ObjectTemplate> result = ObjectTemplate::New();
  result->SetInternalFieldCount(1);

  // Connect getter/setter
  result->SetAccessor(String::New("point"), GetPointValue);
  result->SetAccessor(String::New("int_array"), GetIntArrayValue);

  return handle_scope.Close(result);
}

Handle<Object> V8Palette::ForgePalette(
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

void V8Palette::GetPointValue(
    Local<String> name,
    const PropertyCallbackInfo<Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();

  // Возвращает точку!
  Palette* palette = static_cast<Palette*>(ptr);

  // Нужно плучить V8Palette или сделать новый хэндлер
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(), 
      point_blueprint_);
  Handle<Object> instance = templ->NewInstance();

  // Wrap the raw C++ pointer in an External so it can be referenced
  // from within JavaScript.
  Handle<External> point_handle = External::New(&palette->point_);

  // Store the map pointer in the JavaScript wrapper.
  instance->SetInternalField(0, point_handle);

  // Вот как вернуть объект!?
  // Похоже объект не тот!
  info.GetReturnValue().Set<v8::Object>(instance);
}

void V8Palette::GetIntArrayValue(
      Local<String> name,
      const PropertyCallbackInfo<Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();

  // Возвращает точку!
  Palette* palette = static_cast<Palette*>(ptr);

  // Нужно обернуть и вернуть
}

void V8Palette::ArrayIndexSetter(
    uint32_t index,
    Local<Value> value,
    const PropertyCallbackInfo<Value>& info) 
  { 
  if (index < Palette::MAX_SIZE) {
    v8::Local<v8::Object> self = info.Holder();
    Handle<External> field = Handle<External>::Cast(self->GetInternalField(0));
    void* ptr = field->Value();
    int* array_tmp = static_cast<int*>(ptr);
    
    // Как извлечь значение?
    array_tmp[index] = ObjectToInt(value);

    //info.GetReturnValue().Set(v8::Number::New(array_tmp[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void V8Palette::ArrayIndexGetter(
    uint32_t index,
    const PropertyCallbackInfo<Value>& info) 
  {
  
  if (index < Palette::MAX_SIZE) {
    v8::Local<v8::Object> self = info.Holder();
    //info.GetReturnValue().Set(v8::Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}
