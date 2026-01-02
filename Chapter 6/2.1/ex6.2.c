#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 100

int getword(char *, int);
int getch(void);
void ungetch(int);

char buf[BUFSIZE];
int bufp = 0;

struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
};

int n = 6;   /* number of leading characters */

/* addtree: add word to tree */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->left = p->right = NULL;
    } else if ((cond = strncmp(w, p->word, n)) < 0)
        p->left = addtree(p->left, w);
    else if (cond > 0)
        p->right = addtree(p->right, w);

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

int main(int argc, char *argv[])
{
    struct tnode *root = NULL;
    char word[MAXWORD];

    if (argc > 1)
        n = atoi(argv[1]);

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) || word[0] == '_')
            root = addtree(root, word);

    treeprint(root);
    return 0;
}
