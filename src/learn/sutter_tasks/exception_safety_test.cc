

/// New tasks - p. 81
// безопасность искл. - часть проектирования
//
// Troubles:
//   - Resources
//   - Consistency - Invariants
//
// Guards, transactions
//
// !!!Error handling strategy - это самое важное!!! Это не деталь реализации
//   Сообщения об ошибках, Распространение ошибок, Обработка
// Важно то что обработчик должен иметь достаточно информации - например пользователь
//
// "...обрабатывает сам и остается в согласованном состоянии..."
// Интересно сделано. Классы исключения включены в интерфейс класса, как внутр. классы
//
// Try/Catch - обработка ошибок, преобразование искл., перехват на границе системы
//
// Warranty
// - Basic - нет утечек и объекты в согл., но возможно непредсказуемом состоянии
// - Strong - обеспечивает семантику транзакций
// - Nofail - бессбойность - destructors, resource free, swap
//TODO: Когда какую? Минимально строгую, в которой не нуждается вызывающий код. - don't understood...
//
// Methods
// - RAII
// - Работа на стороне, а затем обмен - транзакционное программирование
// - Одна функция - одно действие


#include <stdexcept>
#include <algorithm>

#include <gtest/gtest.h>

using std::logic_error;

class Session {
public:
  // Inner class:
  // http://bytes.com/topic/c/answers/133914-static-nested-class
  // http://stackoverflow.com/questions/3846696/nested-classes-c-static-inner-methods-xml-parsing-and-trying-to-populate-vect
  //
  // Inh.:
  // http://stackoverflow.com/questions/15777635/c-calling-base-class-constructors
  /*static*/ class OpenFailed : public logic_error {
  public:
    OpenFailed() : logic_error("") {

    }
  };

  // Throws: OpenFailed
  void Open() {
  }
};


TEST(Sutter, ExceptionBase) {
  Session::OpenFailed error();

}

// safe stack
// Требования к Т довольно строгие.
//   - ..
//   - Безопасное присваивание - ?
//   - конструктор по умолчанию
//TODO: снизить требование
template<class T> class Stack
{
public:
  Stack();
  ~Stack();

  // Step 3
  Stack(const Stack&);
  Stack& operator=(const Stack&);
  T* NewCopy(const T* src, size_t srcsize, size_t destsize);

  // Step 4
  size_t Count() const;
  void Push(const T&);
  // решают две задачи
  T Pop_nosafe();  // if empty throw
  void Pop_better_but(T& result);
  // safe
  T& Top();  //TODO: const?
  void Pop();

private:
  T* v_;
  size_t vsize_;
  size_t vused_;  // количество реально исп. объектов
};
template<class T>
Stack<T>::Stack() :
    v_(/*0 step 2*/new T[10]),
    vsize_(10),
    vused_(0) {
  //v_ = new T[vsize_];  // Step 2: лучше передать в списке иниц. Мишко похожее говорил в GTechTalk
  // T::T() may throw
}
template<class T>
Stack<T>::~Stack() {
  delete [] v_;
  // T::~T() // throw()  // must be!!
}

// Step 3
template<class T>
T* Stack<T>::NewCopy(const T* src, size_t srcsize, size_t destsize) {
  using std::copy;
  assert(destsize >= srcsize);
  T* dest = new T[destsize];
  try {
    copy(src, src+srcsize, dest);  //DANGER: used =,  не ясно в чем проблема, но она есть
  } catch (...) {
    delete [] dest;
    throw;
  }
  return dest;
}

// Step 3: neutral
template<class T>
Stack<T>::Stack(const Stack<T>& other) :
  v_(NewCopy(other.v_,
             other.vsize_,
             other.vsize_)),  // strange
  vsize_(other.vsize_),
  vused_(other.vused_) {
}

// Step 3: assign
template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
  if (this != &other) {
      // may throw
      T* v_new = NewCopy(other.v_, other.vsize_, other.vsize_);

      // must not throw - change state object
      delete [] v_;
      v_ = v_new;
      vsize_ = other.vsize_;
      vused_ = other.vused_;
  }
  return *this;
}

// Step 4
template<class T>
size_t Stack<T>::Count() const  { return vused_; }

template<class T>
void Stack<T>::Push(const T& t) {
  if (vused_ == vsize_) {
    // нужно увеличить память
    // may throw - isolated code
    size_t vsize_new = vsize_*2+1;
    T* v_new = NewCopy(v_, vsize_, vsize_new);

    // no throw
    delete[] v_;
    v_ = v_new;
    vsize_ = vsize_new;
  }
  v_[vused_] = t;  //DANGER: if throw - then no Strong Warr.
    // Итераторы станут не действ.
  ++vused_;  // pointer to next
}

// Step 5
// bad pop
// Проблема не в функции, а в том что такая реализация
// заставляет клиента писать небезопасный код.
//
// !! Функции мутаторы не должны возвр. по значению!!
template<class T>
T Stack<T>::Pop_nosafe() {
  if (vused_ == 0) {
    throw "if empty";
  } else {
    T result = v_[vused_];
    --vused_;
    return result;  // при копировании может возн. искл.
    // объект не дошел до плучателя, а состояние уже изменили
  }
}

template<class T>
void Stack<T>::Pop_better_but(T& result) {
  if (vused_ == 0) {
    throw "if empty";
  } else {
    result = v_[vused_];  // сперва снимаем значение
    --vused_;
    //return result;  // при копировании может возн. искл.
    // объект не дошел до плучателя, а состояние уже изменили
  }
}

template<class T>
T& Stack<T>::Top() {
  if (vused_ == 0) {
    throw "if empty";
  } else {
    return v_[vused_];
  }
}

template<class T>
void Stack<T>::Pop() {
  if (vused_ == 0) {
    throw "if empty";
  } else {
    --vused_;
  }
}

namespace util {
template<class T1, class T2>
void construct(T* p, const T2& value) {
  new (p) T1(value);
}

template<class T>
void destroy(T* t) {
  t->~T();
}

template<class FwdIter>
void destroy(FwdIter first, FwdIter last) {
  while(first != last) {
      destroy(&*first);
      ++first;
  }
}
}

/// Updated Stack - step 6:
template<class T>
class StackImpl {
/*?*/  // protected - if inh. public - member
protected:
  StackImpl(size_t size=0);
  ~StackImpl();
  void Swap(StackImpl& other) throw();  // nothrow!! very important
  T* v_;
  size_t vsize_;
  size_t vused_;

private:
  StackImpl(const StackImpl&);
  StackImpl& operator=(const StackImpl&);

};

template<class T>
StackImpl<T>::StackImpl(size_t size)
  : v_(static_cast<T*>
  (size == 0
      ? 0
  : operator new(sizeof(T)*size))),
       vsize_(size),
       vused_(0) {
}

template<class T>
StackImpl<T>::~StackImpl() {
  using util::destroy;

  destroy(v_, v_+vused_);  // compiled but...

  operator delete(v_);
}


template<class T>
void StackImpl<T>::Swap(StackImpl<T>& other) throw() {
  using std::swap;

  swap(v_, other.v_);
  swap(vsize_, other.vsize_);
  swap(vused_, other.vused_);
}

template<class T>
class StackInh : private StackImpl<T> {
public:
  StackInh(size_t size=0)
    : StackImpl<T>(size) {}

  ~StackInh();
  StackInh(const StackInh&);
  StackInh& operator=(const StackInh&);
  size_t Count() const;
  void Push(const T&);
  T& Top();
  void Pop();
};

TEST(Sutter, StackFirst) {
  Stack<int> stack;
  StackInh<int> stackInh(10);
}



//TODO:
//Not-throw swap
// http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Non-throwing_swap
// http://www.gotw.ca/gotw/059.htm
// http://stackoverflow.com/questions/11485776/exception-safety-regarding-swap-operation-whats-so-wrong-with-that
// http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom!!

//TODO:
// copy-and-swap idiom
// http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
