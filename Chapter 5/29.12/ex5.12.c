#include <stdio.h>
#include <stdlib.h>

/*
 Exercise 5-12:
  - Extends entab/detab with shorthand -m +n
  - -m : starting column
  - +n : tab width
*/

int main(int argc, char *argv[])
{
    int start = 0, width = 8;
    int c, col = 0;

    while (--argc > 0) {
        if ((*++argv)[0] == '-')
            start = atoi(argv[0] + 1);
        else if ((*argv)[0] == '+')
            width = atoi(argv[0] + 1);
    }

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int spaces = width - ((col - start) % width);
            while (spaces-- > 0) {
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
