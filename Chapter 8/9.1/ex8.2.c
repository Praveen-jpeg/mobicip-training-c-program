#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define EOF     (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20
#define PERMS   0666

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int fd;

    char read;
    char write;
    char unbuf;
    char eof;
    char err;
} FILE;

/* standard streams */
FILE _iob[OPEN_MAX] = {
    { 0, NULL, NULL, 0, 1, 0, 0, 0, 0 },
    { 0, NULL, NULL, 1, 0, 1, 0, 0, 0 },
    { 0, NULL, NULL, 2, 0, 1, 1, 0, 0 }
};

#define getc(p) (--(p)->cnt >= 0 \
                ? (unsigned char)*(p)->ptr++ \
                : _fillbuf(p))

FILE *fopen(char *name, char *mode);
int _fillbuf(FILE *fp);

/* fopen */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (!fp->read && !fp->write)
            break;

    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);

    if (fd == -1)
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->ptr = NULL;

    fp->read  = (*mode == 'r');
    fp->write = (*mode != 'r');
    fp->unbuf = 0;
    fp->eof   = 0;
    fp->err   = 0;

    return fp;
}

/* _fillbuf */
int _fillbuf(FILE *fp)
{
    int bufsize;

    if (!fp->read || fp->eof || fp->err)
        return EOF;

    bufsize = fp->unbuf ? 1 : BUFSIZE;

    if (fp->base == NULL)
        if ((fp->base = (char *)malloc(bufsize)) == NULL) {
            fp->err = 1;
            return EOF;
        }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (fp->cnt <= 0) {
        if (fp->cnt == 0)
            fp->eof = 1;
        else
            fp->err = 1;
        fp->cnt = 0;
        return EOF;
    }

    fp->cnt--;
    return (unsigned char)*fp->ptr++;
}

/* test main */
int main(int argc, char *argv[])
{
    FILE *fp;
    int c;

    if (argc != 2) {
        write(2, "usage: ex8.2 file\n", 18);
        return 1;
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        write(2, "can't open file\n", 16);
        return 1;
    }

    while ((c = getc(fp)) != EOF)
        write(1, &c, 1);

    return 0;
}
