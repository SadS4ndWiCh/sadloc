#include <stdio.h>

#include "sadloc.h"

#define ASSERT(expr, message) \
    if (expr) printf("[\033[92m+\033[m] "message"\n"); \
    else { \
        printf("[\033[91m-\033[m] "message"\n"); \
        return 1; \
    }

int main(void) {
    int *ages = sadloc(sizeof(int) * 5);
    ASSERT(ages != NULL, "Should be able to allocate an array of ages");

    for (int i = 0; i < 5; i++) ages[i] = 21;
    ASSERT(1, "Should be able to assign to memory block without error");

    int *many_ages = sadreloc(ages, sizeof(int) * 10);
    ASSERT(many_ages != NULL, "Should be able to grow the array of ages");

    for (int i = 0; i < 10; i++) ages[i] = 21;
    ASSERT(1, "Should be able to assign to new memory block without error");

    sadfree(many_ages);
    sadfree(ages);

    return 0;
}