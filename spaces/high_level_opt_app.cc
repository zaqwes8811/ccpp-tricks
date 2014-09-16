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

