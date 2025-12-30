/* sort_5_16.c — Exercise 5-16 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN   1000

char *lineptr[MAXLINES];

int getline2(char *, int);
int readlines(char *lineptr[], int);
void writelines(char *lineptr[], int);
void qsort2(void *lineptr[], int, int, int (*)(void *, void *));

int dircmp(char *, char *);
int fold = 0;

int main(int argc, char *argv[])
{
    int nlines;

    while (--argc > 0 && (*++argv)[0] == '-') {
        if (strcmp(argv[0], "-f") == 0)
            fold = 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) < 0)
        return 1;

    qsort2((void **)lineptr, 0, nlines - 1,
           (int (*)(void *, void *))dircmp);
    writelines(lineptr, nlines);
    return 0;
}

int dircmp(char *s, char *t)
{
    char a, b;

    do {
        while (*s && !isalnum(*s) && *s != ' ')
            s++;
        while (*t && !isalnum(*t) && *t != ' ')
            t++;

        a = fold ? tolower(*s) : *s;
        b = fold ? tolower(*t) : *t;

        if (a != b)
            return a - b;

        if (*s) s++;
        if (*t) t++;
    } while (a && b);

    return 0;
}
void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort2(void *v[], int left, int right,
            int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if (comp(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    qsort2(v, left, last - 1, comp);
    qsort2(v, last + 1, right, comp);
}
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char line[MAXLEN];
    char *p;

    while ((len = getline2(line, MAXLEN)) > 0) {
        if (nlines >= maxlines)
            return -1;

        p = malloc(len + 1);
        if (p == NULL)
            return -1;

        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i++)
        printf("%s", lineptr[i]);
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
