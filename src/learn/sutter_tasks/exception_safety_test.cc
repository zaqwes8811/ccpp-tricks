

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

//TODO: Not-throw swap
// http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Non-throwing_swap
// http://www.gotw.ca/gotw/059.htm
// http://stackoverflow.com/questions/11485776/exception-safety-regarding-swap-operation-whats-so-wrong-with-that
// http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom!!
