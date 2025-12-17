#include <stdio.h>

#define TABSIZE 4

int main() {
    int c, column = 0, space_count = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            space_count++;
            column++;
            if (column % TABSIZE == 0) {
                putchar('\t'); // replace spaces with tab
                space_count = 0;
            }
        } else {
            for (int i = 0; i < space_count; i++)
                putchar(' '); // print leftover spaces
            space_count = 0;

            putchar(c);
            if (c == '\n')
                column = 0;
            else
                column++;
        }
    }
    return 0;
}
