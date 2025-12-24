#include <stdio.h>

int buf = EOF;

int getch(void)
{
    if (buf != EOF) {
        int c = buf;
        buf = EOF;
        return c;
    }
    return getchar();
}

void ungetch(int c) { buf = c; }

int main(void)
{
    ungetch(EOF);
    printf("EOF handled safely\n");
    return 0;
}
