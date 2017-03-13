/*
 * implement dup() and dup2() using fcntl() and close()
 */
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "../../lib/error_functions.h"

int mydup(int oldfd)
{
    /* check if oldfd valid */
    if (fcntl(oldfd, F_GETFL) == -1) {
        errno = EBADF;
        return -1;
    }

    /* duplicate oldfd into newfd,
     * using lowest unused file descriptor
     * greater than or equal to 0 */
    return fcntl(oldfd, F_DUPFD, 0);
}

int mydup2(int oldfd, int newfd)
{
    /* check if oldfd valid */
    if (fcntl(oldfd, F_GETFL) == -1) {
        errno = EBADF;
        return -1;
    }

    if (oldfd == newfd)
        return newfd;

    close(newfd);
    return fcntl(oldfd, F_DUPFD, newfd);
}

/* test mydup() by moving offset on one fd, then write with the other.
 * written bytes should then appear where offset was because duplicate
 * file descriptors share an offset */
void test_mydup(char *pathname)
{
    int fd, fd2, l;
    char s[] = "foobar";
    l = strlen(s);

    fd = open(pathname, O_WRONLY);
    if (fd == -1)
        errExit("error opening %s", pathname);

    fd2 = mydup(fd);
    if (fd2 == -1)
        errExit("error duplicating file descriptor %d", fd);

    if (lseek(fd, 0, SEEK_END) == -1)
        errExit("error seeking file descriptor %d", fd);
    if (write(fd2, s, l) < l)
        errExit("error writing to file descriptor %d", fd2);
}


/* test mydup2 by opening a file, then duplicating into stdout's fd,
 * writing to stdout should then write to file instead */
void test_mydup2(char *pathname)
{
    int fd, fd2, l;

    char s[] = "foobar";
    l = strlen(s);

    fd = open(pathname, O_WRONLY);
    if (fd == -1)
        errExit("error opening %s", pathname);

    if ((fd2 = mydup2(fd, 1)) != 1)
        errExit("error duplicating fd into 1");

    if (write(fd2, s, l) < l)
        errExit("error writing to file descriptor %d", fd2);
}

/* test mydup() and mydup2()
 * first flag is name of function to test (mydup or mydup2)
 * second flag is file to test with (file should already be created
 * and contain some bytes) */
int main(int argc, char *argv[])
{
    if (argc != 3)
        usageErr("%s function file\n", argv[0]);

    if (strcmp(argv[1], "mydup"))
        test_mydup(argv[2]);

    if (strcmp(argv[1], "mydup2"))
        test_mydup2(argv[2]);
}
