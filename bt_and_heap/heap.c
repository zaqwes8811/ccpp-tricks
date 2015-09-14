#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>

extern void backtrace();

void* malloc(size_t sz)
{
	backtrace();
    void *(*libc_malloc)(size_t) = dlsym(RTLD_NEXT, "malloc");
    //printf("malloc\n");
    return libc_malloc(sz);
}

void free(void *p)
{
    //backtrace();
    void (*libc_free)(void*) = dlsym(RTLD_NEXT, "free");
    //printf("free\n");
    libc_free(p);
}