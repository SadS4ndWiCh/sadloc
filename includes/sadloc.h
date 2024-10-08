#include <stdlib.h>

#ifndef _SADLOCH_
#define _SADLOCH_

typedef char ALIGN[16];

union header {
    struct {
        size_t size;        // Block of memory's size
        unsigned is_free;   // Flag if block of memory is free
        union header *next; // Pointer to next block of memory
    } s;

    ALIGN stup;
};

// Block of memory's header info
typedef union header header_t;

// Alloc a block of memory of given `size`
void *sadloc(size_t size);

// Free a block of memory
void sadfree(void *block);

// Allocate memory for an array of `nmemb` elements of `size` bytes each and 
// return a pointer to it
void *sadcloc(size_t nmemb, size_t size);

// Changes the size of the memory block pointed to by `ptr` to `size` bytes.
void *sadreloc(void *ptr, size_t size);

// Return the first free block of memory of the given size (first-fit)
header_t *get_free_block(size_t size);

#endif