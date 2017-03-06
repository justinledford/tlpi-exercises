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
    int opt, append, *outputFds, openFlags, i;
    ssize_t n;
    mode_t filePerms;
    char buf[BUFSIZE];
    char usage[] = "%s [-a] FILE\n  -a\tappend to file\n";

    /* parse arguments */
    if (argc < 2)
        usageErr(usage, argv[0]);

    append = 0;
    while ((opt = getopt(argc, argv, ":a")) != -1) {
        switch (opt) {
            case 'a':
                append = 1;
                break;
            case '?':
                usageErr(usage, argv[0]);
                break;
            default: fatal("Unexpected case in switch()");
        }
    }

    /* open files */
    openFlags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    outputFds = malloc(sizeof(int)*(argc-optind));

    for (i = 0; i < argc-optind; i++) {
        *(outputFds+i) = open(argv[optind+i], openFlags, filePerms);
        if (*(outputFds+i) == -1)
            errExit("error opening %s", argv[optind+i]);
    }

    /* write to files */
    while ((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0) {
        for (i = 0; i < argc-optind; i++)
            if (write(*(outputFds+i), buf, n) != n)
                fatal("couldn't write whole buffer to %s", argv[optind+i]);
        if (write(STDOUT_FILENO, buf, n) != n)
            fatal("couldn't write whole buffer to stdout");
    }

    if (n == -1)
        errExit("read");

    /* clean up */
    for (i = 0; i < argc-optind; i++)
        if (close(*(outputFds+i)) == -1)
            errExit("close");

    free(outputFds);

    exit(EXIT_SUCCESS);
}
