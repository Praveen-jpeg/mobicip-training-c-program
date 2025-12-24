#include <stdio.h>

/* Single-character pushback buffer */
int buf = EOF;

/* getch: returns buffered character or reads new one */
int getch(void)
{
    int c = (buf != EOF) ? buf : getchar();
    buf = EOF;
    return c;
}

/* ungetch: allows only one character */
void ungetch(int c)
{
    buf = c;
}

int main(void)
{
    int c = getchar();
    ungetch(c);
    printf("Read again: %c\n", getch());
    return 0;
}
