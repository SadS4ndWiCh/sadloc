#include <stdio.h>

#include "sadloc.h"

struct person_t {
    char *name;
    unsigned char age;
};

int main(void) {
    struct person_t *me = (struct person_t *) sadloc(sizeof(struct person_t));
    me->name = "John Doe";
    me->age = 31;

    printf("Name: %s | Age: %d\n", me->name, me->age);

    sadfree(me);

    return 0;
}