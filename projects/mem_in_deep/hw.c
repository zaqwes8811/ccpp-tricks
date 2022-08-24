#include <stdint.h>
#include <stdio.h>

int kern(float* p, int32_t* k) {
    p[9] = 10;
    return 0;
}

int main() { printf("Hello World!\n"); }
