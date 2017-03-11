/*
 * write a program that creates a file and writes a number
 * of bytes, with a flag to use O_APPEND or seek before each write
 *
 * run two instances at same time on same file, once with flag on,
 * and once with flag off, then compare sizes
 *
 * running with the flag on results in the file having a smaller
 * size than the other, this is because seek and write
 * are not called atomically, so some bytes were overwritten
 */

#include <fcntl.h>
#include <unistd.h>

#include "../../lib/error_functions.h"
#include "../../lib/get_num.h"

int main(int argc, char *argv[])
{
    int fd, seek, flags, b, i;
    mode_t filePerms;
    long numBytes;

    if (argc < 2 || argc > 4)
        usageErr("%s filename num-bytes [x]\n", argv[0]);

    seek = (argc == 3) ? 1 : 0;

    numBytes = getLong(argv[2], GN_NONNEG | GN_GT_0, "num-bytes");

    flags = O_WRONLY | O_CREAT;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    if (seek)
        flags |= O_APPEND;

    fd = open(argv[1], flags, filePerms);
    if (fd == -1)
        errExit("error opening %s", argv[1]);

    for(i = 0, b = 'a'; i < numBytes; i++) {
        if (seek)
            lseek(fd, 0, SEEK_END);
        if (write(fd, &b, 1) < 1)
            errExit("error on write");
    }
}
