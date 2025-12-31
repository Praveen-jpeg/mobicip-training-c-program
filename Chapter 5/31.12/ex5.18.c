#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int gettoken(void);
void dcl(void);
void dirdcl(void);
void skipline(void);

/* dcl: parse a declarator */
void dcl(void)
{
    int ns = 0;

    while (gettoken() == '*')
        ns++;

    dirdcl();

    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else {
        printf("error: expected name or (dcl)\n");
        skipline();      /* ERROR RECOVERY */
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

/* skip rest of input line on error */
void skipline(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* gettoken: return next token */
int gettoken(void)
{
    int c;
    char *p = token;

    while ((c = getchar()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetc(c, stdin);
            return tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; (*p++ = getchar()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getchar()); )
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

/* main */
int main(void)
{
    printf("Enter declarations (Ctrl+D / Ctrl+Z to stop):\n");

    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();

        if (tokentype != '\n')
            printf("syntax error\n");

        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}
