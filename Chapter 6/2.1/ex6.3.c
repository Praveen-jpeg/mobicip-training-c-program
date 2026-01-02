#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

struct lnode {
    int line;
    struct lnode *next;
};

struct tnode {
    char *word;
    struct lnode *lines;
    struct tnode *left;
    struct tnode *right;
};

int lineno = 1;

char *noise[] = { "the", "and", "is", "of", "to", NULL };

int isnoise(char *w)
{
    int i;
    for (i = 0; noise[i]; i++)
        if (strcmp(w, noise[i]) == 0)
            return 1;
    return 0;
}

struct lnode *addline(struct lnode *p)
{
    struct lnode *n = malloc(sizeof(struct lnode));
    n->line = lineno;
    n->next = p;
    return n;
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->lines = addline(NULL);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->lines = addline(p->lines);
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

void treeprint(struct tnode *p)
{
    struct lnode *l;

    if (p != NULL) {
        treeprint(p->left);
        printf("%s:", p->word);
        for (l = p->lines; l; l = l->next)
            printf(" %d", l->line);
        printf("\n");
        treeprint(p->right);
    }
}

/* simplified getword */
int getword(char *w, int lim)
{
    int c;
    char *p = w;

    while ((c = getchar()) != EOF) {
        if (c == '\n')
            lineno++;
        if (isalpha(c))
            break;
    }

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
    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (!isnoise(word))
            root = addtree(root, word);

    treeprint(root);
    return 0;
}
