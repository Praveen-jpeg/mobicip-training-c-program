/* tail.c — Exercise 5-13
 * Print the last n lines of input (default 10)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int getline2(char *, int);

int main(int argc, char *argv[])
{
    int n = 10;
    int i, count = 0;
    char line[MAXLINE];
    char **lines;

    /* optional -n argument */
    if (argc == 2 && argv[1][0] == '-')
        n = atoi(argv[1] + 1);

    if (n <= 0)
        return 0;

    lines = malloc(n * sizeof(char *));
    if (lines == NULL)
        return 1;

    for (i = 0; i < n; i++)
        lines[i] = NULL;

    while (getline2(line, MAXLINE) > 0) {
        char *p = malloc(strlen(line) + 1);
        if (p == NULL)
            break;

        strcpy(p, line);

        if (lines[count % n])
            free(lines[count % n]);

        lines[count % n] = p;
        count++;
    }

    int start = (count > n) ? count - n : 0;
    for (i = start; i < count; i++)
        printf("%s", lines[i % n]);

    return 0;
}

int getline2(char *s, int lim)
{
    int c;
    char *t = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - t;
}
