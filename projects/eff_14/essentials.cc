
// These types are frequently different, because ParamType often contains 
// adornments, e.g., const or reference qualifiers.
template<typename T>
void f(ParamType param);

// Exmple
template<typename T>
void f(const T& param);
// ParamType is const T&

// Case 1:
For example, if this is our template,
template<typename T>
void f(T& param);
// param is a reference

int x = 27;
const int cx = x;
const int& rx = x;
// x is an int
// cx is a const int
// rx is a reference to x as a const int
f(x); // T is int, param's type is int&
f(cx); // T is const int,
// param's type is const int&
f(rx); // T is const int,  // That’s because rx’s reference-ness is ignored during type deduction.
// param's type is const int&

template<typename T>
void f(const T& param); // param is now a ref-to-const
int x = 27;
const int cx = x;
const int& rx = x; // as before
// as before
// as before
f(x); // T is int, param's type is const int&
f(cx); // T is int, param's type is const int&
f(rx); // T is int, param's type is const int&

template<typename T>
void f(T* param); // param is now a pointer

// Case 2: ParamType is a Universal Reference
template<typename T>
void f(T&& param); // param is now a universal reference
int x = 27;
const int cx = x;
const int& rx = x; // as before
// as before
// as before
f(x); // x is lvalue, so T is int&,
// param's type is also int&
f(cx); // cx is lvalue, so T is const int&,
// param's type is also const int&
f(rx); // rx is lvalue, so T is const int&,
// param's type is also const int&
f(27); // 27 is rvalue, so T is int,
// param's type is therefore int&&

// Case 3: ParamType is Neither a Pointer nor a Reference
template<typename T>
void f(T param);
// param is now passed by value

// Arrays and Ptrs
// return size of an array as a compile-time constant. (The
// array parameter has no name, because we care only about
// the number of elements it contains.)
template<typename T, std::size_t N>
// see info
constexpr std::size_t arraySize(T (&)[N]) noexcept // below on
{
// constexpr
   return N;
// and
// noexcept
}

// [!] Arrays aren’t the only things in C++ that can decay into pointers.

// This rarely makes any difference in practice, but if you’re going to know about array-
// to-pointer decay, you might as well know about function-to-pointer decay, too.

//==========================================================================
//==========================================================================
//==========================================================================

// Item 2: Understand auto type deduction.
template<typename T>
void f(ParamType param);
// and this general call:
f(expr);
// call f with some expression
//In the call to f, compilers use expr to deduce types for T and ParamType.
// When a variable is declared using auto, auto plays the role of T in the template, and
// the type specifier for the variable acts as ParamType.

auto x3 = { 27 }; // type is std::initializer_list<int>,
// value is { 27 }
auto x4{ 27 }; // ditto


//==========================================================================
//==========================================================================
//==========================================================================

// Item 3: Understand decltype .

//==========================================================================
//==========================================================================
//==========================================================================