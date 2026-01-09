/* ex8.1.c
 * A version of cat using read, write, open, close
 * K&R Exercise 8-1
 */

#include <unistd.h>   /* read, write, close */
#include <fcntl.h>    /* open */
#include <stdio.h>    /* fprintf */
#include <stdlib.h>   /* exit */

#define BUFSIZE 4096

void filecopy(int fd);

int main(int argc, char *argv[])
{
    int fd;

    if (argc == 1) {
        /* no files, copy stdin */
        filecopy(0);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                fprintf(stderr, "cat: can't open %s\n", *argv);
                exit(1);
            }
            filecopy(fd);
            close(fd);
        }
    }
    return 0;
}

/* filecopy: copy file fd to stdout */
void filecopy(int fd)
{
    int n;
    char buf[BUFSIZE];

    while ((n = read(fd, buf, BUFSIZE)) > 0)
        write(1, buf, n);
}
