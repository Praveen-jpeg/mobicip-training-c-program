#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 100

/* number of characters to compare */
int n = 6;

/* getword support */
int getword(char *, int);
int getch(void);
void ungetch(int);

/* input buffer */
char buf[BUFSIZE];
int bufp = 0;

/* binary tree node */
struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
};

/* addtree: add a word to the tree */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->left = p->right = NULL;
    }
    else if ((cond = strncmp(w, p->word, n)) < 0)
        p->left = addtree(p->left, w);
    else if (cond > 0)
        p->right = addtree(p->right, w);
    /* words identical in first n chars are grouped */
    return p;
}

/* treeprint: print words in order */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%s\n", p->word);
        treeprint(p->right);
    }
}

/* getword: get next word, skipping comments and strings */
int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    /* skip whitespace */
    while (isspace(c = getch()))
        ;

    if (c == EOF)
        return EOF;

    /* skip comments */
    if (c == '/') {
        if ((d = getch()) == '/') {      /* single-line comment */
            while ((c = getch()) != '\n' && c != EOF)
                ;
            return getword(word, lim);
        }
        else if (d == '*') {             /* multi-line comment */
            while ((c = getch()) != EOF) {
                if (c == '*' && (c = getch()) == '/')
                    break;
            }
            return getword(word, lim);
        }
        else
            ungetch(d);
    }

    /* skip string literals */
    if (c == '"') {
        while ((c = getch()) != '"' && c != EOF)
            ;
        return getword(word, lim);
    }

    /* identifier */
    if (isalpha(c) || c == '_') {
        *w++ = c;
        while (--lim > 0 && (isalnum(c = getch()) || c == '_'))
            *w++ = c;
        *w = '\0';
        ungetch(c);
        return word[0];
    }

    return getword(word, lim);
}

/* getch */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch */
void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
}

/* main */
int main(int argc, char *argv[])
{
    struct tnode *root = NULL;
    char word[MAXWORD];

    if (argc > 1)
        n = atoi(argv[1]);   /* set prefix length */

    while (getword(word, MAXWORD) != EOF)
        root = addtree(root, word);

    treeprint(root);
    return 0;
}
        