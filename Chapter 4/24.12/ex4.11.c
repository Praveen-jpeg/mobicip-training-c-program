#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'

/* getop: get next operator or numeric operand without ungetch */
int getop(char s[])
{
    static int lastc = 0;
    int c, i = 0, next;

    if (lastc != 0) {
        c = lastc;
        lastc = 0;
    } else
        c = getchar();

    while (c == ' ' || c == '\t')
        c = getchar();

    if (c == '-') {
        next = getchar();
        if (!isdigit(next) && next != '.') {
            lastc = next;
            return '-';
        }
        s[i++] = '-';
        c = next;
    }

    if (!isdigit(c) && c != '.')
        return c;

    while (isdigit(c)) {
        s[i++] = c;
        c = getchar();
    }

    if (c == '.') {
        s[i++] = c;
        while (isdigit(c = getchar()))
            s[i++] = c;
    }

    s[i] = '\0';
    lastc = c;
    return NUMBER;
}

int main(void)
{
    char s[100];
    int type;

    printf("Enter input (Ctrl+D to end):\n");

    while ((type = getop(s)) != EOF) {
        if (type == NUMBER)
            printf("NUMBER: %s\n", s);
        else
            printf("CHAR: %c\n", type);
    }
    return 0;
}
