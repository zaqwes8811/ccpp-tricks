// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2271.html
// http://stackoverflow.com/questions/826569/compelling-examples-of-custom-c-allocators

// Theory:
// http://blogs.msdn.com/b/calvin_hsia/archive/2010/03/16/9979985.aspx
// !! http://blogs.msdn.com/b/vcblog/archive/2008/08/28/the-mallocator.aspx

// About rebind:
//   http://stackoverflow.com/questions/4062503/stl-allocator-copy-constructor-of-other-type-rebind

// Troubles:
//   https://ez.analog.com/message/13396

// Q: vector<> need continue alloc. How it apply here?

// Q: "node-based" containers. Hmm...
// http://www.qnx.com/developers/docs/660/index.jsp?topic=%2Fcom.qnx.doc.dinkum%2Ftopic%2Fcpp11%2Findex_alloc.html

#include <gtest/gtest.h>

// The following headers are required for all allocators.
#include <stddef.h>  // Required for size_t and ptrdiff_t and NULL
#include <new>       // Required for placement new and std::bad_alloc
#include <stdexcept> // Required for std::length_error

// The following headers contain stuff that Mallocator uses.
#include <stdlib.h>  // For malloc() and free()
#include <iostream>  // For std::cout
#include <ostream>   // For std::endl

// The following headers contain stuff that main() uses.
//#include <list>      // For std::list
#include <vector>


// (c) Stephan T. Lavavej
template <typename T> class Mallocator {
public:

    // The following will be the same for virtually all allocators.
    typedef T * pointer;
    typedef const T * const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    T * address(T& r) const {
        return &r;
    }

    const T * address(const T& s) const {
        return &s;
    }

    size_t max_size() const {
        // The following has been carefully written to be independent of
        // the definition of size_t and to avoid signed/unsigned warnings.
        return (static_cast<size_t>(0) - static_cast<size_t>(1)) / sizeof(T);
    }


    // The following must be the same for all allocators.
    template <typename U> struct rebind {
        typedef Mallocator<U> other;
    };

    bool operator!=(const Mallocator& other) const {
        return !(*this == other);
    }

    void construct(T * const p, const T& t) const {
        void * const pv = static_cast<void *>(p);

        new (pv) T(t);
    }

    void destroy(T * const p) const; // Defined below.


    // Returns true if and only if storage allocated from *this
    // can be deallocated from other, and vice versa.
    // Always returns true for stateless allocators.
    bool operator==(const Mallocator& other) const {
        return true;
    }


    // Default constructor, copy constructor, rebinding constructor, and destructor.
    // Empty for stateless allocators.
    Mallocator() { }

    Mallocator(const Mallocator&) { }

    template <typename U> Mallocator(const Mallocator<U>&) { }

    ~Mallocator() { }


    // The following will be different for each allocator.
    T * allocate(const size_t n) const {
        // Mallocator prints a diagnostic message to demonstrate
        // what it's doing. Real allocators won't do this.
        std::cout << "Allocating " << n << (n == 1 ? " object" : " objects")
            << " of size " << sizeof(T) << "." << std::endl;

        // The return value of allocate(0) is unspecified.
        // Mallocator returns NULL in order to avoid depending
        // on malloc(0)'s implementation-defined behavior
        // (the implementation can define malloc(0) to return NULL,
        // in which case the bad_alloc check below would fire).
        // All allocators can return NULL in this case.
        if (n == 0) {
            return NULL;
        }

        // All allocators should contain an integer overflow check.
        // The Standardization Committee recommends that std::length_error
        // be thrown in the case of integer overflow.
        if (n > max_size()) {
            throw std::length_error("Mallocator<T>::allocate() - Integer overflow.");
        }

        // FIXME: it's thread safe?
        // Mallocator wraps malloc().
        void * const pv = malloc(n * sizeof(T));

        // Allocators should throw std::bad_alloc in the case of memory allocation failure.
        if (pv == NULL) {
            throw std::bad_alloc();
        }

        return static_cast<T *>(pv);
    }

    void deallocate(T * const p, const size_t n) const {
        // Mallocator prints a diagnostic message to demonstrate
        // what it's doing. Real allocators won't do this.
        std::cout << "Deallocating " << n << (n == 1 ? " object" : " objects")
            << " of size " << sizeof(T) << "." << std::endl;

        // Mallocator wraps free().
        free(p);
    }


    // The following will be the same for all allocators that ignore hints.
    template <typename U> T * allocate(const size_t n, const U * /* const hint */) const {
        return allocate(n);
    }


    // Allocators are not required to be assignable, so
    // all allocators should have a private unimplemented
    // assignment operator. Note that this will trigger the
    // off-by-default (enabled under /Wall) warning C4626
    // "assignment operator could not be generated because a
    // base class assignment operator is inaccessible" within
    // the STL headers, but that warning is useless.
private:
    Mallocator& operator=(const Mallocator&);
};

// A compiler bug causes it to believe that p->~T() doesn't reference p.

#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable: 4100) // unreferenced formal parameter
#endif

// The definition of destroy() must be the same for all allocators.
template <typename T> void Mallocator<T>::destroy(T * const p) const {
    p->~T();
}

#ifdef _MSC_VER
    #pragma warning(pop)
#endif


TEST(Alloc, Lavavej) {
    using namespace std;

    cout << "Constructing l:" << endl;

    vector<int, Mallocator<int> > l;
    l.assign(5, 1);

    cout << endl << "l.push_back(1729):" << endl;

    l.push_back(1729);

    cout << endl << "l.push_back(2161):" << endl;

    l.push_back(2161);

    cout << endl;

    for (vector<int, Mallocator<int> >::const_iterator i = l.begin(); i != l.end(); ++i) {
        cout << "Element: " << *i << endl;
    }

    cout << endl << "Destroying l:" << endl;
}


namespace no_heap_poly {
using namespace std;
// TODO: no-heap poly.
// http://www.barrgroup.com/Embedded-Systems/How-To/Polymorphism-No-Heap-Memory
typedef char Note;
class Instrument {
public:
  virtual void playNote(Note key) = 0;
};

class GenericInstrument : public Instrument {
  // буффер должен быть первой переменной?
  char buf[40];   // max size of Instr.
public:
  virtual void playNote(Note key) {
    this->playNote(key); // enforce late binding
  }
};

class Configuration {

public:
  GenericInstrument i;
};

class Piano : public Instrument {
  int attr;

public:
  Piano() { assert(sizeof(*this) <= sizeof (GenericInstrument)); }
  virtual void playNote(Note key)
  { cout << "Piano " << key << endl; }
};

class Violin : public Instrument {
  int attr1;
  int attr2;
public:
  Violin() { assert(sizeof(*this) <= sizeof (GenericInstrument)); }
  virtual void playNote(Note key)
  { cout << "Violin " << key << endl; }
};

// Mem pool?
static Configuration c1, c2;
}

TEST(Alloc, Board) {
  // Placment
  // new http://stackoverflow.com/questions/6783993/placement-new-and-delete

  //Instrument *i;
  //i = new Piano;
  //i->playNote(key);
  using namespace no_heap_poly;

  Instrument* inst = new(&c1.i) Piano;

  inst->playNote('c');
  c1.i.playNote('c');
}

/// MMap
// http://stackoverflow.com/questions/8475609/implementing-your-own-malloc-free-with-mmap-and-munmap
// http://stackoverflow.com/questions/826569/compelling-examples-of-custom-c-allocators

// Addition
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2486.pdf

