

// G8
class B {
public:
  void g();
private:
  virtual void f(); // new
};
class D : public B {
public:
  void f();  // неожиданно стала виртуальной
private:
  double g; // new - неожиданно перекрыла публичную функцию
};

// G9 - Using Bad Language
//method -> member function!
//NULL - ... похоже платформо зависимое значение - 0 просто ноль

// G8 - gnorance of Idiom
//One of the most common and useful C++ idioms is the copy operation idiom. Every abstract data type in C++ should
//make a decision about its copy assignment operator and copy constructor. Either the compiler should be allowed to
//write them, the programmer should write them, or they should be disallowed

