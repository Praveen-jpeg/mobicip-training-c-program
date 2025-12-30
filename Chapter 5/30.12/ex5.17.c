/* fieldsort.c — Exercise 5-17 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int field = 1;
int numeric = 0;
int fold = 0;
int directory = 0;
int reverse = 0;

char *getfield(char *, int);
int fieldcmp(void *, void *);

int getline2(char *, int);
int readlines(char *[], int);
void writelines(char *[], int);
void qsort2(void *[], int, int, int (*)(void *, void *));

int main(int argc, char *argv[])
{
    int nlines;

    while (--argc > 0 && (*++argv)[0] == '-') {
        if ((*argv)[1] == 'k')
            field = atoi(*argv + 2);
        else {
            char *p = argv[0] + 1;
            while (*p) {
                switch (*p++) {
                case 'n': numeric = 1; break;
                case 'f': fold = 1; break;
                case 'd': directory = 1; break;
                case 'r': reverse = 1; break;
                }
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) < 0)
        return 1;

    qsort2((void **)lineptr, 0, nlines - 1, fieldcmp);
    writelines(lineptr, nlines);
    return 0;
}

int fieldcmp(void *a, void *b)
{
    char *s = getfield((char *)a, field);
    char *t = getfield((char *)b, field);

    int result;

    if (numeric)
        result = atof(s) - atof(t);
    else
        result = strcmp(s, t);

    return reverse ? -result : result;
}

char *getfield(char *s, int k)
{
    while (--k > 0 && *s) {
        while (*s && *s != ' ')
            s++;
        while (*s == ' ')
            s++;
    }
    return s;
}

void qsort2(void *v[], int left, int right,
            int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *[], int, int);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    qsort2(v, left, last - 1, comp);
    qsort2(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
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

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char line[MAXLEN];
    char *p;

    while ((len = getline2(line, MAXLEN)) > 0) {
        if (nlines >= maxlines)
            return -1;
        p = malloc(len + 1);
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s", lineptr[i]);
}
