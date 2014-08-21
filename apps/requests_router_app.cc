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
    // DANGER: Data Races
    if (obj_)
      doSome(obj_);
    
  }
  
private:
  const hash_map<string, Action> call_table_;
  SomeClass* const obj_;  // DANGER: это реальная не контроллируемая проблема
}

// Threads
// "Goal - no raw ptrs, and not raw sync primitives."
string server_fun(SomeClass* obj) 
{
  // Befor - нужно каждый раз вызывать
  // проблема разрушения объекта на который ссылаемся присутствет!
  RequestHanders handler(obj);  
  
  // After Try
  // Lazy
  static RequestHanders handler(obj);
  
  // After Try
  std::call_once;
  
  // After Try
  // If use lock
  
  // After Try
  // shared_ptr and weak_ptr
  //http://mydov.blogspot.ru/2012/10/weakptr-lock-is-thread-safe.html
  
  // After Try
  // Нельзя захватить объект умным указателем - например топовый класс MFC
  // Или объект вообще стековый.
  
  // After Try
  // Fork/Join - разрушать только когда используемые потоки объединились.
}