//
// Created by zaqwes on 18.09.2022.
//

// "Aut'o'matic

#include <vector>

// TODO(me) Read book about effective

void foo(const std::vector<int>& vec) {
    for (auto i = 0; i < vec.size(); ++i) {  // int i. Bad for x64
    }

    for (size_t i = 0; i < vec.size(); ++i) {
    }

    for (auto i = 0ull; i < vec.size(); ++i) {  // 128 systems?
    }

    // auto& item - or
    for (auto&& item : vec) {  // Better
    }
}

// Next
// Misreference
auto other = static_cast<const Self&(!!!)>(rhs_);       // copy here
auto& other = static_cast<const Self&>(rhs_);           // fix
decltype(auto) other = static_cast<const Self&>(rhs_);  // fix

const T& a = data[n];
const T& b = other.data[m];

// Should not auto! only for superclean situations

// Versus Intuition
using V = std::vector<...>;

void vector_inc(V& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        v[i]++;
    }
}

vector<uint32_t> v;
vector<uint8_t> v;  // Contrintuitive

auto it = v.begin();
const auto end = v.end();
for (; it != end; ++it) {
    ++(*it);
}

// again !
for (auto&& elem : v) {
    ++elem;
}

// Security
void DoSomething() {
    char passord[];

    memset(passord, 0, sizeof(passord));  // !!!

    // safe_memset + disable LTO/WPO
    // volatile
    //  Memse+ mem barrier
    // Disable some opt
    // memset_s
}

if (!fgets(readbuf, BUFSIZ, stdin)) {  // empty line!
}

if (getline(readbuf, BUFSIZ, stdin) == -1) {
}  // no! not here

if (readbuf[strlen(readbuf) - 1] == '\n')  // underflow
    readbuf[strlen(readbuf) - 1] = '\n';

// ! check input

// Last Mile
// ctrl+c / ctrl + v

// Have spaceship / Will travel
// <=>

struct Foo {
    int a, b;
};

bool operator==(Foo lhs, Foo rhs) {  // != - Ok?
    //    return lhs
}

// bool operator<  // Problem
bool operator<(Foo lhs, Foo rhs) { return lhs.a < rhs.a && lhs.b < rhs.b; }

bool operator<(Foo lhs, Foo rhs) {
    if (lhs.a < rhs.a) return true;  // && lhs.b < rhs.b;
    // ...
}

struct Foo {
    double a;
};

// < and >=
// Foo{Nan}

// lexicalgraphical compre
struct Foo {
    auto operator<=>(const Foo& rhs) const = default;
};

// ternary

// emplace
// NO Pod types with emplace

// Find It Again
// emplace for map/unord_map
// try_emplace

if (auto [it, success] = infoMap.try_emplace(); !success) {
    auto&& a = it->second;
}

// search only once

// noexcept
// Not noexcept/but implide so
// DllMain