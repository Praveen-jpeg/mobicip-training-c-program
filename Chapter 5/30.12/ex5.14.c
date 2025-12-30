/* ex5_14.c — Exercise 5-14 (reverse sort) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN   1000

char *lineptr[MAXLINES];

int getline2(char *, int);
int readlines(char *lineptr[], int);
void writelines(char *lineptr[], int);
void qsort2(void *lineptr[], int, int, int (*)(void *, void *));
int numcmp(char *, char *);

int numeric = 0;
int reverse = 0;

int main(int argc, char *argv[])
{
    int nlines;
    int (*cmp)(void *, void *);

    while (--argc > 0 && (*++argv)[0] == '-') {
        if (strcmp(argv[0], "-n") == 0)
            numeric = 1;
        else if (strcmp(argv[0], "-r") == 0)
            reverse = 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
        printf("error: input too big\n");
        return 1;
    }

    cmp = numeric
        ? (int (*)(void *, void *))numcmp
        : (int (*)(void *, void *))strcmp;

    qsort2((void **)lineptr, 0, nlines - 1, cmp);
    writelines(lineptr, nlines);
    return 0;
}

/* ---------------- sorting ---------------- */

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
        if ((reverse ? -comp(v[i], v[left])
                     :  comp(v[i], v[left])) < 0)
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

/* ---------------- comparisons ---------------- */

int numcmp(char *s1, char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
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
