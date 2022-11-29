#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

//#include <concepts>


template<typename T>
concept Any = true;

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
void ignore(T const&) {}

template<typename T>
void shell(T const& env) {
    class ShallowChecks {
        void deref(typename T::Index ptr) { ignore(*ptr); }
    };

    typename T::Index i;
    middle<T>(i);
}

class Client {
public:
    using Index = int;
};

TEST(DebugTemplatesTest, Step0) {
    //    Client mainClient;
    //    shell(mainClient);
}

template<typename T>
class HasDereference {
private:
    template<typename U>
    struct Identity;

    template<typename U>
    static std::true_type test(Identity<decltype(*std::declval<U>())>*);

    template<typename U>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

// https://stackoverflow.com/questions/44579440/how-can-i-use-a-concept-as-a-template-parameter

template<typename T>
//requires(
//
//    )
void shell1(T const& env) {
    static_assert(HasDereference<T>::value, "T is not dereferenceable");
    typename T::Index i;
    middle(i);
}

TEST(DebugTemplatesTest, Step1) {
    Client mainClient;
//    shell1(mainClient);

    static_assert(HasDereference<int*>::value, "T is not dereferenceable");
}

// archetype
template<typename T>
int find(T const* array, int n, T const& value) {
    int i = 0;
    //    while(i != n && array[i] != value)
    while (i != n /*&& !(array[i] == value)*/) {
        if (array[i] == value) {
            return i;
        }
        ++i;
    }
    return i;
}

//class EqualityComparableArchetype {
//};
//
//class ConvertableToBoolArchetype {
//public:
//    operator bool() const;
//
//    bool operator!() = delete;
//};
//
//ConvertableToBoolArchetype operator==(EqualityComparableArchetype const&, EqualityComparableArchetype const&);
//
//template int find(EqualityComparableArchetype const*, int, EqualityComparableArchetype const&);
