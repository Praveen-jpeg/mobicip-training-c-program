#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
#define MAXWORD  100

/* table entry */
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
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup name */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

/* install name and definition */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = malloc(sizeof(*np));
        if (np == NULL)
            return NULL;
        np->name = strdup(name);
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free(np->defn);
    }

    np->defn = strdup(defn);
    return np;
}

/* undef: remove name from table */
void undef(char *name)
{
    struct nlist *np, *prev = NULL;
    unsigned h = hash(name);

    for (np = hashtab[h]; np != NULL; prev = np, np = np->next) {
        if (strcmp(name, np->name) == 0) {
            if (prev == NULL)
                hashtab[h] = np->next;
            else
                prev->next = np->next;

            free(np->name);
            free(np->defn);
            free(np);
            printf("'%s' undefined\n", name);
            return;
        }
    }
    printf("'%s' not found\n", name);
}

/* main: user-driven test */
int main(void)
{
    char cmd[MAXWORD], name[MAXWORD], defn[MAXWORD];
    struct nlist *np;

    printf("Commands:\n");
    printf("  define <name> <definition>\n");
    printf("  undef <name>\n");
    printf("  print <name>\n");
    printf("  quit\n\n");

    while (1) {
        printf("> ");

        if (scanf("%s", cmd) != 1)
            break;

        if (strcmp(cmd, "define") == 0) {
            scanf("%s %s", name, defn);
            install(name, defn);
            printf("Defined %s = %s\n", name, defn);
        }
        else if (strcmp(cmd, "undef") == 0) {
            scanf("%s", name);
            undef(name);
        }
        else if (strcmp(cmd, "print") == 0) {
            scanf("%s", name);
            np = lookup(name);
            if (np)
                printf("%s = %s\n", name, np->defn);
            else
                printf("%s not found\n", name);
        }
        else if (strcmp(cmd, "quit") == 0) {
            break;
        }
        else {
            printf("Unknown command\n");
        }
    }

    return 0;
}
