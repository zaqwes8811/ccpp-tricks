// G72
// "A Template Method gives us a level of
//   control between that of nonvirtual and virtual functions."
// NVI - это тоже как бы шаблонынй метод
class Base {
public:
  virtual ~Base(); // I'm a base class
  virtual bool verify() const = 0; // you must verify yourself
  virtual void doit(); // you can do it your way or mine
  long id() const; // live with this function or go elsewhere
  void jump(); // when I say "jump," all you can ask is . . .
protected:
  virtual double howHigh() const; // . . . how high, and . . .
  virtual int howManyTimes() const = 0; // . . . how many times.
};

// G73 Overloading Virtual Functions

// G76 Virtual Assign
// = -> clone() (virtual constructor) - Prototype pattern

// G77 Failure to Distinguish among Overloading, Overriding, and Hiding
// A nonvirtual base class function cannot be overridden, only hidden.
// Скрывает все! невиртуальные перегруженные функции.

