// Только после профелирования!!!

// Troubles:
//   http://stackoverflow.com/questions/15083121/custom-pooled-allocator-in-c-besides-boostpool

// Stack allocation
//   http://www.codeguru.com/cpp/article.php/c18503/C-Programming-Stack-Allocators-for-STL-Containers.htm
//   http://anki3d.org/cpp-allocators-for-games/
//    "To understand the problem better we need first to understand that malloc and free 
//    work optimally when we allocate big chunks and we don’t call them that often."
//
//   http://www.drdobbs.com/cpp/improving-performance-with-custom-pool-a/184406243
//   http://yosefk.com/blog/why-custom-allocatorspools-are-hard.html