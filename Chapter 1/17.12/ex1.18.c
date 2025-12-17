#include <stdio.h>

#define MAXLINE 1000

int getline_custom(char line[], int maxline);
void trim_trailing(char line[]);

int main(void)
{
    char line[MAXLINE];
    int len;

    while ((len = getline_custom(line, MAXLINE)) > 0) {
        trim_trailing(line);
        if (line[0] != '\0')  /* skip empty lines */
            printf("%s\n", line);
    }

    return 0;
}

/* read a line into s, return length without '\n' */
int getline_custom(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    s[i] = '\0';
    return i;
}

/* remove trailing spaces and tabs */
void trim_trailing(char s[])
{
    int i = 0;
    while (s[i] != '\0') i++;  /* find end */
    i--;
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t'))
        s[i--] = '\0';
}
