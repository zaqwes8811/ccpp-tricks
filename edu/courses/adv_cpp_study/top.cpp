//
// Created by zaqwes on 19.03.2022.
//

#include <iostream>
#include <iterator>
#include <set>
#include <type_traits>
#include <unordered_set>

// 6.2 Шаблоны
// зависимый и независимый тип

// Hierarhy of iterators

//
// 8.2 Iter inv
//
// Basic idea, iterators invalidation
// vector - iters invalidation - True \ ref invalidation - сырой указатель -
// Invalidation deque - скорее нет, но - реаллокация \ Остальные не ломаются
// list - нет инвалидации \ Остальные не ломаются
// map - нет инвалидации \ Остальные не ломаются
// unordered_map - рехэш \ Остальные не ломаются

// 8.3 - iterator types
// InputIterator -
// std::find(InputIterator first, InputIterator last, const T& x);
// будет делать инкремент(нет декремента) и разыменование - однопроходный
// алгоритый - нельзя скопировать и сделать инкремен и получить одно и то же
// Задача за линейное и один прход, бывает линейное но не один проход
// Forward iterator - допфишка - несколько раз можно проходить
// [forward_list::iteratior, unordered_map/unordered_set] FI ->
// BidirectionalIterator - (reverse iterator)
//   миожно дикрементировать [list::iterator, set/map (?? == begin? rend? TASK),
//   map/set может и не O(n)] - асмимптотики нет
// BI -> RandomAccessIterator - <> <= => +=n, it2-it1 - как указатель
// [vector/deque]
//
// FAI (c++17) - ContiquousIterator - гарантия - объекты лежат подряд,
//  &(*it) + 1 - следующий объекты [vector, array, c-style pointers]

//
// 8.4
//

// template <typename T>
// struct iterator_traits {
////    using value_type = ...;
////    using iterator_category = ..;  <<< !
//};

// struct input_iterator_tag {  // tag чтобы обозначить
// };
// struct forward_iterator_tag : public input_iterator_tag {
// };
//

template <typename Iterator, typename IteratorCategory>
void my_adv_helper(Iterator &iter, int n, IteratorCategory) {
    for (int i = 0; i < n; ++i) {
        ++iter;
    }
}

template <typename Iterator>
void my_adv_helper(Iterator &iter, int n, std::random_access_iterator_tag) {
    iter += n;
}

// C++17, tag for c++20
// template<typename Iterator>
// void my_adv_helper(Iterator& iter, int n, std::contiqous_iterator_tag) {
//    iter += n;
//}

template <typename Iterator>
void my_advance(Iterator &iter, int n) {
    //    if (...) iter+=n;
    //    else ...
    //    if /*constexpr*/ (std::is_same_v<typename
    //    std::iterator_traits<Iterator>::iterator_category,
    //        std::random_access_iterator_tag>) {
    //        iter += n;  // !!! CE
    //    }
    my_adv_helper(iter, n, typename std::iterator_traits<Iterator>::iterator_category());
}

//
// 8.5 - const and reverse iterators
//
// begin/cbegin
// const по разыменованному не записаться

template <bool B, typename U, typename V>
struct condtional {
    using type = V;
};

template <typename U, typename V>
struct condtional<true, U, V> {
    using type = V;
};

template <bool B, typename U, typename V>
using condtional_t = typename condtional<B, U, V>::type;

// надстрйока
template <typename Iterator>
class reverse_iterator {
    Iterator iter;

public:
    // same
    reverse_iterator<Iterator> &operator++() {
        --iter;
        return *this;
    }

    Iterator base() const { return iter; }
};

// !!! crbegin()

template <typename T>
struct Vector {
    int sz;
    T *str;

public:
    // how to use const and without copy

private:
    // std::conditional

    template <bool IsConst>
    struct common_iterator {
    private:
        //        using CondtionalPtr = ...
        std::conditional_t<IsConst, const T *, T *> ptr;

    public:
        std::conditional_t<IsConst, const T &, T &> &operator*() { return *ptr; }

        // Tricky - особенный
        //        std::conditional_t<IsConst, const T*, T*>* operator->() {
        //            return ptr;
        //        }

        //        template<typename U>  // WTF?
        //        U& operator->*(U T::*p) {
        //            return (*ptr).*p;
        //        }

        common_iterator &operator+=(int n) {
            ptr += n;
            return *this;
        }

        common_iterator operator+(int n) const {
            auto copy = *this;
            copy += n;
            return copy;
        }
    };

private:
    using iterator = common_iterator<false>;
    using const_iterator = common_iterator<true>;

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
};

// String::iterator operator+(int n, const String::iterator& iter) {
//     return iter + n;
// }

int main1() {
    std::set<int> s;
    //    std::unordered_set<int> s;
    for (int i = 0; i < 100; ++i) {
        s.insert(i);
    }
    //    std::set<int>::iterator it = s.begin();
    auto it = s.begin();
    //    std::cout << *(it + 1);
    std::cout << *std::next(it);
    std::advance(it, 25);  // work time depend on type
    std::cout << *it;
    std::advance(it, -10);  // unordered - segfault
    std::cout << *it;

    // std::distance
    auto it2 = it;

    std::cout << std::distance(it2, it);
    // если не достижим от первого ко второму - то UB
}

//
// 8.6 output iterators
//
// отдельно
// все в контейнерах не output
#include <algorithm>

template <typename Container>
struct back_insert_iterator {
private:
    Container &cont;

    operator++() {
        return *this;  // << nothign
    }

    // std::iterator_traits<Container::iterator>::value_type;
    typename Container::value_type &operator=(const typename Container::value_type &value) {
        cont.push_back(value);
        return cont.back();
    }

    back_insert_iterator operator*() {  // !!!
    }
};

// front_insert_iter - push_front
// insert_iterator

// back_inserter!!! - template fu
// inserter!!!

template <typename Container>
std::back_insert_iterator<Container> back_inserter(Container &c) {
    return back_inserter<Container>(c);
}

//
// 8.7 Stream iter
//

struct istream_iter {
    T value;

    T &operator*() { return val; }

    istream_iterator<T> &operator++() {
        stream >> value;
        return *this;
    }
};

int main2() {
    std::vector<int> v(10);

    std::vector<int> vv;                        // <<
    std::copy(v.begin(), v.end(), vv.begin());  // UB

    std::vector<int>::const_iterator i;
    //    std::vector<int>::iterator j = i;

    // Output - пишет-сдвигат, пишет-сдвигает
}

//============================================================================================
//============================================================================================
//============================================================================================

// Containers

//
// 9.1 Vector
//

// C++03
template <typename T>
class Vector {
private:
    T *arr;
    size_t sz;
    size_t cap;

public:
    // size() const
    // capacity() const

    void reserve(size_t n) {
        if (n <= cap) return;

        // https://stackoverflow.com/questions/64580921/c-aligned-new
        // https://www.cppstories.com/2019/08/newnew-align/
        // https://stackoverflow.com/questions/12942548/making-stdvector-allocate-aligned-memory
        // https://wiki.sei.cmu.edu/confluence/display/cplusplus/MEM54-CPP.+Provide+placement+new+with+properly+aligned+pointers+to+sufficient+storage+capacity
        // https://en.cppreference.com/w/cpp/types/aligned_storage
        // https://wiki.sei.cmu.edu/confluence/display/cplusplus/MEM57-CPP.+Avoid+using+default+operator+new+for+over-aligned+types
        // !
        // https://stackoverflow.com/questions/10587879/does-new-char-actually-guarantee-aligned-memory-for-a-class-type
        T *newarr = reinterpret_cast<T *>(new int8_t[n * sizeof(T)]);  // MY: alignment
        //        T* newarr = new T[n];  // <<< !!! ctor by default, but it's bad
        //        anyway

        size_t i = 0;

        try {
            std::uninitialized_copy(arr, arr + sz, newarr);  // << !!!
        } catch (...) {
            delete[] reinterpret_cast<int8_t *> newarr;
            throw;
        }
        //        try {
        //            for (; i < sz; ++i) {
        ////            newarr[i] = arr[i];  // << UB now, can't assign
        //                new(newarr + i) T(arr[i]);  // copy ctor
        //            }
        //        } catch (...) {
        //            for (size_t j = 0; j < i; ++j) {
        //                (newarr + i)->~T();
        //            }
        //            delete[] reinterpret_cast<int8_t*> newarr;
        //            throw;
        //        }

        //        delete[] /*(T*)*/arr;  // UB/ for creation [], call all dtors - we
        //        don't have sometime
        for (size_t i = 0; i < sz; ++i) {
            (arr + i)->~T();
        }
        delete[] reinterpret_cast<int8_t *>(arr);  // no dtros will be called
        arr = newarr;
        cap = n;
    }

    // ctor by default
    void resize(size_t n, const T &value = T()) {
        if (n > cap) reserve(n);

        for (size_t i = sz; i < n; ++i) {
            //            arr[i] = value;
            new (arr + i) T(value);
        }

        if (n < sz) {
            sz = n;  // for simplicity
        }
    }

    // shrink_to_fit - later

    void push_back(const T &value) {
        if (cap == sz) {
            reserve(2 * sz);
        }

        //        arr[sz] = value;
        new (arr + sz) T(value);
        ++sz;
    }

    void pop_back() {
        --sz;
        (arr + sz)->~T();
    }

    T &operator[](size_t i) { return arr[i]; }

    const T &operator[](size_t i) const { return arr[i]; }

    T &at(size_t i) {
        if (i >= sz) {
            throw std::out_of_range("...");
        }
        return arr[i];
    }
};

// MY: static_vector
// https://en.cppreference.com/w/cpp/types/aligned_storage

// 9.2 Vector<bool>
template <>
class Vector<bool> {
    uint8_t *arr;

private:
    struct BitReference {
        uint8_t *bucket_ptr;
        uint8_t pos;

        BitReference operator=(bool b) {
            if (b) {
                *bucket_ptr |= ((uint8_t)1 << pos);
            } else {
                *bucket_ptr &= ~((uint8_t)1 << pos);
            }
            return *this;
        }
    };

public:
    BitReference operator[](size_t i) {
        uint8_t pos = i % 8;
        uint8_t *ptr = arr + i / 8;
        return BitReference(ptr, pos);
    }
};

// Type punning
// https://www.youtube.com/watch?v=_qzMpk-22cc&ab_channel=CppCon
// UB https://www.youtube.com/watch?v=XEXpwis_deQ&ab_channel=CppCon

class C {
    template <typename U>
    C(const U &) = delete;
};

int main3() {
    std::vector<int> v(10);
    v.size();

    std::vector<bool> vb(10, false);
    C c(vb[5]);
}

// C++23 - list/map/unordered_map
// deque - push_front/pop_front
// Uninit backets - rollback ctors

// Node* pnode = new Node(<>)??? T init?

// node = (reinterpret_cast)new char[sizeof(Node)];
// pn->next = ...  << UB?? Lifetime?
// new (&(pn->value)) T(...);

// new Node(...,...);  << better, without manual alloc
//  splice
//  can write good allocator

// 9.5 map<key, value, cmp=std::less<key>>
