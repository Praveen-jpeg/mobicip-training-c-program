/* test_stdio.c */

#include <unistd.h>

/* forward declarations from stdio_field.c */
typedef struct _iobuf FILE;
FILE *fopen(char *, char *);
int _fillbuf(FILE *);

#define EOF (-1)
#define getc(p)   (--(p)->cnt >= 0 \
                    ? (unsigned char)*(p)->ptr++ \
                    : _fillbuf(p))

int main(int argc, char *argv[])
{
    FILE *fp;
    int c;

    if (argc != 2) {
        write(2, "usage: test file\n", 17);
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
