#include <stdio.h>

int main(void) {
    int c;
    int freq[128] = {0};  /* ASCII character frequencies */

    /* count each character */
    while ((c = getchar()) != EOF)
        if (c >= 0 && c < 128)
            freq[c]++;

    /* print histogram */
    for (int i = 0; i < 128; i++) {
        if (freq[i] > 0) {
            if (i >= 32 && i <= 126)
                printf("'%c' | ", i);   /* printable */
            else
                printf("%3d | ", i);    /* non-printable */
            for (int j = 0; j < freq[i]; j++)
                putchar('*');
            putchar('\n');
        }
    }

    return 0;
}
