
// http://stackoverflow.com/questions/262439/create-a-wrapper-function-for-malloc-and-free-in-c
#include <stdio.h>

#include <vector>

extern "C" {
void* malloc(size_t sz);
void free(void *p);
}

int main()
{
    free(malloc(10));
    std::vector<char> v(10);
    std::vector<int> vi(10);
    return 0;
}
