//
// Created by zaqwes on 29.11.2022.
//

#include <gtest/gtest.h>

// syntactic constraints
// semantic constraints

template<typename T>
void clear(T& p) {
    *p = 0;
}

template<typename T>
void core(T& p) {
    clear(p);
}

template<typename T>
void middle(typename T::Index p) {
    core(p);
}

template<typename T>
void shell(T const& env) {
    typename T::Index i;
    middle<T>(i);
}

class Client {
public:
    using Index = int;
};

TEST(DebugTemplatesTest, Step0) {
    Client mainClient;
    shell(mainClient);
}