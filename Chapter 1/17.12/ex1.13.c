#include <stdio.h>

#define MAXLEN 20   /* maximum word length counted */

int main(void) {
    int c, len = 0;
    int wl[MAXLEN + 1] = {0};  /* wl[i] = number of words of length i */

    /* read input and count word lengths */
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (len > 0) {
                if (len > MAXLEN)
                    len = MAXLEN;   /* clamp long words */
                wl[len]++;
                len = 0;
            }
        } else {
            len++;
        }
    }

    /* print histogram */
    for (int i = 1; i <= MAXLEN; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < wl[i]; j++)
            putchar('*');
        putchar('\n');
    }

    return 0;
}
