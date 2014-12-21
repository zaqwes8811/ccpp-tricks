
#include "stdafx.h"


//@Global:
// http://stackoverflow.com/questions/2407540/what-are-the-downsides-to-using-dependency-injection?rq=1

//@Variants:
//   - Передача в конструктор. Но это тянет за собой наверх некоторые вещи.
//     Q: А скрытые зависимости? Это то же самое что и new в конструкторах? Или несовсем?
//       http://habrahabr.ru/post/166287/
//       http://sergeyteplyakov.blogspot.ru/2012/12/di-constructor-injection.html !!
//   "Вместо этого, на каждом уровне системы у нас будет набор абстракций, релевантных решаемым задачам, ""
//   - Method
//   - Fields - Guice поддерживать похоже
//   Q: А как быть со статическими методами генерации?
//  https://code.google.com/p/google-guice/wiki/Injections

//@Coupling and other: 
// http://www.youtube.com/watch?v=acjvKJiOvXw "In prod. no nulls, no new operators, 
//   in test code - lots of news lots of nulls."
// IoC and testing - http://stackoverflow.com/questions/1465849/using-ioc-for-unit-testing
// Есть DI and IoC
// DI Framework для тестирование полезен, но не обазятален. IoC контейнер похоже
//   излишен. Для С++ - вот в Java можно создавать классы и так и сяк, там
//   @Inject аннотация

//@FRAMEWORKS

//@Framework: Wallaroo
// Q: Может он и не предназначен для тестирования - больше для релизов?
// Похоже инжекция только в поля класса, по примерам в закрытые. В Google Guice - в конструктор
// 
// С gmock взаимодействие не ясно.
// Fake-объекты - все ок, но вот Mock из gmock...
//
// Ограничивает число паремаетров констр. двумя
//   "Now, whenever we add or remove dependencies, the compiler will remind us what tests need to be fixed. 
//     The dependency is exposed in the API signature."
//   https://code.google.com/p/google-guice/wiki/Motivation
//
// Как передать конструктору объект? Например через конф. файл
//
// Похоже в памяти создается много объектов
//
// Q: Для тестирования вообще подходит?
//
// Есть сомнения...


//@Framework: dicpp
// Похоже только инжекция через конструктор, но как просто создать объект
// Похоже на Google Guice, и наверное лучше сперва понять как оно работает

//@Framework: sauce
//   https://github.com/phs/sauce/ - Q: Как собрать под windows? - A: Похоже никак

//@Framework: iocp https://code.google.com/p/iocplusplus/
// Выглядит ниче

//@Decigion:
//   Просто фабрики, иначе шаблоны и макросы.


#include "wallaroo/registered.h"
#include "wallaroo/catalog.h"

#include <boost/shared_ptr.hpp>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
using ::testing::AtLeast;

using boost::shared_ptr;

using namespace wallaroo;

class Probe : public Device {
public:
	~Probe() {}
	virtual bool MustDrain() = 0;
};

class SumpProbe : public Probe {
public:
	virtual bool MustDrain() { 
		return true; 
	}
};

class SumpProbeShPtr : public Probe {
public:
  SumpProbeShPtr(shared_ptr<int> i) {
    
  }
	virtual bool MustDrain() { 
		return true; 
	}
};


// Объект нужно настраивать перед вызовом тесто
//   и похоже это делать над реальным объектом, а не над
//   указателем
class MockSumpProbe : public Probe {
public:
	MOCK_METHOD0(MustDrain, bool());
};

class PumpEngine : public Device {
public:
	void On() {}
	void Off() {}
};

class SumpPump : public Device {
public:
  SumpPump();
  virtual void Drain();
private:
  // Q: Использует weak_ptr's. А как быть с владением?
  // Q: Инжекция происходит не через конструктор и в закрытые члены. Норм?
  // Q: Как быть с моками из gmock? Можно ли их подсунить, и нужно ли?
  Plug<Probe> probe;
  Plug<PumpEngine> engine;
};

WALLAROO_REGISTER( PumpEngine )
WALLAROO_REGISTER( SumpProbe )
WALLAROO_REGISTER( MockSumpProbe )
WALLAROO_REGISTER( SumpPump )
WALLAROO_REGISTER( SumpProbeShPtr, shared_ptr<int> )

SumpPump::SumpPump() :
  probe( "probe", RegistrationToken() ),
  engine( "engine", RegistrationToken() )
{
}


void SumpPump::Drain() {
    if (probe-> MustDrain() ) engine -> On();
    else engine -> Off();
}

// По сути формируется дерево зависимостей
	Catalog catalog;

TEST(PainterTest, CanDrawSomething) {
	//
	shared_ptr< SumpPump > pump = catalog[ "pump" ];
	//while ( true )
		pump -> Drain();

  /*MockTurtle turtle;                          // #2
  EXPECT_CALL(turtle, PenDown())              // #3
      .Times(AtLeast(1));

  Painter painter(&turtle);                   // #4

  EXPECT_TRUE(painter.DrawCircle(0, 0, 10));*/
  //Probe* probe = new SumpProbe();
}

int main(int argc, char** argv) {
  // Create object graph
  catalog.Create( "twoLevelsProbe", "SumpProbe" );
  catalog.Create( "safeEngine", "PumpEngine" );
  catalog.Create( "pump", "SumpPump" );

	wallaroo_within( catalog ) {
		use( "twoLevelsProbe" ).as( "probe" ).of( "pump" );
		use( "safeEngine" ).as( "engine" ).of( "pump" );
	}
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

