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
    header_t *age_header = (header_t *) age - 1;
    ASSERT(age_header->s.is_free == 0, "Should be able to initialize a non free block of memory");
    
    sadfree(age);
    ASSERT(age_header->s.is_free == 1, "Should be able to free a memory");

    return 0;
}