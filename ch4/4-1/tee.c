#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../../lib/error_functions.h"

#ifndef BUFSIZE
#define BUFSIZE     1024
#endif

int main(int argc, char *argv[])
{
    int outputFd, openFlags;
    ssize_t n;
    mode_t filePerms;
    char buf[BUFSIZE];

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s output-file", argv[1]);

    openFlags = O_WRONLY | O_CREAT | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    outputFd = open(argv[1], openFlags, filePerms);
    if (outputFd == -1)
        errExit("error opening %s", argv[1]);

    while ((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0) {
        if (write(outputFd, buf, n) != n)
            fatal("couldn't write whole buffer");
        if (write(STDOUT_FILENO, buf, n) != n)
            fatal("couldn't write whole buffer");
    }

    if (n == -1)
        errExit("read");

    if (close(outputFd) == -1)
        errExit("close");

    exit(EXIT_SUCCESS);
}
