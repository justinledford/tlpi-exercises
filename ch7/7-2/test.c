#include <stdio.h>

#include "malloc.h"

int main()
{
    int *a;

    /* first call should add a block of size 4 */
    a = mymalloc(4 * sizeof(int));
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    printf("%d\n", a[0]);
    printf("%d\n", a[1]);
    printf("%d\n", a[2]);

    /* second call should find block in free_list with bigger
     * size and split it */
    a = mymalloc(4 * sizeof(int));
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    printf("%d\n", a[0]);
    printf("%d\n", a[1]);
    printf("%d\n", a[2]);

    /* here test block with same size */
    a = mymalloc(4056);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    printf("%d\n", a[0]);
    printf("%d\n", a[1]);
    printf("%d\n", a[2]);

    /* here test empty list after malloced */
    a = mymalloc(4 * sizeof(int));
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    printf("%d\n", a[0]);
    printf("%d\n", a[1]);
    printf("%d\n", a[2]);
}
