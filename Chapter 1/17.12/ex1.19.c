#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getline_custom(char line[], int maxline);
void reverse(char s[]);

int main(void)
{
    char line[MAXLINE];
    int len;

    while ((len = getline_custom(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s\n", line);
    }

    return 0;
}

/* read a line into s, return length */
int getline_custom(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    s[i] = '\0';
    return i;
}

/* reverse string s in place */
void reverse(char s[])
{
    int i, j;
    char temp;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}
