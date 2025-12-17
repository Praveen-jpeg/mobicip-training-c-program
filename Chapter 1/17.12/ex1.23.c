#include <stdio.h>

int main() {
    int c, next;
    while ((c = getchar()) != EOF) {
        if (c == '/') {
            next = getchar();
            if (next == '/') {
                // skip single-line comment
                while ((c = getchar()) != EOF && c != '\n');
                if (c == '\n') putchar('\n');
            } else if (next == '*') {
                // skip multi-line comment
                int prev = 0;
                while ((c = getchar()) != EOF) {
                    if (prev == '*' && c == '/') break;
                    prev = c;
                }
            } else {
                putchar(c);
                if (next != EOF) putchar(next);
            }
        } else if (c == '"' || c == '\'') {
            // print strings and char literals unchanged
            int quote = c;
            putchar(c);
            while ((c = getchar()) != EOF) {
                putchar(c);
                if (c == quote) break;
                if (c == '\\') {
                    c = getchar();
                    putchar(c);
                }
            }
        } else {
            putchar(c);
        }
    }
    return 0;
}
