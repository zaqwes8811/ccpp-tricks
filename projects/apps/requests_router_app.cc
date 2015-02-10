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
    // DANGER: Data Races - вариант - захватить лог объекта
    // но это тормоза.
    if (obj_)
      doSome(obj_);
    
  }
  
private:
  const hash_map<string, Action> call_table_;
  SomeClass* const obj_;  // DANGER: это реальная не контроллируемая проблема
  
  //weak_ptr<SomeClass> obj_;  // должно быть так
}

// Threads
// "Goal - no raw ptrs, and not raw sync primitives."
// Проблема явной передачи ссылки в тред.
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
  // Но! это работа с кучей. Как быть с локальными стековыми переменными?
  //http://mydov.blogspot.ru/2012/10/weakptr-lock-is-thread-safe.html
  
  // After Try
  // Нельзя захватить объект умным указателем - например топовый класс MFC - там явного майна не было.
  // Или объект вообще стековый.
  
  // After Try
  // Fork/Join - разрушать только когда используемые потоки объединились.
}