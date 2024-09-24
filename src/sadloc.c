#include <unistd.h>
#include <stdlib.h>

#include "sadloc.h"

/*
    The `sbrk(size)` can allocate a block memory by increasing the `program break` 
    or deallocate by decrement the `program break`.

    With `size == 0`, it gives the current address of the program.
    With `size > 0`, it increments the program break by `x bytes`.
    With `size < 0`, it decrements the program break by `x bytes`.

    On failure, it returns `(void *) -1`.
*/

void *sadloc(size_t size) {
    void *block;

    block = sbrk(size);
    if (block == (void *) -1) return NULL;

    return block;
}