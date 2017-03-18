#include "malloc.h"

/*
 * scan list of free blocks looking for block as big
 * or bigger than size
 *      if block found and same size, return
 *      if block found and bigger, split, place remaining
 *      into free list, return
 * if no block found in free list, increase heap with
 * sbrk(), put excess memory in free list
 *
 * place size_t of number of bytes as first bytes in block,
 * return next block
 *
 */
void *mymalloc(size_t size)
{
    struct free_list **fp;
    int pagesize, blocksize, offset;
    void *allocedp, *brkp;
    size_t newlength;

    fp = &free_blocks;

    while (*fp != NULL && (*fp)->length < size)
        fp = &(*fp)->next;

    /* couldn't find big enough block or list just empty */
    if (*fp == NULL) {
        pagesize = getpagesize();
        blocksize = pagesize * ((size + sizeof(size_t))/pagesize+1);

        /* increase heap size */
        brkp = sbrk(blocksize);

        /* set length and get pointer to new block */
        *(size_t *)brkp = size;
        allocedp = brkp + sizeof(size_t);

        /* place remaining block onto free_blocks */
        *fp = brkp + size + sizeof(size_t);
        (*fp)->length = blocksize - size - sizeof(size_t);
        (*fp)->next = NULL;
        (*fp)->prev = NULL;

        return allocedp;
    } else {
        /* found free block with same size */
        if ((*fp)->length == size) {

            allocedp = *fp;

            /* connect previous and next blocks in list */
            if ((*fp)->prev)
                (*fp)->prev->next = (*fp)->next;
            if ((*fp)->next)
                (*fp)->next->prev = (*fp)->prev;
            *fp = NULL;
            return allocedp;
        }
        /* found free block with bigger size, so split */
        else {
            newlength = (*fp)->length - size;

            (*fp)->length = size;
            allocedp = (*fp)+sizeof(size_t);

            /* set up newly split block */
            offset = size+sizeof(size_t);
            (*fp+offset)->prev = (*fp)->prev;
            (*fp+offset)->next = (*fp)->next;

            if ((*fp)->prev)
                (*fp)->prev->next = *fp+offset;

            if ((*fp)->next)
                (*fp)->next->prev = *fp+offset;

            (*fp+offset)->length = newlength;
            *fp = *fp+offset;

            return allocedp;
        }
    }
}
