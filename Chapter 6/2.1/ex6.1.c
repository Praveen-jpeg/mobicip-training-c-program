#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 100

int getword(char *word, int lim);
int getch(void);
void ungetch(int);

/* buffer for ungetch */
char buf[BUFSIZE];
int bufp = 0;

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    /* skip whitespace */
    while (isspace(c = getch()))
        ;

    if (c == EOF)
        return EOF;

    *w++ = c;

    /* preprocessor line */
    if (c == '#') {
        while ((c = getch()) != '\n' && c != EOF)
            ;
        word[0] = '#';
        word[1] = '\0';
        return '#';
    }

    /* string constant */
    if (c == '"') {
        while (--lim > 0 && (c = getch()) != '"' && c != EOF)
            *w++ = c;
        *w++ = '"';
        *w = '\0';
        return '"';
    }

    /* character constant */
    if (c == '\'') {
        while (--lim > 0 && (c = getch()) != '\'' && c != EOF)
            *w++ = c;
        *w++ = '\'';
        *w = '\0';
        return '\'';
    }

    /* comments */
    if (c == '/') {
        d = getch();
        if (d == '/') {                 /* single-line comment */
            while ((c = getch()) != '\n' && c != EOF)
                ;
            return getword(word, lim);
        } else if (d == '*') {          /* multi-line comment */
            while ((c = getch()) != EOF) {
                if (c == '*' && (c = getch()) == '/')
                    break;
            }
            return getword(word, lim);
        } else {
            ungetch(d);
        }
    }

    /* identifier: letters, digits, underscore */
    if (isalpha(c) || c == '_') {
        while (--lim > 0) {
            c = getch();
            if (!isalnum(c) && c != '_') {
                ungetch(c);
                break;
            }
            *w++ = c;
        }
    }

    *w = '\0';
    return word[0];
}

/* getch: get a character (possibly pushed back) */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
}

/* main: test getword */
int main(void)
{
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        printf("%s\n", word);

    return 0;
}
