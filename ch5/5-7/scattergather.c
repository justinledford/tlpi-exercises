/*
 * implement readv and writev
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../lib/error_functions.h"

struct myiovec {
    void *iov_base;     /* start address of buffer */
    size_t iov_len;     /* number of bytes to transfer */
};

ssize_t myreadv(int fd, const struct myiovec *iov, int iovcnt)
{
    ssize_t n, m;

    for (n = 0, m = 0; iovcnt > 0; iovcnt--, iov++, n += m)
        if ((m = read(fd, iov->iov_base, iov->iov_len)) == -1)
            return m;

    return n;
};

ssize_t mywritev(int fd, const struct myiovec *iov, int iovcnt) {
    ssize_t n, m;

    for (n = 0, m = 0; iovcnt > 0; iovcnt--, iov++, n += m)
        if((m = write(fd, iov->iov_base, iov->iov_len)) == -1)
            return m;

    return n;
}

void test_myreadv(char *pathname)
{
    int fd, i;
    struct myiovec iov[3];

    fd = open(pathname, O_RDONLY);
    if (fd == -1)
        errExit("error opening %s\n", pathname);


    for (i = 0; i < 3; i++) {
        iov[i].iov_base = malloc(4);
        iov[i].iov_len = 4;
    }

    myreadv(fd, iov, 3);

    for (i = 0; i < 3; i++)
        puts(iov[i].iov_base);

    for (i = 0; i < 3; i++)
        free(iov[i].iov_base);
}

void test_mywritev(char *pathname)
{
    int fd, i;
    struct myiovec iov[3];

    fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1)
        errExit("error opening %s\n", pathname);


    for (i = 0; i < 3; i++) {
        iov[i].iov_base = malloc(4);
        strcpy(iov[i].iov_base, "foo");
        iov[i].iov_len = 4;
    }

    mywritev(fd, iov, 3);

    for (i = 0; i < 3; i++)
        free(iov[i].iov_base);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        usageErr("%s function file\n", argv[0]);

    if (strcmp(argv[1], "readv") == 0)
        test_myreadv(argv[2]);
    else if (strcmp(argv[1], "writev") == 0)
        test_mywritev(argv[2]);
}
