/* minscanf: minimal scanf, K&R style */

#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p;
    int *ip;
    double *dp;
    char *sp;
    char *cp;
    int c;

    va_start(ap, fmt);

    for (p = fmt; *p; p++) {
        if (*p != '%') {
            /* match literal character */
            if ((c = getchar()) != *p)
                break;
            continue;
        }

        switch (*++p) {
        case 'd':       /* integer */
            ip = va_arg(ap, int *);
            scanf("%d", ip);
            break;

        case 'f':       /* floating point */
            dp = va_arg(ap, double *);
            scanf("%lf", dp);
            break;

        case 's':       /* string */
            sp = va_arg(ap, char *);
            scanf("%s", sp);
            break;

        case 'c':       /* character */
            cp = va_arg(ap, char *);
            *cp = getchar();
            break;

        default:
            /* ignore unknown specifier */
            break;
        }
    }

    va_end(ap);
}
int main(void)
{
    int i;
    double x;
    char s[100];
    char c;

    printf("Enter: int double string char\n");

    minscanf("%d %f %s %c", &i, &x, s, &c);

    printf("You entered:\n");
    printf("i = %d\n", i);
    printf("x = %g\n", x);
    printf("s = %s\n", s);
    printf("c = %c\n", c);

    return 0;
}