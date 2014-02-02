// C++
#include <string>
#include <iostream>

// Third party
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/python.hpp>

#include <gtest/gtest.h>


using boost::python::class_;
using boost::python::object;
using boost::python::handle;
using boost::python::borrowed;
using boost::python::error_already_set;

class Foo{
public:
    Foo() {}
    Foo(std::string const& s) : m_string(s){}
    void doSomething() {
        std::cout << "Foo:" << m_string << std::endl;
    }
    std::string m_string;
};

BOOST_PYTHON_MODULE(hello)
{
    class_<Foo, boost::shared_ptr<Foo>>("Foo")
        .def("doSomething", &Foo::doSomething)
    ;
}

TEST(EmbPy, First) {
    Py_Initialize();
    try {
        PyRun_SimpleString(
            "a_foo = None\n"
            "\n"
            "def setup(a_foo_from_cxx):\n"
            "    print 'setup called with', a_foo_from_cxx\n"
            "    global a_foo\n"
            "    a_foo = a_foo_from_cxx\n"
            "\n"
            "def run():\n"
            "    a_foo.doSomething()\n"
            "\n"
            "print 'main module loaded'\n"
        );

        boost::shared_ptr<Foo> ptr_cc_object = boost::make_shared<Foo>("c++");

        inithello();
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

int main(int argc, char* argv[])
{

  // Получаем текущую локаль CRT (если нужно потом восстановить)
  char* crtLocale = setlocale(LC_ALL, NULL);
  setlocale(LC_ALL, ".1251");

  // Run
  testing::InitGoogleTest(&argc, argv);
  //testing::GTEST_FLAG(print_time) = true;
  RUN_ALL_TESTS();
  setlocale(LC_ALL, crtLocale);
  return 0;
}
