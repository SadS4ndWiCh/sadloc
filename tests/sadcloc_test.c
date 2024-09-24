#include <stdio.h>

#include "sadloc.h"

#define ASSERT(expr, message) \
    if (expr) printf("[\033[92m+\033[m] "message"\n"); \
    else { \
        printf("[\033[91m-\033[m] "message"\n"); \
        return 1; \
    }

int main(void) {
    size_t total_ages = 5;
    int *ages = sadcloc(total_ages, sizeof(int));
    ASSERT(ages != NULL, "Should be able to allocate an array of int");

    for (size_t i = 0; i < total_ages; i++) {
        ASSERT(ages[i] == 0, "Element should be initialize with 0");
    }

    ages[2] = 10;
    ASSERT(ages[2] == 10, "Should be able to assign a value to any position");

    sadfree(ages);
    return 0;
}