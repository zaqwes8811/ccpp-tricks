#include <typeinfo>

#include <cassert>

// вообще базовые классы не должны создаваться - 35
class B {
public:
  B() {}  // обязательно если объявлен копирующий
  // не переносимо
  //explicit B(const B& rhs);  // нельзя будет передать по значению и запрещает срезку
  
  //virtual B* Clone() const = 0;  // change to NVI
  
  B* Clone() const {
    B* p = DoClone();
    
    // BAD: производительность сильно падает?
    // Тип копии должен быть одинаковым
    assert(typeid(*p) == typeid(*this) && "DoClone incorrect overridden.");
    return p;
  }
  
  // по умолчанию в базовом классе лучше вообще запретить копирование
  
protected:
  // нужен чтобы можно было создать копированием
  B(const B& rhs) : i(rhs.i) { }  // он нужен, т.к. мы создаем копированием
  
private:
  int i;
  
  virtual B* DoClone() const = 0;
};

class D : public B {
public:
  
  // BAD: создается в куче
  //virtual D* Clone() const { return new D(*this); }
  // может запрещать копирование и передавать умный указатель?
  D() {}
  
protected:
  D(const D& rhs) : B(rhs) {}
  
private:
  virtual D* DoClone() const { return new D(*this); }
};

//void Transmogrify_no_compiled(B obj) {} 
void Transmogrify(B* obj) {} 

void Transubstantiate(B& obj) {
  //!!!
  Transmogrify(&obj); // срезка!!
}

int main() 
{
  // 54 - срезка
  
  D d;
  Transubstantiate(d);
  
  // TODO: а как контейнеры будут с этими классами
  // Похоже лучше в контейнере хранить указатели, иначе похоже будет происходить что-то ужасное
  
  
  
  return 0;
}