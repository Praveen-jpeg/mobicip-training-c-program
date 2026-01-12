/* Program 8.4 : Implementation of fseek
   Coordinated with buffered I/O */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define EOF     (-1)
#define BUFSIZ  1024

#define _READ   01
#define _WRITE  02
#define _EOF    010

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} FILE;

/* fseek implementation */
int fseek(FILE *fp, long offset, int origin)
{
    if (fp->flag & _WRITE) {
        /* flush write buffer */
        if (write(fp->fd, fp->base, fp->ptr - fp->base)
            != fp->ptr - fp->base)
            return EOF;
    }
    else if (fp->flag & _READ) {
        /* adjust offset for buffered input */
        if (origin == SEEK_CUR)
            offset -= fp->cnt;
        fp->cnt = 0;
        fp->ptr = fp->base;
    }

    if (lseek(fp->fd, offset, origin) < 0)
        return EOF;

    fp->flag &= ~_EOF;
    return 0;
}

int main(void)
{
    FILE f;
    char c;

    f.fd = open("ex83.txt", O_RDONLY);
    f.flag = _READ;
    f.cnt = 0;
    f.base = NULL;

    fseek(&f, 5L, SEEK_SET);   /* move to 6th byte */
    read(f.fd, &c, 1);
    write(1, &c, 1);           /* print to stdout */

    close(f.fd);
    return 0;
}
