class Point {
  public:
   Point(int x, int y) : x_(x),
        y_(y) { }
   int x_;
   int y_;
   //const int* ptr;  // нужно быть внимательным! Var...name  это только int!
   std::string name_;  // Возможно для V8 нужно еще пребразовывать в const char*

   // пока считает за скаляры
   std::vector<std::string> vector_values;
   Vector values_range;
   //int array[42];  // Replace to vector!!
};

/*
void SetPointY(Local<String> property, Local<Value> value,
               const PropertyCallbackInfo<void>& info) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    static_cast<Point*>(ptr)->y_ = value->Int32Value();
}
*/