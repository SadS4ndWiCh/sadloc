#include <stdio.h>

#include "sadloc.h"

#define ASSERT(expr, message) \
    if (expr) printf("[\033[92m+\033[m] "message"\n"); \
    else { \
        printf("[\033[91m-\033[m] "message"\n"); \
        return 1; \
    }

int main(void) {
    int *age = (int *) sadloc(sizeof(int));
    ASSERT(age != NULL, "Should be able to alloc a block of memory.");

    *age = 12;

    ASSERT(*age == 12, "Should be able to store value in memory block.");
    return 0;
}