#include <stdio.h>

#define BUFSIZE 100

/* Buffer for ungetch */
char buf[BUFSIZE];
int bufp = 0;

/* getch: get a character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push one character back */
void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
}

/*
 ungets:
  - Pushes an entire string back onto input
  - Characters are pushed in reverse order
*/
void ungets(char s[])
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
        ;
    while (i > 0)
        ungetch(s[--i]);
}

int main(void)
{
    char s[50];
    int c;

    printf("Enter string: ");
    scanf("%s", s);

    ungets(s);

    printf("Reading back: ");
    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}
