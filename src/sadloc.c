#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "sadloc.h"

/*
    The `sbrk(size)` can allocate a block memory by increasing the `program break` 
    or deallocate by decrement the `program break`.

    With `size == 0`, it gives the current address of the program break.
    With `size > 0`, it increments the program break by `x bytes`.
    With `size < 0`, it decrements the program break by `x bytes`.

    On failure, it returns `(void *) -1`.
*/

header_t *head, *tail;

pthread_mutex_t sadloc_mutex;

void *sadloc(size_t size) {
    size_t total_size;
    header_t *header;
    void *block;

    if (!size) {
        return NULL;
    }

    // Prevent multiple threads to allocate at same time
    pthread_mutex_lock(&sadloc_mutex);

    header = get_free_block(size);
    if (header) {
        header->s.is_free = 0;
        pthread_mutex_unlock(&sadloc_mutex);
        return (void *) (header + 1);
    }

    total_size = sizeof(header_t) + size;

    block = sbrk(total_size);
    if (block == (void *) -1) {
        pthread_mutex_unlock(&sadloc_mutex);
        return NULL;
    }

    header = block;
    header->s.size = size;
    header->s.is_free = 0;
    header->s.next = NULL;

    if (!head) head = header;
    if (tail) tail->s.next = header;

    tail = header;

    pthread_mutex_unlock(&sadloc_mutex);
    return (void *) (header + 1);
}

header_t *get_free_block(size_t size) {
    header_t *curr = head;

    while (curr) {
        if (curr->s.is_free && curr->s.size >= size) return curr;
        curr = curr->s.next;
    }

    return NULL;
}

void sadfree(void *block) {
    header_t *header, *tmp;
    void *programbreak;

    if (!block) return;

    pthread_mutex_lock(&sadloc_mutex);
    header = (header_t *) block - 1;

    // Check if memory to free is the end of program break
    programbreak = sbrk(0);
    if ((char *)block + header->s.size == programbreak) {
        if (head == tail) {
            head = tail = NULL;
        } else {
            tmp = head;
            while (tmp) {
                if (tmp->s.next == tail) {
                    tmp->s.next = NULL;
                    tail = tmp;
                }

                tmp = tmp->s.next;
            }
        }

        // Decrease the program break by the memory block size to
        // successfuly deallocate
        sbrk(0 - sizeof(header_t) + header->s.size);
        pthread_mutex_lock(&sadloc_mutex);
        return;
    }

    header->s.is_free = 1;
    pthread_mutex_unlock(&sadloc_mutex);
}

void *sadcloc(size_t nmemb, size_t size) {
    void *block;

    if (nmemb == 0 || size == 0) return NULL;

    size_t total_size = nmemb * size;
    if (size != total_size / nmemb) return NULL;

    block = sadloc(total_size);
    if (!block) return NULL;

    for (size_t i = 0; i < total_size; i++) {
        unsigned char *c = ((unsigned char *) block) + i;
        *c = 0;
    }

    return block;
}