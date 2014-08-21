// 

hash_map<string, Action> init() {
  return ...
}

class RequestHanders 
{
public:
  explicit RequestHanders(SomeClass* obj) : obj_(obj), call_table_(init()) { }
  
  action() {
    // No thread safe
    if (obj_)
      doSome(obj_);
    
  }
  
private:
  const hash_map<string, Action> call_table_;
  SomeClass* const obj_;
}

// Threads
string server_fun(SomeClass* obj) 
{
  // Befor - нужно каждый раз вызывать
  RequestHanders handler(obj);  // проблема разрушения объекта присутствет!
  
  // After Try
  // Lazy
  static RequestHanders handler(obj);
  
  // After Try
  std::call_once;
  
  // After Try
  // shared_ptr and weak_ptr
  //http://mydov.blogspot.ru/2012/10/weakptr-lock-is-thread-safe.html
  
  // After
  // Нельзя захватить объект умным указателем - например топовый класс MFC
  // Или объект вообще стековый.
  
}