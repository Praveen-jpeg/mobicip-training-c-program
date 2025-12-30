/* ex5_15.c — Exercise 5-15 (case folding with -f) */

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
void swap(void *v[], int, int);

int fold = 0;

/* ---------------- main ---------------- */

int main(int argc, char *argv[])
{
    int nlines;

    if (argc > 1 && strcmp(argv[1], "-f") == 0)
        fold = 1;

    if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
        printf("error: input too big\n");
        return 1;
    }

    qsort2((void **)lineptr, 0, nlines - 1,
           (int (*)(void *, void *))strcmp);

    writelines(lineptr, nlines);
    return 0;
}

/* ---------------- sorting ---------------- */

void qsort2(void *v[], int left, int right,
            int (*comp)(void *, void *))
{
    int i, last;

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if (foldcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    qsort2(v, left, last - 1, comp);
    qsort2(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* ---------------- comparison ---------------- */

int foldcmp(char *s, char *t)
{
    for (; tolower(*s) == tolower(*t); s++, t++)
        if (*s == '\0')
            return 0;

    return tolower(*s) - tolower(*t);
}

/* ---------------- input/output ---------------- */

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
