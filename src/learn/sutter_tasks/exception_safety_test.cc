

/// New tasks - p. 81
// безопасность искл. - часть проектирования
//
// Troubles:
//   - Resources
//   - Consistency - Invariants
//
// Guards, transactions
//
// Error handling strategy:
//   Сообщения об ошибках
//   Распространение ошибок
//   Обработка
// Важно то что обработчик должен иметь достаточно информации - например пользователь
//
// "...обрабатывает сам и остается в согласованном состоянии..."
// Интересно сделано. Классы исключения включены в интерфейс класса, как внутр. классы

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
