//
// Created by zaqwes on 26.03.2022.
//

#include <iterator>

// Part 3
// traits - template properties

// Naive
template <typename T>
T accum(T const *beg, T const *end) {
    // Trouble here - overflow
    T total{};  // default ctor/or zero
    // bool -> false, ptr -> nullptr

    while (beg != end) {
        total += *beg;
        ++beg;
    }

    return total;
}

// Update
template <typename T>
struct AccumulationTraits;  // traits template

template <>
struct AccumulationTraits<char> {
    using AccT = int;

    static AccT const zero = 0;

    // C++17
    //    static constexpr AccT zero() {
    //        return 0;
    //    }
};

template <>
struct AccumulationTraits<short> {
    using AccT = int;

    static AccT const zero = 0;
};

template <>
struct AccumulationTraits<int> {
    using AccT = long;

    static AccT const zero = 0;  // << enum of "int"
};

template <>
struct AccumulationTraits<float> {
    using AccT = float;

    static AccT constexpr /*const*/ zero = 0.0f;
};

template <typename T>
auto accum_v1(T const *beg, T const *end) {  // my bad - T -> auto
    using AccT = typename AccumulationTraits<T>::AccT;
    AccT total{};  // << default ctor?

    while (beg != end) {
        total += *beg;
        ++beg;
    }

    return total;
}

// Update
// property-value - value trait

class BigInt {
public:
    BigInt(long long) {}
};

template <>
struct AccumulationTraits<BigInt> {
    using AccT = BigInt;
    //    static constexpr BigInt zero = BigInt(0);  // trouble

    // C++17
    // < C++17 - out of class
    inline static const BigInt zero = BigInt{0};  // trouble
};

template <typename T>
auto accum_v2(T const *beg, T const *end) {
    using AccT = typename AccumulationTraits<T>::AccT;
    AccT total = AccumulationTraits<T>::zero;
    //    AccT total = AccumulationTraits<T>::zero();

    while (beg != end) {
        total += *beg;
        ++beg;
    }

    return total;
}

// ^^^ fixed trait

// Update
template <typename T, typename AT = AccumulationTraits<T>>
auto accum_v3(T const *beg, T const *end) {
    typename AT::AccT total = AT::zero;  // depend type?
    //    AccT total = AccumulationTraits<T>::zero();

    while (beg != end) {
        total += *beg;
        ++beg;
    }

    return total;
}

//
// Policies and classes of Policies
//

class SumPolicy {
public:
    template <typename T1, typename T2>
    static void accumulate(T1 &total, T2 const &value) {
        total += value;
    }
};

class MultPolicy {  // << zero as identity
public:
    template <typename T1, typename T2>
    static void accumulate(T1 &total, T2 const &value) {
        total *= value;
    }
};

// dead end. std::accumulate() takes 3rd params as start value
template <typename T, typename Policy = SumPolicy, typename Traits = AccumulationTraits<T>>
auto accum_v4(T const *beg, T const *end) {
    typename Traits::AccT total = Traits::zero;  // depend type?
    //    AccT total = AccumulationTraits<T>::zero();

    while (beg != end) {
        Policy::accumultae(total, *beg);
        ++beg;
    }

    return total;
}

// strategies and properties - first one about behavior

template <typename T1, typename T2>
class SumPolicyV1 {
public:
    static void accumulate(T1 &total, T2 const &value) { total += value; }
};

// T through all types
template <typename T, template <typename, typename> class Policy = SumPolicyV1, typename Traits = AccumulationTraits<T>>
auto accum_v4(T const *beg, T const *end) {
    typename Traits::AccT total = Traits::zero;  // depend type?
    //    AccT total = AccumulationTraits<T>::zero();

    while (beg != end) {
        Policy<typename Traits::AccT, T>::accumultae(total, *beg);
        ++beg;
    }

    return total;
}

//
// Acc with iterators
//
template <typename Iter>
auto accum_v5(Iter start, Iter end) {
    // Alarm: no acc type value
    using VT = typename std::iterator_traits<Iter>::value_type;
    VT total{};  // use zero for simplicity
    while (start != end) {
        total += *start;
        ++start;
    }
    return total;
}

//
//
// SFINAE
//
//

// !! lambdas

//...

// Paragraph 20
// Props overloading
// Specialization of algs

// Paragraph 21 - templates and inh.

// Paragraph 22 - static and dynamic polym.

// Paragraph 23 - Metaprogramming

// Paragraph 24 - type lists

// Paragraph 25 - Tuples
// Boost.Fusion
// https://theboostcpplibraries.com/boost.fusion
// Fusion/Variadic - coupled?

// Paragraph 26 - Unions/Variant?
// std::launder
// https://stackoverflow.com/questions/39382501/what-is-the-purpose-of-stdlaunder
// https://www.youtube.com/watch?v=-rIixnNJM4k&t=583s&ab_channel=CppCon