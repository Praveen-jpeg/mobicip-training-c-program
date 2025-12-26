#include <stdio.h>
#include <ctype.h>

#define SIZE 100
#define BUFSIZE 100

int getint(int *);
int getch(void);
void ungetch(int);

/* main: read integers using getint */
int main(void)
{
    int n, array[SIZE];

    printf("Enter integers (Ctrl+D to end):\n");

    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;

    printf("\nIntegers read:\n");
    while (--n >= 0)
        printf("%d ", array[n]);
    printf("\n");

    return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign, next;

    while (isspace(c = getch()))   /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);                /* not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        next = getch();
        if (!isdigit(next)) {      /* not a valid number */
            ungetch(next);
            ungetch(c);
            return 0;
        }
        c = next;
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

/* getch and ungetch */

int buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
