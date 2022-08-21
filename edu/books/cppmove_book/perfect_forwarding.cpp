//
// Created by zaqwes on 26.03.2022.
//

#include <gtest/gtest.h>

#include <iostream>

// universal refs (also called forwrading refs) and (perfect) forwarding
// move sem is not automatically passed through

class X {};

void foo(const X &) { std::cout << "void foo(const X&)" << std::endl; }

void foo(X &) { std::cout << "void foo(X&)" << std::endl; }

void foo(X &&) { std::cout << "void foo(X&&)" << std::endl; }

void callFoo(const X &arg) { foo(arg); }

void callFoo(X &arg) { foo(arg); }

void callFoo(X &&arg) { foo(std::move(arg)); }

TEST(PerfForwarding, Basic) {
    X v;
    const X c;
    foo(v);
    foo(c);
    foo(X{});
    foo(std::move(v));
    foo(std::move(c));

    std::cout << "Wrapper" << std::endl;

    // perfectly forwarded, but duplication
    callFoo(v);
    callFoo(c);
    callFoo(X{});
    callFoo(std::move(v));
    callFoo(std::move(c));
}