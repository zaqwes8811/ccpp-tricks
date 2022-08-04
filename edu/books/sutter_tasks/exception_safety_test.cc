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
// Важно то что обработчик должен иметь достаточно информации - например
// пользователь
//
// "...обрабатывает сам и остается в согласованном состоянии..."
// Интересно сделано. Классы исключения включены в интерфейс класса, как внутр.
// классы
//
// Try/Catch - обработка ошибок, преобразование искл., перехват на границе
// системы
//
// Warranty
// - Basic - нет утечек и объекты в согл., но возможно непредсказуемом состоянии
// - Strong - обеспечивает семантику транзакций
// - Nofail - бессбойность - destructors, resource free, swap
// TODO: Когда какую? Минимально строгую, в которой не нуждается вызывающий код.
// - don't understood...
//
/// Own Summary:
// - RAII, ScopeLocks
// - one function - strongly one task
// - calc and change state object use exc. safe methods - транзакционное
// программирование
// - base types and pointer (smart?) on assign no throw - TODO: = can throw, how
// impl swap? pimpl?
//   конструктор, констр. копирования и опер. присв. могут бросать исключения.

#include <algorithm>
#include <iostream>
#include <stdexcept>

#include <gtest/gtest.h>

using std::cout;
using std::logic_error;

// TODO: часть 9

// TODO:
// Not-throw swap
// http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Non-throwing_swap
// http://www.gotw.ca/gotw/059.htm
// http://stackoverflow.com/questions/11485776/exception-safety-regarding-swap-operation-whats-so-wrong-with-that
// http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom!!

// TODO:
// copy-and-swap idiom
// http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom

// TODO: p. 339

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
    OpenFailed() : logic_error("") {}
  };

  // Throws: OpenFailed
  void Open() {}
};

TEST(Sutter, ExceptionBase) { Session::OpenFailed error(); }

TEST(Sutter, Stack) {
  // перенесен в структуры данных
}

// TODO: Exception on construction
// http://www.gotw.ca/gotw/066.htm
// http://herbsutter.com/2008/07/25/constructor-exceptions-in-c-c-and-java/
TEST(Sutter, ExcConstr) {
  {
    int(1);
    // http://www.informit.com/guides/content.aspx?g=cplusplus&seqNum=199
    const int &perch = int(1);

    // ... more code; at this point, only the first
    // temporary object is pushing up daisies ...
  }
  // Get it? It's a lifetime-of-temporaries-bound-to-references joke
}
