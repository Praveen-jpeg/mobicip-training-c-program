#include <stdio.h>

#define MAXLINE 1000

int getline_custom(char line[], int maxline);

int main(void)
{
    int len;               /* current line length */
    int max;               /* maximum length seen so far */
    char line[MAXLINE];    /* current input line */
    char longest[MAXLINE]; /* longest line saved */

    max = 0;
    while ((len = getline_custom(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            /* save as much as possible */
            int i;
            for (i = 0; i < MAXLINE && i < len; i++)
                longest[i] = line[i];
        }
    }

    if (max > 0) {
        printf("Longest line length = %d\n", max);
        printf("%s", longest);
    }

    return 0;
}

/* read a line into s, return length */
int getline_custom(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}
