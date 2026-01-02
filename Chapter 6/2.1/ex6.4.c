#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXWORDS 1000

struct word {
    char *word;
    int count;
};

struct word words[MAXWORDS];
int nwords = 0;

int findword(char *w)
{
    int i;
    for (i = 0; i < nwords; i++)
        if (strcmp(words[i].word, w) == 0)
            return i;
    return -1;
}

int cmp(const void *a, const void *b)
{
    return ((struct word *)b)->count - ((struct word *)a)->count;
}

int getword(char *w, int lim)
{
    int c;
    char *p = w;

    while ((c = getchar()) != EOF && !isalpha(c))
        ;
    if (c == EOF)
        return EOF;

    *p++ = c;
    while (--lim > 0 && isalnum(c = getchar()))
        *p++ = c;
    *p = '\0';
    return w[0];
}

int main(void)
{
    char word[MAXWORD];
    int i;

    while (getword(word, MAXWORD) != EOF) {
        i = findword(word);
        if (i >= 0)
            words[i].count++;
        else {
            words[nwords].word = strdup(word);
            words[nwords].count = 1;
            nwords++;
        }
    }

    qsort(words, nwords, sizeof(struct word), cmp);

    for (i = 0; i < nwords; i++)
        printf("%4d %s\n", words[i].count, words[i].word);

    return 0;
}
