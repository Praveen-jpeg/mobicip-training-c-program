#include <stdio.h>

int buf = EOF;

int getch(void)
{
    int c = (buf != EOF) ? buf : getchar();
    buf = EOF;
    return c;
}

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
