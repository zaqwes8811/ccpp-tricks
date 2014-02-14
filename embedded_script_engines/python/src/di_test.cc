// di - dependency injections

// http://www.boost.org/doc/libs/1_43_0/libs/python/doc/v2/register_ptr_to_python.html

// Third party
#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/python.hpp>

using boost::shared_ptr;
using boost::python::object;
using boost::python::handle;
using boost::python::borrowed;
using boost::python::error_already_set;


// Абстрактный класс
class Preamplifier {
public:
	virtual ~Preamplifier () {}
	virtual int SetChannel(const int value) {return 0;}// = 0;
};

class PreamplifierImplFake : public Preamplifier {
public:
	PreamplifierImplFake() {}
	virtual int SetChannel(const int value) {
		channel_ = value;
		return 0;
	}
private:
	int channel_;
};

class PreamplifierImplReal : public Preamplifier {
public:
	PreamplifierImplReal() {}
	virtual int SetChannel(const int value) {
		channel_ = value;
		printf("channel = %d\n", value);
		return 0;
	}
private:
	int channel_;
	int eeprom_[20];
};

BOOST_PYTHON_MODULE(preampl)
{
  boost::python::class_<PreamplifierImplFake, 
	  boost::shared_ptr<PreamplifierImplFake>>("PreamplifierImplFake")
    .def("SetChannel", &PreamplifierImplFake::SetChannel)
  ;
}

using boost::python::wrapper;

class BaseWrap : public Preamplifier, wrapper<Preamplifier> {
	int SetChannel()
	{
	if (boost::python::override SetChannel = this->get_override("f"))
		return SetChannel(); // *note*
	return Preamplifier::SetChannel(0);
	}
	int default_f() { return this->Preamplifier::SetChannel(0); }
};

/*BOOST_PYTHON_MODULE(preampl_base)
{
  boost::python::class_<Preamplifier, boost::noncopyable>("Base")
	.def("f", boost::python::pure_virtual(&Preamplifier::SetChannel))
 ;
}*/


TEST(DI, Base) {
	//Preamplifier preampl;  // не компилируется
	//PreamplifierImplFake preampl;
	PreamplifierImplReal preampl;  // создание по значению!

	// Клиентский код
	// Действия над усилителем
	preampl.SetChannel(1);
}

TEST(DI, SmartPtr) {
	//Preamplifier preampl;  // не компилируется
	//PreamplifierImplFake preampl;
	shared_ptr<Preamplifier> preampl(new PreamplifierImplFake());  // создание по значению!

	// Клиентский код
	// Действия над усилителем
	preampl->SetChannel(1);
}

TEST(DI, RunFromString) {
  Py_Initialize();
  try {
    PyRun_SimpleString(
      "a_foo = None\n"
      "\n"
      "def setup(a_foo_from_cxx):\n"
      "  print 'setup called with', a_foo_from_cxx\n"
      "  global a_foo\n"
      "  a_foo = a_foo_from_cxx\n"
      "\n"
      "def run():\n"
      "  a_foo.SetChannel(6)\n"
      "\n"
      "print 'main module loaded'\n"
    );

    boost::shared_ptr<Preamplifier> ptr_cc_object(new PreamplifierImplFake());

    initpreampl();
    object main = object(handle<>(borrowed(PyImport_AddModule("__main__"))));

    // pass the reference to a_cxx_foo into python:
    object setup_function = main.attr("setup");
    setup_function(ptr_cc_object);

    // now run the python 'main' function
    object run_func = main.attr("run");
    run_func();
  } catch (error_already_set) {
    PyErr_Print();
  }

  Py_Finalize();
}
