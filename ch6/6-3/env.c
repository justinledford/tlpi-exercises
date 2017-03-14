/*
 * implement setenv() and unsetenv()
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../lib/error_functions.h"

extern char **environ;

int mysetenv(const char *name, const char *value, int overwrite)
{
    char *var;

    /* variable already exists and overwrite off */
    if (getenv(name) != NULL && overwrite == 0)
        return 0;

    var = malloc(strlen(name) + strlen(value) + 2);

    sprintf(var, "%s=%s", name, value);

    if (putenv(var) == 0)
        return 0;
    else
        return -1;
}

int myunsetenv(const char *name)
{
    char **tp, **pp;
    size_t len;

    /* find target to unset */
    for (tp = environ, len = strlen(name); *tp != NULL; tp++)
        if (strncmp(*tp, name, len) == 0)
            break;

    /* target not found */
    if (*tp == NULL)
        return 0;

    /* target is last var */
    if (*(tp+1) == NULL) {
        *tp = NULL;
        return 0;
    }

    /* find last var to replace target with */
    for (pp = tp; *(++pp + 1) != NULL;)
        ;

    *tp = *pp;
    *pp = NULL;

    return 0;
}

void printenv()
{
    char **ep;

    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);
}

int main()
{
    puts("testing overwriting SHELL...\n");
    if (mysetenv("SHELL", "/foo/bar", 1) != 0)
        errExit("error setting SHELL=/foo/bar");

    printf("new SHELL: %s\n", getenv("SHELL"));

    puts("clearing env vars...\n");
    clearenv();

    puts("testing setenv with FOO=bar, BAZ=quux\n");
    if (mysetenv("FOO", "bar", 0) != 0)
        errExit("error setting FOO=bar");

    if (mysetenv("BAZ", "quux", 0) != 0)
        errExit("error setting BAZ=quux");

    printenv();

    puts("testing unsetenv FOO\n");
    myunsetenv("FOO");
    printenv();
}
