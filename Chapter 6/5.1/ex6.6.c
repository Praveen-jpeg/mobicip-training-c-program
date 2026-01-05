#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

/* hash function */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 *hashval;
    return hashval % HASHSIZE;
}

/* lookup */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

/* install */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned h;

    if ((np = lookup(name)) == NULL) {
        np = malloc(sizeof(*np));
        np->name = strdup(name);
        h = hash(name);
        np->next = hashtab[h];
        hashtab[h] = np;
    } else
        free(np->defn);

    np->defn = strdup(defn);
    return np;
}

/* getword: return word or single character */
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    c = getchar();
    if (c == EOF)
        return EOF;

    if (!isalpha(c) && c != '_') {
        *w = c;
        *(w + 1) = '\0';
        return c;
    }

    *w++ = c;
    while (--lim > 0 && (isalnum(c = getchar()) || c == '_'))
        *w++ = c;

    *w = '\0';
    if (c != EOF)
        ungetc(c, stdin);

    return word[0];
}

/* main: formatted macro processor */
int main(void)
{
    char word[MAXWORD];
    char name[MAXWORD], defn[MAXWORD];
    struct nlist *np;

    while (getword(word, MAXWORD) != EOF) {

        /* handle #define */
        if (strcmp(word, "#") == 0) {
            getword(word, MAXWORD);        /* define */
            if (strcmp(word, "define") == 0) {
                getword(name, MAXWORD);
                getword(defn, MAXWORD);
                install(name, defn);
            }
        }
        /* identifier */
        else if (isalpha(word[0]) || word[0] == '_') {
            if ((np = lookup(word)) != NULL)
                printf("%s", np->defn);
            else
                printf("%s", word);
        }
        /* any other character */
        else {
            printf("%s", word);
        }
    }
    return 0;
}
