// http://en.wikibooks.org/wiki/Optimizing_C%2B%2B

/// Есть цикл разработки, как в курсе по cuda for NVIDIA
// design -> impl -> func. testing -> opt 

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
