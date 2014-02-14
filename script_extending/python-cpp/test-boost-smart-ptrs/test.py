# http://stackoverflow.com/questions/5049842/autocomplete-in-pycharm-for-python-compiled-extensions

import hello_

hello_.say_hello("you")
hello_.Foo().doSomething() # In PyCharm bad autocomplete


class Foo(object):
    def doSomething(self):
        hello_.Foo().doSomething()

Foo().doSomething()