
#include <boost/shared_ptr.hpp>

#include <algorithm>
#include <string>

using std::string;

// http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms
// http://tinf2.vub.ac.be/~dvermeir/c++/EuroPLoP98.html

/// Pure VI

/// NVI
// http://en.wikipedia.org/wiki/Fragile_base_class
// http://clean-cpp.org/interfaces-done-right/

/// Pimpl habr
// http://stackoverflow.com/questions/60570/why-should-the-pimpl-idiom-be-used
// Testing:
// http://stackoverflow.com/questions/2785206/the-pimpl-idiom-and-testability?rq=1
//
// Cons:
//   неэффективно, проблемы с inline и константной семантных метовдов
//   нарушение const-корректности - а есть ли она реально?
//   нет доступа к parent
//   какие-то сложности с наследованием - сейчас не осознал
//
// Pro:
//   - скрывает детали реализации - remove from *.h file
//   - уменьшает время компиляции
//   - можно сделать swap and assign exception safe
//   - классы с d-указателями хорошо подходят для транзакционно-ориентированного
//   и безопасного относительно исключений кода.
//   - это возможность сократить дополнительные динамические выделения памяти -
//   можно сделать члены values тогда память будет выдел
//     большим куском - но есть какая-то проблема c последовательностью
//     распределений памяти
//
// Decision:
//   решение проблема громоздкие, а значит не для всех классов системы, а значит
//   система должна быть реально большой.
//   http://stackoverflow.com/questions/825018/pimpl-idiom-vs-pure-virtual-class-interface?rq=1
//   - что-то в этом есть. pimpl помогает
//     реализовать копирующие функции.
//   "However, I only ever use pImpl to implement Value types (type 1),
//    and only sometimes when I really want to minimize coupling and
//    compile-time dependencies."
//   http://stackoverflow.com/questions/843389/the-pimpl-idiom-in-practice?rq=1
//
// FIXME: что-то с константностью
// habr.
// *.h
namespace habr_version {
typedef int SomeThing;

// V0
template <typename T> class deep_const_ptr {
  T *p;

public:
  explicit deep_const_ptr(T *t) : p(t) {}

  const T &operator*() const { return *p; }

  T &operator*() { return *p; }

  const T *operator->() const { return p; }

  T *operator->() { return p; }
};

// Необычный оператор присваивания
/*
Handle& Handle::operator=(const Handle &other) {
  if(this != &other) {
      *smile = *(other.smile);
  }
  return *this;
}
*/

class Class {

private:
  // no assign and copy ctor
  class Private; // предварительное объявление
  Private *d_;   // сокрытие деталей реализации
                 // d - не константен!

public:
  void swap(Class &rhs) {
    std::swap(d_, rhs.d_);
    // ...
  }

  ~Class();

  Class();

  Class &operator=(const Class &other) {
    // это может не сработать, но не изменит *this
    Class copy(other);
    // это не может не сработать, фиксируя транзакцию в *this
    swap(copy);
    return *this;
  }

  // DANGER)0 - const
  const SomeThing &someThing() const;

  void f(double n);

  // V2 - перегрузка
  const Private *d_func() const { return d_; }

  Private *d_func() { return d_; }
};

// *.cc - порадок определений некоторых функция важен
class Class::Private { // !! нужно определить до определения конструктора и
                       // дектруктора
public:
  bool canAcceptN(double num) const { return num != 0; }

  double n;

  Class * // const
      q;  // back-link

  const SomeThing &someThing() const { return s_; }

public:
  // не передаем
  explicit Private(/*Class * qq*/) : q(0) {}

  SomeThing s_;
};

Class::Class() : d_(new Private) {

  // обр ссылка -  в самом конце, до этого нельзя
  d_->q = this;
}

Class::~Class() {
  // http://stackoverflow.com/questions/4190703/is-it-safe-to-delete-a-null-pointer
  // if (d)  ??  // Wrong - не нужно проверять
  delete d_; // кажется проверяет указатель на ноль
}

void Class::f(double n) {
  if (d_->canAcceptN(n))
    d_->n = n;
}

const SomeThing &Class::someThing() const {
  // for const meth. this is const
  const Private *d = d_func();
  return d->someThing();
}
} // namespace habr_version

namespace drdobbs_version {
// Dr.Dobbs
// http://www.drdobbs.com/cpp/making-pimpl-easy/205918714
class Book {
public:
  Book(string const &title, string const &author);

  string const &title() const;

  string const &author() const;

  bool operator==(Book const &that) const { return impl_ == that.impl_; }

  bool operator!=(Book const &that) const { return !operator==(that); }

  // FIXME: not compiled!
  // operator bool() const { return impl_; }

private:
  struct Implementation;
  boost::shared_ptr<Implementation> impl_;
};
} // namespace drdobbs_version
