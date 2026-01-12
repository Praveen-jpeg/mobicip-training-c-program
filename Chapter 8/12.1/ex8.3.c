/* Program 8.3 : Implementation of _flushbuf, 
    fflush, fclose*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define EOF     (-1)
#define BUFSIZ  1024
#define OPEN_MAX 20

/* flags */
#define _READ   01
#define _WRITE  02
#define _UNBUF  04
#define _EOF    010
#define _ERR    020

typedef struct _iobuf {
    int cnt;        /* characters left */
    char *ptr;      /* next character position */
    char *base;     /* buffer base */
    int flag;       /* file access mode */
    int fd;         /* file descriptor */
} FILE;

FILE _iob[OPEN_MAX];

/* flush output buffer */
int _flushbuf(int c, FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
        return EOF;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL) {
        fp->base = (char *) malloc(bufsize);
        if (fp->base == NULL) {
            fp->flag |= _ERR;
            return EOF;
        }
    } else {
        if (write(fp->fd, fp->base, fp->ptr - fp->base)
            != fp->ptr - fp->base) {
            fp->flag |= _ERR;
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = bufsize - 1;
    *fp->ptr++ = c;

    return c;
}

/* flush file fp or all files if fp is NULL */
int fflush(FILE *fp)
{
    int i;

    if (fp == NULL) {
        for (i = 0; i < OPEN_MAX; i++)
            if (_iob[i].flag & _WRITE)
                fflush(&_iob[i]);
        return 0;
    }

    if (!(fp->flag & _WRITE) || fp->base == NULL)
        return 0;

    if (write(fp->fd, fp->base, fp->ptr - fp->base)
        != fp->ptr - fp->base) {
        fp->flag |= _ERR;
        return EOF;
    }

    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 0 : BUFSIZ;
    return 0;
}

/* close a file */
int fclose(FILE *fp)
{
    int rc;

    rc = fflush(fp);
    free(fp->base);

    fp->base = NULL;
    fp->ptr = NULL;
    fp->cnt = 0;
    fp->flag = 0;

    return close(fp->fd) == -1 ? EOF : rc;
}

int main(void)
{
    FILE *fp;
    int i;

    fp = &_iob[3];
    fp->fd = open("ex83.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    fp->flag = _WRITE;
    fp->base = NULL;

    for (i = 0; i < 10; i++)
        _flushbuf('A' + i, fp);

    fclose(fp);
    return 0;
}
