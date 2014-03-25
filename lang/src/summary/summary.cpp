// summary.cpp : Defines the entry point for the console application.
//
// Что хотелось бы:
//   Обращение к параметрам конфигурации идет парное по типу, и хорошо бы
//     набрать парных вызовов, и на недостающие укажет компилятор.
//
// Скрывает тип конфигурационного файла - Json, Yaml, XML, ...

// Конфигуратор в Java для Yaml. Главное знать какой тип нужен.
/*
class ...
  // Все строится из одного объекта. В С++ не так.
  // Возможно это и проблема, поэтому в конфигураторах есть разделение
  //   в имени, а не в типе.
  Object getValueByPath(String path) { some actions; }
}

// Преобразование все же рискованное...
Map<String> getListEmployers() {
  Map<String> employers = (Map<String>)configurator.getValueByPath("any/thing");
  return employers;
}*/

// Апачевский конфигурато
// http://commons.apache.org/proper/commons-configuration/
// Сразу бросается в глаза, что:
//   - Пути через точку
//   - getLong, getString... - тип в названии

/*
http://crypto.pp.ua/2010/06/peregruzka-metodov-klassov-java/
"При перегрузке всегда следует придерживаться следующих правил:

· не использовать сложных вариантов перегрузки;
· не использовать перегрузку с одинаковым числом параметров; - а я использовал
· заменять при возможности перегруженные методы на несколько разных методов."
*/

// C++
#include <stdexcept>
#include <string>

// Генарация акссессоров к хранилищу, чтобы они знали где что лежит
//   но по сути, спецификация шаблок должна где-то пройти.
//
// По итогам работы с JsonCpp


// http://ru.wikipedia.org/wiki/%D0%9F%D0%B5%D1%80%D0%B5%D0%B3%D1%80%D1%83%D0%B7%D0%BA%D0%B0_%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BE%D0%B2
//
//@GetOnly or @GetAndSet?
template <typename T>
class Configurator {
  // T - std::string, Json::Value, int, double, map, list, vector...
  //   реализация скорее всего будет отличаться.
public:
  //@Trouble: разделить геттеры! По возвращаемому значению нельзя
  // 
  //@Idea: Необязательный параметр
  //  А как разделить при вызове?
  //
  //virtual T GetByPath(std::string path, T* value=NULL) const = 0;  // не вышло
  // 
  //
  //@Idea: передать объект для модификации
  // Не удобно для getter, но компромисно, если 
  //   этот класс должен оборачиваться, для инкапсуляции путей.
  // Передаем по ссылке, допустим, а если полиморфный объект? Что будет со
  //   спецификацией - по Лискоу ничего, специфицыруем базовый класс. Подумать таки...
  // 
  // Для защиты параметры поменял местами
  //virtual void GetByPath(const std::string& path, /*mutable*/ T& value) const = 0;  

  // Значение нужно реально сохранить! Т.е. скопировать, и подойдет ли тогда передача
  //   по ссылке?
  //
  virtual void SetByPath(const T/*&*/ value, const std::string& path) = 0;

  // Реализация пары отслеживается компилятором
};


//@GetAndSet
//template <typename T>
//class Setting {

//};

/*
class BaseAppConfigurer : 
  public Configurator<std::string>, 
  public Configurator<int> {
public:
  virtual ~BaseAppConfigurer() {}
};*/


// http://www.quizful.net/post/return-type-function-overloading
// Кажется плохо перегружать методы с одним параметром
// http://habrahabr.ru/post/149287/
// http://otvety.google.ru/otvety/thread?tid=41691fc1e0d27729
//
// Как быть с деструкторами?
class ServiceConfigurer : 
  // Задаю, какие мне нужны типы - в пределах типа, операции будут похожие.
  // По сути регистрация
  //
  // Однако обязывает переопределять методы. Это скорее не конфигуратор,
  //   а конфигуратор и менеджер настроек.
  public Configurator<int>, 
  public Configurator<std::string>
{
public:
  // Тут уже более подробная реализация через перегрузку
  virtual void SetByPath(const int/*&*/, const std::string& path) { return; }
  virtual void SetByPath(const std::string/*&*/, const std::string& path ) { return; }

  static ServiceConfigurer Build() { return ServiceConfigurer(); }

  // Проверка ключа!

private:
  // Должен быть терминальным!
  ServiceConfigurer() {}
  //virtual void GetByPath(const int/*&*/) { return; }
  //virtual void GetByPath(const std::string/*&*/ ) { return; }
};

//class WrapperServiceConfigurator : ...
//  int GetSNMPPort() const;
//  int SetSNMPPort


int main(int argc, char* argv[]) {
  ServiceConfigurer configurer = ServiceConfigurer::Build();
  return 0;
}

