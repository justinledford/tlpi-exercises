/*
 *  open file with O_APPEND, seek to beginning and write,
 *  where does data appear?
 *
 *  data appears at end of file because the file offset
 *  is positioned at the end of file before each write
 */
#include <fcntl.h>
#include <unistd.h>

#include "../../lib/error_functions.h"

int main(int argc, char **argv)
{
    int fd;

    fd = open(argv[1], O_WRONLY | O_APPEND);
    if (fd == -1)
        errExit("error opening %s", argv[1]);
    if (lseek(fd, 0, SEEK_SET) == -1)
        errExit("error seeking");
    if (write(fd, "bar", 3) < 3)
        errExit("error writing");
    if (close(fd) == -1)
        errExit("error closing %s", argv[1]);
}
