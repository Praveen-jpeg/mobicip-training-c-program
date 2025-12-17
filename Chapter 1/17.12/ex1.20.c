#include <stdio.h>

#define TABSIZE 4  // Tab stops every 4 columns

int main() {
    int c, column = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int spaces = TABSIZE - (column % TABSIZE); // spaces to next tab stop
            for (int i = 0; i < spaces; i++)
                putchar(' ');
            column += spaces;
        } else if (c == '\n') {
            putchar(c);
            column = 0;
        } else {
            putchar(c);
            column++;
        }
    }
    return 0;
}
