#include <gtest/gtest.h>

#include <cassert>
#include <typeinfo>

// вообще базовые классы не должны создаваться - 35
class B {
public:
    B() {}  // обязательно если объявлен копирующий
    // не переносимо
    // explicit B(const B& rhs);  // нельзя будет передать по значению и запрещает
    // срезку

    // virtual B* Clone() const = 0;  // change to NVI

    B *Clone() const {
        B *p = DoClone();

        // BAD: производительность сильно падает?
        // Тип копии должен быть одинаковым
        assert(typeid(*p) == typeid(*this) && "DoClone incorrect overridden.");
        return p;
    }

    // по умолчанию в базовом классе лучше вообще запретить копирование

protected:
    // нужен чтобы можно было создать копированием
    // !!! передавать обязательно по ссылке? похоже если нет, то будет рекурсия.
    B(const B &rhs) : i(rhs.i) {}  // он нужен, т.к. мы создаем копированием

private:
    int i;

    virtual B *DoClone() const = 0;
};

class D : public B {
public:
    // BAD: создается в куче
    // virtual D* Clone() const { return new D(*this); }
    // может запрещать копирование и передавать умный указатель?
    D() {}

protected:
    D(const D &rhs) : B(rhs) {}

private:
    virtual D *DoClone() const { return new D(*this); }
};

// void Transmogrify_no_compiled(B obj) {}
void Transmogrify(B *obj) {}

void Transubstantiate(B &obj) {
    //!!!
    Transmogrify(&obj);  // срезка!!
}

///
class Base {
public:
    Base() {}

    Base(char *arg1, int arg2) {}

    Base(const Base &object) {}

    virtual ~Base() {}

    Base &operator=(const Base &object) {}

    virtual void Method1() = 0;

    void Method2(){};

private:
    int size;
    char *data;
};

class Derived : public Base {
public:
    Derived() : Base() {}

    Derived(char *arg1, int arg2, char *arg3, int arg4) : Base(arg3, arg4) {}

    // Danger
    // Derived(const Derived& object) : Base((Base &) object) { }
    // Правильно, но может бысть срезка, если еще наследовать
    Derived(const Derived &object) : Base(object) {}

    ~Derived() {}

    Derived &operator=(const Derived &object) {}

    virtual void Method1() {}

private:
    int size;
    char *data;
};

TEST(M, Main) {
    // 54 - срезка
    // Похоже тут дело даже не в этом. А в том, что если мы переопределям
    // конструторы копирования при наследновании возникает много трудностей. Но
    // работа с кучей!

    D d;
    Transubstantiate(d);

    // TODO: а как контейнеры будут с этими классами
    // Похоже лучше в контейнере хранить указатели, иначе похоже будет происходить
    // что-то ужасное

    // TODO: конструктор копирования при насделовании
    // http://forum.vingrad.ru/forum/topic-341831.html
    // Вообще переопределять конструктор копирования ответственной дело
    // http://www.cyberguru.ru/cpp/cpp-velvet-way2-page14.html
    // !!! http://www.cyberguru.ru/cpp/cpp-programming-rules2-page44.html
}