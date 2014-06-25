

/// New tasks - p. 81
// безопасность искл. - часть проектирования
//
// Troubles:
//   - Resources
//   - Consistency - Invariants
//
// Guards, transactions
//
// !!!Error handling strategy - это самое важное!!!
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
// step 2: safe
template<class T> class Stack
{
public:
  Stack();
  ~Stack();

  // Step 3
  Stack(const Stack&);
  Stack& operator=(const Stack&);
  T* NewCopy(const T* src, size_t srcsize, size_t destsize);

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
    copy(src, src+srcsize, dest);  // used = ! не ясно в чем проблема, но она есть
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

// Step 4: assign
template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
  if (this != &other) {
      // may throw
      T* v_new = NewCopy(other.v_, other.vsize_, other.vsize_);

      // not throw - change state object
      delete [] v_;
      v_ = v_new;
      vsize_ = other.vsize_;
      vused_ = other.vused_;
  }
  return *this;
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
