/// "Shared ptr as good as global vars" Sean Parent
// http://cs.brown.edu/~jwicks/boost/libs/smart_ptr/sp_techniques.html
// http://www.boost.org/doc/libs/1_37_0/libs/smart_ptr/sp_techniques.html#com
// DANGER: ref counting and GC http://stackoverflow.com/questions/17646509/why-do-garbage-collectors-wait-before-deallocating/17647062#17647062


//#include "app/config.h"
// http://www.chromium.org/blink/coding-style#TOC-include-Statements

// App - включает только необходимое
// Порядок правда - хотя по идее не должен влиять
#define G_ZAQWES_ANALYSE
#include "Common/ReferenceCount.h" 
// FIXME: todo->fixme

/// Все хедеры, что нужны интерфейсам приложения включены, остались для реализации

// 3rdparty
#include <boost/intrusive_ptr.hpp>
#include <gtest/gtest.h>

// C++
#include <algorithm>
#include <deque>
#include <ostream>
#include <set>

// C

// System specific
// FIXME: A как быть если были включены? Может в config.h?
// http://www.chromium.org/developers/coding-style

using std::cout;
using std::endl;

// shared vs intrusive 
//   http://boost.2283326.n4.nabble.com/intrusive-ptr-vs-shared-ptr-td4641535.html
//   http://baptiste-wicht.com/posts/2011/11/boost-intrusive_ptr.html
// "Another case where it's interesting to use an intrusive_ptr is when dealing with 
// libraries using a lot of raw pointers, 
// because you can create several intrusive_ptr to the same raw pointer without any problem."
// FIXME: да, но библиотечные классы, то обычные, в них нет встроенного счетчика?
// множественное наследование? http://transportempire.com/?intrusive-pointer,19
//   потенциально можно передать ссылку и не удалять - стековый объект - но в чем смысл то?
// About COM: http://www.gamedev.net/topic/582850-boost-intrusive-pointer-intrusive_ptr/
// Кстатит можно вызывать не delete а делать какие-то действия - но есть ли польза если стековая переменная
//   и вообще тогда есть деструктор.
// http://legalizeadulthood.wordpress.com/2009/01/11/direct3d-programming-tip-3-use-smart-pointers/
//
// As a general rule, if it isn't obvious whether intrusive_ptr better fits 
//  your needs than shared_ptr, try a shared_ptr-based design first.
//
// Cons:
//   нет weak-пары
//
// Похоже в com-объекты уже встоены счетчики
// Intrusive use cases: http://blog.chrisd.info/a-use-case-for-intrusive-pointers/
// !!http://alsharabi.blogspot.nl/2009/06/boostintrusiveptr-is-one-of-six-smart.html
// http://www.boost.org/community/counted_body.html
//
// https://code.google.com/p/chromiumembedded/wiki/UsingTheCAPI
//
// Shared vs Intr.
// http://www.gamedev.ru/code/forum/?id=34739
TEST(Ref, BoostIntr) {
  
}

// зачем наследовать?
namespace Hypertable_analyse {
// ApplicationHandler(EventPtr &event) : m_event(event) {
  
using Hypertable::ReferenceCount;
class Widget : public ReferenceCount {
public:
  ~Widget() {
    cout << "dtor" << endl;
  }
};

typedef boost::intrusive_ptr<Widget> WidgetPtr;

TEST(Hy, RefConuting) {
  Widget w;
  Widget k;
  //w = k;  // non-copyble - только ссылки
  WidgetPtr w_ptr(new Widget());
  WidgetPtr w_a_ptr;
  w_a_ptr = w_ptr;
}
  
}


/// Theory
namespace Counting_Handle {

struct deleter {
  template <typename deletion_type>
  void operator()(deletion_type to_delete) const {
    delete to_delete;  // удаляет одни элемент
  }
};

//typename <typedef element_type>
template < typename element_type, typename destructor = deleter>
class counting_ptr {
public:
  explicit counting_ptr(element_type* countee=0);
  counting_ptr(const counting_ptr &);
  counting_ptr(element_type*, destructor); // step 2
  ~counting_ptr();
  counting_ptr &operator=(const counting_ptr &);
  element_type *operator->() const;
  element_type &operator*() const;
  
private:
  destructor destruct;
};

template <typename resource_type>
class resource_factory {
public:
  typedef typename resource_type::initializer_type initializer_type;
  resource_factory(initializer_type);
  resource_type* create() {
    return new resource_type(initializer);
  }
  
  typedef counting_ptr<resource_type> pointer;
  pointer create_1()
  {
    return pointer(new resource_type(initializer));
  } 
  
  // удаление - фабрика и разрушает тоже?
  class disposer
  {
  public:
    // неявное преобразование
    disposer(resource_factory *home) : home(home) {}
    void operator()(resource_type *to_dispose) const
    {
      home->dispose(to_dispose);
    }
  private:
    resource_factory *home;
  };
  
  typedef counting_ptr<resource_type, disposer> pointer_full;
  pointer_full create_2()
  {
    return pointer_full(new resource_type(initializer), this);  // что-то здесь не так
  }
  
  // объекто-крошилка, и она передается умному указателю
  void dispose(resource_type *);


  // ...
private:
  initializer_type initializer;
  // ...
};
}
// problem - не совсем понял в чем она

namespace Exlicitly_counting_object {
  
template <typename element_type>
class counting_ptr
{
public:
  //....
  size_t count() const;
  //....
};


template<typename resource_type>
class resource_factory
{
public:
  //....
  typedef typename resource_type::initializer_type initializer_type;
  
  // а что она вообще делает-то? переиспользует объекты что ли?
  typedef counting_ptr<resource_type> pointer;
  pointer create()
  {
    resource_type *result = 0;
    if(spare.empty())
    {
      result = new resource_type(initializer);
    }
    else
    {
      result = spare.front();
      result->reset(initializer);
      spare.pop_front();
    }
    live.insert(result);
    return pointer(result, this);
  }
  
  void dispose(resource_type *to_dispose)
  {
    live.erase(to_dispose);
    spare.push_back(to_dispose);
  }
  
  void clear()
  {
    std::for_each(spare.begin(), spare.end(), Counting_Handle::deleter());
    spare.clear();
  }
private:
  std::deque<resource_type *> spare;
  std::set<resource_type *> live;
  initializer_type initializer;
};
 
}
