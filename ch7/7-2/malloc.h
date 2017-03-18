#ifndef MALLOC_H
#define MALLOC_H

#include <unistd.h>

struct free_list {
    size_t length;
    struct free_list *prev;
    struct free_list *next;
};

static struct free_list *free_blocks;

void *mymalloc(size_t);
void free(void *ptr);

#endif
