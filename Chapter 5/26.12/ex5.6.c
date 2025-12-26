#include <stdio.h>

#define MAXLINE 1000

int getlinep(char *line, int max);

/* main: test getlinep */
int main(void)
{
    char line[MAXLINE];
    int len;

    printf("Enter a line of text:\n");

    len = getlinep(line, MAXLINE);

    printf("\nLine length: %d\n", len);
    printf("Line read:\n%s", line);

    return 0;
}

/* getlinep: read a line into s, return length */
int getlinep(char *s, int lim)
{
    int c;
    char *start = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;

    if (c == '\n')
        *s++ = c;

    *s = '\0';
    return s - start;
}
