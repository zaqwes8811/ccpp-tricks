// http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms
// http://tinf2.vub.ac.be/~dvermeir/c++/EuroPLoP98.html

/// NVI
// http://en.wikipedia.org/wiki/Fragile_base_class
// http://clean-cpp.org/interfaces-done-right/

/// Pimpl habr
// http://stackoverflow.com/questions/60570/why-should-the-pimpl-idiom-be-used
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
//   - классы с d-указателями хорошо подходят для транзакционно-ориентированного и безопасного относительно исключений кода.
//   - это возможность сократить дополнительные динамические выделения памяти - можно сделать члены values тогда память будет выдел
//     большим куском - но есть какая-то проблема c последовательностью распределений памяти
//
// Summary:
//   решение проблема громоздкие, а значит не для всех классов системы, а значит система должна быть реально большой.
//
// FIXME: что-то с константностью
// habr.
// *.h
class Class
{
public:
  void swap(Class& rhs) {
    std::swap(d, rhs.d);
    // ...
  }

  Class &operator=(const Class &other)
  {
      // это может не сработать, но не изменит *this
      Class copy(other);
      // это не может не сработать, фиксируя транзакцию в *this
      swap(copy);
      return *this;
  }

  // DANGER)0 - const
  SomeThing & Class::someThing() const {
    // for const meth. this is const
    const Private* d = d_func();
    return d->someThing;
  }

  // V0
  template <typename T>
  class deep_const_ptr 
  {
      T * p;
  public:
      explicit deep_const_ptr( T * t ) : p( t ) {}

      const T & operator*() const { return *p; }
      T & operator*() { return *p; }

      const T * operator->() const { return p; }
      T * operator->() { return p; }
  };

  // V2 - перегрузка
  const Private * d_func() const { return d_; }
  Private * d_func() { return d_; }

  // Необычный оператор присваивания
  Handle& Handle::operator=(const Handle &other) {
    if(this != &other) {
        *smile = *(other.smile);
    }
    return *this;
  }

private:
  // no assign and copy ctor
  class Private; // предварительное объявление
  Private* d_;    // сокрытие деталей реализации
  // d - не константен! 
};

// *.cc
class Class::Private {  // !!
public:
  bool canAcceptN(double num) const { return num != 0 ; }
  double n;

  Class * const q; // back-link
public:
  // не передаем
    explicit Private( /*Class * qq*/ ) : q( 0 ) {}
};

Class::Class()
    : d(new Private) {

      // обр ссылка -  в самом конце, до этого нельзя
      d->q = this;
    }

Class::~Class()
{
    // http://stackoverflow.com/questions/4190703/is-it-safe-to-delete-a-null-pointer
    // if (d)  ??  // Wrong - не нужно проверять
    delete d;  // кажется проверяет указатель на ноль
}

void Class::f(double n)
{
    if (d->canAcceptN(n))
        d->n = n;
}

// Dr.Dobbs
// http://www.drdobbs.com/cpp/making-pimpl-easy/205918714
class Book
{
  public:

    Book(string const& title, string const& author);
    string const& title() const;
    string const& author() const;

    bool operator==(Book const& that) const { return impl_ == that.impl_; }
    bool operator!=(Book const& that) const { return !operator==(that); }
    operator bool() const { return impl_; }

  private:

    struct Implementation;
    boost::shared_ptr<Implementation> impl_;
};