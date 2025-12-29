#include <stdio.h>
#include <stdlib.h>

#define MAXTAB 20

int main(int argc, char *argv[])
{
    int tabstops[MAXTAB];
    int ntabs = 0;
    int c, col = 0, i;

    if (argc > 1)
        while (--argc > 0)
            tabstops[ntabs++] = atoi(*++argv);

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int next = 8;
            for (i = 0; i < ntabs; i++)
                if (tabstops[i] > col)
                    next = tabstops[i] - col;
            while (next-- > 0) {
                putchar(' ');
                col++;
            }
        } else {
            putchar(c);
            col++;
        }
    }
    return 0;
}
