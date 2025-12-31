#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, QUALIFIER };

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int gettoken(void);
void dcl(void);
void dirdcl(void);

/* dcl: parse declaration */
void dcl(void)
{
    int ns = 0;

    while (tokentype == QUALIFIER) {
        strcat(out, " ");
        strcat(out, token);
        gettoken();
    }

    while (tokentype == '*') {
        ns++;
        gettoken();
    }

    dirdcl();

    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl */
void dirdcl(void)
{
    if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("error: expected name\n");
}

/* gettoken */
int gettoken(void)
{
    int c;
    char *p = token;

    while ((c = getchar()) == ' ' || c == '\t')
        ;

    if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getchar()); )
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);

        if (strcmp(token, "const") == 0)
            return tokentype = QUALIFIER;
        else
            return tokentype = NAME;
    }
    return tokentype = c;
}

/* main */
int main(void)
{
    printf("Enter declaration (supports const):\n");

    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        gettoken();
        dcl();
        printf("%s:%s %s\n", name, out, datatype);
    }
    return 0;
}
