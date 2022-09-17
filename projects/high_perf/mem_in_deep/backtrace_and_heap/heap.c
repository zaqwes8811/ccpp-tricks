#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>

extern void backtrace();

void *malloc(size_t sz) {
    backtrace();
    void *(*libc_malloc)(size_t) = dlsym(RTLD_NEXT, "malloc");
    return libc_malloc(sz);
}

void free(void *p) {
    // backtrace();  // core dump
    void (*libc_free)(void *) = dlsym(RTLD_NEXT, "free");
    libc_free(p);
}