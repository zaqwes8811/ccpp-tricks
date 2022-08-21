
// http://stackoverflow.com/questions/262439/create-a-wrapper-function-for-malloc-and-free-in-c
#include <stdio.h>
#define UNW_LOCAL_ONLY
#include <cxxabi.h>
#include <libunwind.h>

#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
void backtrace();
}

void backtrace() {
    unw_cursor_t cursor;
    unw_context_t context;

    // Initialize cursor to current frame for local unwinding.
    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    std::printf("\n");

    // Unwind frames one by one, going up the frame stack.
    while (unw_step(&cursor) > 0) {
        unw_word_t offset, pc;
        unw_get_reg(&cursor, UNW_REG_IP, &pc);
        if (pc == 0) {
            break;
        }
        std::printf("0x%lx:", pc);

        char sym[256];
        if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
            char *nameptr = sym;
            int status;
            char *demangled = abi::__cxa_demangle(sym, 0, 0, &status);
            if (status == 0) {
                nameptr = demangled;
            }
            std::printf(" (%s+0x%lx)\n", nameptr, offset);
            std::free(demangled);
        } else {
            std::printf(" -- error: unable to obtain symbol name for this frame\n");
        }
    }
}

extern "C" {
void *malloc(size_t sz);
void free(void *p);
}

int main() {
    // free(malloc(10));
    std::vector<char> v(10);
    std::vector<int> vi(10);
    return 0;
}
