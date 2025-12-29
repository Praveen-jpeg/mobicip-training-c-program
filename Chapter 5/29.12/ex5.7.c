#include <stdio.h>

#define MAXLINES 100
#define MAXLEN   1000

/* getline: read a line into s */
int getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* readlines: store lines in array supplied by main */
int readlines(char lines[][MAXLEN], int maxlines)
{
    int nlines = 0;
    while (getline(lines[nlines], MAXLEN) > 0) {
        if (nlines >= maxlines)
            return -1;
        nlines++;
    }
    return nlines;
}

int main(void)
{
    char lines[MAXLINES][MAXLEN];
    int nlines, i;

    nlines = readlines(lines, MAXLINES);
    for (i = 0; i < nlines; i++)
        printf("%s", lines[i]);

    return 0;
}
