/*
 * Write a program like cp, but create holes in target file
 * if source file also has holes.
 */

#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../lib/error_functions.h"

int main(int argc, char *argv[])
{
    int i, inputFd, outputFd, openFlags;
    ssize_t n;
    mode_t filePerms;
    struct stat sb;
    char *buf;

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s input-file output-file", argv[1]);

    /* open files */
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
        errExit("open %s", argv[1]);

    openFlags = O_WRONLY | O_CREAT | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1)
        errExit("open %s", argv[2]);

    /* allocate buffer of current block size */
    if (fstat(outputFd, &sb) == -1)
        errExit("stat %s", argv[2]);
    buf = malloc(sb.st_blksize);

    /* copy bytes to output file by block,
     * if an entire block is null, then seek forward
     * one block, creating a file hole */
    while ((n = read(inputFd, buf, sb.st_blksize)) > 0) {
        for (i = 0; i < n && *(buf+i) == '\0'; i++)
            ;

        if (i == sb.st_blksize) {
            if (lseek(outputFd, sb.st_blksize, SEEK_CUR) == -1)
                errExit("lseek");
        }
        else if (write(outputFd, buf, n) != n)
            fatal("couldn't write whole buffer");
    }

    free(buf);

    if (n == -1)
        errExit("read");

    if (close(inputFd) == -1)
        errExit("close");

    if (close(outputFd) == -1)
        errExit("close");

    exit(EXIT_SUCCESS);
}
