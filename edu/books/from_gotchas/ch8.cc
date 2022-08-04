#include <gtest/gtest.h>

#include <iostream>
#include <memory>
#include <string>

using namespace std;

namespace gotchas {

// G47
template <int maxlen> class NBString {
public:
  explicit NBString(const char *name) : name_(name) {}
  // . . .
private:
  std::string name_;
  size_t len_;
  char s_[maxlen];
};

void fun() {
  NBString<32> a("Hello");
  NBString<32> b(a);
  b = a;
}

// G82
// "For the community of C++ programmers, a const member function implements
// "logical" constness." Физическая и логическая константность
//  http://alenacpp.blogspot.ru/2005/10/mutable-constcast.html
//
class BoundedString {
public:
  explicit BoundedString(int len) : buf_(0) {}
  // . . .
  size_t length() const {
    // if ()
    // len_ = // lazy does't work
    return len_;
  }
  void set(char c);
  void wipe() const { buf_[0] = '\0'; } // !! does't change obj !!

  // нельзя применить к неконстантным
  bool operator<(const BoundedString &rhs) {
    cout << "no const" << endl;
    return true;
  } // не гарантирует, что не поменятся сам

  bool operator>=(const BoundedString &rhs) const { return true; }

private:
  char *const buf_; // non-logical const
  // mutable
  int len_;
  size_t maxLen_;
};

// G83
// Проблема в том, что указатель на выделенную в куча и не в куче память не
// различимы.
struct Role {
  // public:
};

class EmployeeMaker;

// !!! // http://accu.org/index.php/journals/1390 - Uses of Classes with only
// Private and Protected Constructors Trouble: один конструктор не защищает от
// глупостей. Просто конструктора не достаточно. Лучше раздеять use and obj
// graph building.
class Employee {
public:
  virtual ~Employee() { delete role_; }
  void adoptRole(Role *newRole); // take ownership

  void shareRole(const Role *sharedRole); // does not own
  void copyRole(const Role *roleToCopy);  // set role to clone
  const Role *getRole() const;

  // TODO: нужны все функции копирования
private:
  // Not ready provide
  Employee &operator=(const Employee &);
  Employee(const Employee &);

public:
  // Stack creating
  //

  // private:
protected: // можно будет отнаследовать и законно создать
  // если конструкторы закрыты, то закрыт все!
  // Напрямую создать не можем
  // http://stackoverflow.com/questions/16785069/why-cant-a-derived-class-call-protected-member-function-in-this-code
  // http://stackoverflow.com/questions/1057221/what-are-practical-uses-of-a-protected-constructor
  // http://stackoverflow.com/questions/4524325/c-protected-class-constructor
  explicit Employee(Role *newRole) : role_(newRole) {}

  // TODO: как избавиться от friend? пока не понятно как. Закрытый конструктор
  // не так то просто вызвать имеет доступ и к приватным частям может иметь
  // много builder-ов
  friend class EmployeeMaker;

  void say_hello() {}

private:
  // Must be heap alloc.
  Role *const role_; // own => new Big Three
};

// Тоже как бы часть интерфейс класса, но не обязательно ее делать челном класса
// Но проблема если есть например многопоточная блокировка. Можно ее сделать
// доступной, но она должна быть еще и
//   рекурсивной иначе selflock, но рекурсивная иногда оверхед. Либо сделать
//   агрегат.
void doSomethingCompose(Employee &e) {
  // e
}

// DANGER: ctor vs named ctor vs fabric vs maker()
//Луше сделать фабрику. Возможно это даже лучше именованного конструктора
// можно использовать EmployeeMaker, это хоть какая-то защита
// он нужен не для того. Можно скрыть конструктор
class EmployeeMaker {
public:
  // Если корректно реализована, то создает только в куче. Хотя можно еще в
  // статической области
  // TODO: как обозначить, что нужно передать что-то созданное в куче?
  // Precond.:
  //   Heap Alloc - объект берет на себя обязательства по управлению временем
  //   жизни
  static Employee *create(/*Role* newRole*/) {
    // Защита улучшена. MakeCommitment не нужна, т.к. сами создаем.
    Role *r = new Role;
    Employee *emp = new Employee(r);
    // emp->role_;
    return emp;
  }
};

// http://stackoverflow.com/questions/120876/c-superclass-constructor-calling-rules
///*
// NO WAY:
// http://answerstop.org/question/466561/one-question-about-protected-constructor
// Еще проблема в том, что в наследуемом лежат данные базового => размер растет!
class EmployeeMakerInh : public Employee {
public:
  // EmployeeMakerInh() :
  //  Если корректно реализована, то создает только в куче. Хотя можно еще в
  //  статической области
  // TODO: как обозначить, что нужно передать что-то созданное в куче?
  // Precond.:
  //   Heap Alloc - объект берет на себя обязательства по управлению временем
  //   жизни

  // TODO: почему не дает создать?
  /*
  protected:
    static Employee* create(
      //Role* newRole
      ) {
      // Защита улучшена. MakeCommitment не нужна, т.к. сами создаем.
      Role* r = new Role;

      Employee* emp = new Employee(r);  // не выходит создать - нет доступк к
  конструктору
      //emp->role_;
      return emp;
    }
  */

private:
  EmployeeMakerInh() : Employee(new Role) /* есть доступ к конструктору */ {
    Employee::say_hello(); // методы может вызывать
  }
};
} // namespace gotchas

TEST(G, NxCh8) {
  using namespace gotchas;
  const BoundedString s(5);
  // const  // not compiled
  BoundedString d(7);
  // s.set('a');  // не даст установить
  d < s;
  d.length();

  // DANGER: runtime failure
  // BoundedString* p_raw = &d;
  // auto_ptr<BoundedString> p(p_raw);  // вобщем классу передать владение не
  // просто.

  auto_ptr<Employee> e(EmployeeMaker::create());

  // EmployeeMakerInh();
}