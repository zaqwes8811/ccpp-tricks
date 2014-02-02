#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/python.hpp>
#include <string>
#include <iostream>

namespace bp = boost::python;

struct Foo{
    Foo(){}
    Foo(std::string const& s) : m_string(s){}
    void doSomething() {
        std::cout << "Foo:" << m_string << std::endl;
    }
    std::string m_string;
};

typedef boost::shared_ptr<Foo> foo_ptr;

BOOST_PYTHON_MODULE(hello)
{
    bp::class_<Foo, foo_ptr>("Foo")
        .def("doSomething", &Foo::doSomething)
    ;
}

int main(int argc, char **argv)
{
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

        foo_ptr a_cxx_foo = boost::make_shared<Foo>("c++");

        inithello();
        bp::object main = bp::object(bp::handle<>(bp::borrowed(
            PyImport_AddModule("__main__")
        )));

        // pass the reference to a_cxx_foo into python:
        bp::object setup_func = main.attr("setup");
        setup_func(a_cxx_foo);

        // now run the python 'main' function
        bp::object run_func = main.attr("run");
        run_func();
    }
    catch (bp::error_already_set) {
        PyErr_Print();
    }

    Py_Finalize();

    return 0;
}
