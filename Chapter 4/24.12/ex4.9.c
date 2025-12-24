#include <stdio.h>

/* Buffer that can also store EOF */
int buf = EOF;

/* getch: handles pushed-back EOF correctly */
int getch(void)
{
    if (buf != EOF) {
        int c = buf;
        buf = EOF;
        return c;
    }
    return getchar();
}

/* ungetch: push back character or EOF */
void ungetch(int c)
{
    buf = c;
}

int main(void)
{
    ungetch(EOF);
    printf("EOF handled safely\n");
    return 0;
}
