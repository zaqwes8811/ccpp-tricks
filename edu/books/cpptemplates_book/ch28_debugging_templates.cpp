#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

//#include <concepts>  // no such think in gnu++2a

template <class T>
concept integral = std::is_integral_v<T>;

template <typename T>
concept Any = true;

template <typename T>
concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;

// syntactic constraints
// semantic constraints

template <typename T>
concept Addable = requires(T a, T b) {
    a + b;
};

// Ptr != Deref.
// template <typename T>
// concept Dereferencable = std::is_pointer_v<T>;

template <typename T>
concept Dereferencable = requires(T t) {
    *t;
};

// this is just one way of doing it...
template <typename Arg>
struct is_dereferencable_f {
    static constexpr bool value = Dereferencable<Arg>;
};

// ...via template template parameters
template <typename Arg, template <typename> typename... Conjuncts>
concept /*bool*/ SatisfiesAll = (... && Conjuncts<Arg>::value);

// TODO() All args in variadic template satisfy

// template<Dereferencable T>
template <typename T>
requires Dereferencable<T> void clear(T& p) {
    *p = 0;
}

template <typename T>
void core(T& p) {
    clear(p);
}

template <typename T>
void middle(typename T::Index p) {
    core(p);
}

template <typename T>
void ignore(T const&) {}

template <typename T>
void shell(T const& env) {
    //    class ShallowChecks {
    //        void deref(typename T::Index ptr) { ignore(*ptr); }
    //    };

    typename T::Index i;
    middle<T>(i);
}

class Client {
public:
    //    using Index = int;
    using Index = std::optional<int>;
};

TEST(DebugTemplatesTest, Step0) {
    Client mainClient;
    shell(mainClient);
}

template <typename T>
class HasDereference {
private:
    template <typename U>
    struct Identity;

    template <typename U>
    static std::true_type test(Identity<decltype(*std::declval<U>())>*);

    template <typename U>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

// https://stackoverflow.com/questions/44579440/how-can-i-use-a-concept-as-a-template-parameter

template <typename T>
// requires(
//
//     )
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
template <typename T>
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

// class EqualityComparableArchetype {
// };
//
// class ConvertableToBoolArchetype {
// public:
//     operator bool() const;
//
//     bool operator!() = delete;
// };
//
// ConvertableToBoolArchetype operator==(EqualityComparableArchetype const&, EqualityComparableArchetype const&);
//
// template int find(EqualityComparableArchetype const*, int, EqualityComparableArchetype const&);
