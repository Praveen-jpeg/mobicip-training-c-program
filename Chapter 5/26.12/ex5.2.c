#include <stdio.h>
#include <ctype.h>

#define SIZE 100
#define BUFSIZE 100

int getfloat(float *);
int getch(void);
void ungetch(int);

/* main: read floating-point numbers using getfloat */
int main(void)
{
    int n;
    float array[SIZE];

    printf("Enter floating-point numbers (Ctrl+D to end):\n");

    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;

    printf("\nFloating-point numbers read:\n");
    while (--n >= 0)
        printf("%g ", array[n]);
    printf("\n");

    return 0;
}

/* getfloat: get next floating-point number from input into *pn */
int getfloat(float *pn)
{
    int c, sign, next;
    float power;

    while (isspace(c = getch()))   /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);                /* not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            ungetch(c);
            return 0;
        }
        c = next;
    }

    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');

    if (c == '.') {
        c = getch();
        for (power = 1.0; isdigit(c); c = getch()) {
            *pn = 10.0 * *pn + (c - '0');
            power *= 10.0;
        }
        *pn /= power;
    }

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
