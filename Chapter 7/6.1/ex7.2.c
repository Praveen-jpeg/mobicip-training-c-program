#include <stdio.h>
#include <ctype.h>

#define MAXCOL 60

/*
 * Print input sensibly:
 *  - printable characters printed as-is
 *  - non-graphic characters printed in hex
 *  - break lines longer than MAXCOL
 */
int main(void)
{
    int c;
    int col = 0;

    while ((c = getchar()) != EOF) {
        if (isprint(c)) {
            putchar(c);
            col++;
        } else {
            printf("\\x%02X", c & 0xff);
            col += 4;
        }

        if (col >= MAXCOL) {
            putchar('\n');
            col = 0;
        }
    }
    return 0;
}
