#include "palette.h"

V8Palette::V8Palette(
    Palette* palette,  
    Isolate* isolate,
    Persistent<Context>* context) : palette_(palette), isolate_(isolate), context_(context) 
  { 
  // Нужно создать Persistent!
  HandleScope handle_scope(isolate_);

  Context::Scope scope(isolate_, *context_);
  if (point_blueprint_.IsEmpty()) {
    V8Point point;
    Handle<ObjectTemplate> raw_template = 
        point.CreateBlueprint(isolate, context_);

    // Сохраняем, но похоже можно и текущим пользоваться
    point_blueprint_.Reset(isolate, raw_template);
  }

  // Создаем объект по шаблону.
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(isolate, point_blueprint_);
  Handle<Object> result = templ->NewInstance();

  // Wrap the raw C++ pointer in an External so it can be referenced
  // from within JavaScript.
  Handle<External> map_ptr = External::New(&this->palette_->point_);

  // Store the map pointer in the JavaScript wrapper.
  result->SetInternalField(0, map_ptr);

  if (point_field_.IsEmpty()) {
    point_field_.Reset(isolate, result);
  }
}

