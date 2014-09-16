// http://en.wikibooks.org/wiki/Optimizing_C%2B%2B

/// Есть цикл разработки, как в курсе по cuda for NVIDIA
// design -> impl -> func. testing -> opt(tune) 

/// http://docs.nvidia.com/cuda/cuda-c-best-practices-guide/#axzz3DSbhUarY
// APOD - Assess, Parallelize, Optimize, Deploy(APOD)

// DANGER: хорошо если дизайн ортогональный, тогда оптимизируются изолированные части, но если нет, то проблему 
//   не всегда ясно решать даже анализирую профайлером.

/*
APOD cycle >- analyse - parall - opt - deploy

"
The performance of an application has nothing to do with the language. 
The most important factor is the application architecture. (!!! не всегда начинают с этого)

Then comes algorithmic efficiency. 
Then micro-optimizations. 
Then comes the quality of the compiler/interpreter. 
Then the CPU. Maybe a couple of other steps in between. The language, however, doesn't directly play a role." 
http://stackoverflow.com/questions/3723374/how-fast-is-javascript-compared-to-java

http://blog.codinghorror.com/why-arent-my-optimizations-optimizing/

NVIDIA CUDA Course
- Picking good algorithm
- Basic principles for efficiency (cache frendly, vectorization)
- Arch-specific detailed opt
- m-opt

*/

/*
/// @BIG: general
/// Performance improving features
- The most efficient types
- Function-objects - лучше их передавать, а не указатели на функции
- qsort and bsearch functions - sort and lower_bound insted
- Encapsulated collections - не всегда известно на момент дизайна какая коллекция нужна. Но в Мейсере написано про то что
   не стоит надеятся на контейнероно независимый код.
- When using an STL container, if several equivalent expressions have the same performance, choose the more general expression.
  empty, distance(), iter != insted size == 0, it-it
- var length cont - vector - and the greatest locality of reference.
- Inlined functions - no function call overhead -  In addition, since inline code is near to the caller code, it has better locality of reference.
  локальны не только данные, но и код, он же тоже в памяти - http://codeblab.com/2009/12/code-locality/
  http://stackoverflow.com/questions/7811792/confused-between-temporal-and-spatial-locality-in-real-life-code
  но профайлер не видит заинлайненные функции
- To represent internal symbols, use enumerations instead of strings. enum directions { North, South, East, West };
- As constants for switch statements cases, use compact sequences of values, that is, sequences with no gaps or with few small gaps.
- In a loop that calls a function with more arguments than there are registers, consider passing a struct or object instead.
   (? вызов функции дорого, но можно ускорить если аргументы как-то соотносятся с какими-то регистрами). Не очень понял, но как понял много аргументов
   лучше запковкать для перадчи.
- To search for an element in a container, use a container member function instead of an STL algorithm.
- To search a sorted sequence, use the std::lower_bound, std::upper_bound, std::equal_range, or std::binary_search generic algorithms.
- static member functions - спорно - см. Мишко

// Performance worsening features
- The throw operator
- virtual member functions
- virtual inheritance
- Do not define templates of polymorphic classes. In other words, 
   don't use the "template" and the "virtual" keywords in the same class definition.
- Use of automatic deallocators - GC and ref. counting; auto_ptr - вроде бы довольно эффективный
- The volatile modifier

// Constructions and destructions
- Variable scope[edit]. Declare variables as late as possible.
- Use initializations instead of assignments. In particular, in constructors, use initialization lists.
- ++i, --i
- Use the assignment composite operators (like in a += b) instead of simple operators combined with assignment operators (like in a = a + b).
  += может не создавать временных объектов

- Function argument passing[edit]
  When you pass an object x of type T as argument to a function, use the following criterion:

  If x is an input-only argument,
    if x may be null,
      pass it by pointer to constant (const T* x),
    otherwise, if T is a fundamental type or an iterator or a function-object, (!!)
      // http://stackoverflow.com/questions/1832621/c-cpu-register-usage !! маленькие объекты могут поместиться в регистры, а не в стек
      pass it by value (T x) or by constant value (const T x),

    otherwise,
      pass it by reference to constant (const T& x),
  otherwise, i.e. if x is an output-only or input/output argument,
    if x may be null,
      pass it by pointer to non-constant (T* x),
    otherwise,
      pass it by reference to non-constant (T& x).

- Declare as explicit all constructors that receive only one argument, except for the copy constructors of concrete classes.
- Declare conversion operators only to keep compatibility with an obsolete library (in C++11, declare them explicit).
- Use the Pimpl idiom only when you want to make the rest of the program independent from the implementation of a class.
  It should not, therefore, be used for classes whose public member functions are called frequently.

- Iterators and function objects[edit] Ensure that custom iterators and function objects are tiny and do not allocate dynamic memory.

/// Allocations and deallocations
- Fixed length arrays - замена вектору, в нем доступ к куче
- Allocating many small objects[edit] If you have to allocate many objects of the same size, use a block allocator.

/// Memory access
- Access memory in increasing addresses order. In particular: 
   3) in class constructors and in assignment operators (operator=), access member variables in the order of declaration.
- Keep the compiler default memory alignment.
- Grouping functions in compilation units - не понял
- Define every global variable in the compilation unit in which it is used most often.
- Private functions and variables in compilation units

/// Thread usage
- In a multicore system, if you can split a CPU-intensive operation across several threads, use as many worker threads as there are processor cores.
- Use of multi-threaded libraries.
  If you are developing a single-threaded application, don't use libraries designed only for multi-threaded applications.
- ...

/// Input/Output
- Store text files in a compressed format[edit] Disk have much less bandwidth than processors. 
  By (de)compressing on the fly, the CPU can speed up I/O. Ну наверное, для конф. файлов точно не подходит, если они не меняются из
  интефейса.
- Binary format[edit] Instead of storing data in text mode, store them in a binary format.
- Open files[edit] Instead of opening and closing an often needed file every 
  time you access it, open it only the first time you access it, and close it when you are finished using it.
  Так делал - типа уменьшал область видимости. Но тут нужно аккуратно. Да уменьшать нужно, но открывать часто не стоит.
- Instead of doing many I/O operations on single small or tiny objects, do I/O operations on a 4 KB buffer containing many objects.
- Memory-mapped file

/// Memoization - короче кеширование - там трюки со static 
- Look-up table
- One-place cache
- N-places cache

/// Sorting
- To sort a data set according an integer key having a small range, use the counting sort algorithm.
- If you have to split a sequence according a criterion, use a partitioning algorithm, instead of a sorting one.
- If you have to partition or sort a sequence for which equivalent entities may be swapped, don't use a stable algorithm.
  те что сохраняют порядок несколько медленнее обычных
- If you have to pick out the first N elements from a sequence, 
  or the Nth element in a sequence, use an order partitioning algorithm, instead of a sorting one.
- 

/// Other techniques
- If you have to do many searches in a !!!rarely changed collection, instead of using a search tree or a hash table, 
  you can get a speed up if you put the data in an array, sort the array, and do binary searches on it. Лучше локальность ссылок
- If for a list you don't need bidirectional iterators, you don't need to insert elements at the end or before the 
  current element, and you don't need to know how many elements there are in the list, use a singly-linked list, instead of a doubly-linked list.

/// @BIG: Code optimization - only in bottlenecks after prof
/// Allocations and deallocations
- Before adding elements to a vector or to a string object, call its member function reserve with a size big enough for most cases.
- To empty a vector<T> x object without deallocating its memory, use the statement x.resize(0);;
 to empty it and deallocate its memory, use the statement vector<T>().swap(x);.
- !!!For every copyable concrete class T which, directly or indirectly, owns some dynamic memory, redefine the appropriate !!!swap functions.

/// Run-time support
- For every bottleneck, move before the bottleneck the try keywords, and after the bottleneck the matching catch clauses.
- To perform input/output operations, instead of using the C++ streams, use the old C functions, declared in the cstdio header.

// Instruction count
- In switch statements, sort the cases by decreasing probability.
- If an integer value is a constant in the application code, but is a variable in library code, make it a template parameter.
- If you have to write a library abstract base class such that in every algorithm 
  in the application code only one class derived from such base class will be used, use the Curiously Recurring Template Pattern.
  http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
- If an object that implements the Strategy design pattern (aka Policy) is a constant in every algorithm of the 
  application code, eliminate such an object, make static all its members, and add its class as a template parameter.

// Constructions and destructions
- For non-inlined functions, try to declare a return type for which an object 
  copy moves no more than 8 bytes. If unfeasible, at least construct the result object in the return statement.
- If a variable is declared in the body of a loop, and an assignment to it costs less 
  than a construction plus a destruction, move that declaration before the loop.
- To avoid costly conversions, define overloaded functions for the most typical argument types.

// Pipeline - Modern processors handle branches efficiently only if they can predict them. 
// In bottlenecks, the hard-to-predict branches should be avoided.
- Instead of a conditional expression in which both cases are constants, use a look-up table with two-places.

// Memory access
- Put near in the same compilation unit all the function definitions belonging to the same bottleneck.

// Faster operations
- Arrange the member variables of classes and structures in such a way 
  that the most used variables are in the first 128 bytes, and then sorted from the longest object to the shortest.
  The sorting minimized the paddings (or holes) caused by the alignment requirements, and so generates a more compact structure.
- http://www.graphics.stanford.edu/~seander/bithacks.html
- Instead of processing a single array of aggregate objects, process in parallel two or more arrays having the same length.
  interlive can help*/

/// From Alexandresky
// http://www.slideshare.net/andreialexandrescu1/three-optimization-tips-for-c

/// Facebook
// https://www.facebook.com/notes/facebook-engineering/three-optimization-tips-for-c/10151361643253920

/*
Commonly given advice about approaching optimization in general, and optimization of C++ code in particular, includes:
- Quoting Knuth more or less out of context
- The classic one-two punch: (a) Don't do it; (b) Don't do it yet
- Focus on algorithms, not on micro-optimization
- Most programs are I/O bound (!!) отсюда процветание асинхронности?
- Avoid constructing objects unnecessarily
- Use C++11's rvalue references to implement move constructors

// other
- Minimize array writes. Save for a few obvious patterns, array accesses are not registered.
  (!!!) Don't forget--computers are good at computation. The whole business of dealing with memory is more awkward.
*/