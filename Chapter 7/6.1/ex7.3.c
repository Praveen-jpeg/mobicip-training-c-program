#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

/*
 * minprintf: minimal printf with more features
 */
void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p;
    int ival, width, precision;
    double dval;
    char *sval;

    va_start(ap, fmt);

    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        width = precision = 0;

        /* field width */
        while (isdigit(*++p))
            width = 10 * width + (*p - '0');

        /* precision */
        if (*p == '.') {
            while (isdigit(*++p))
                precision = 10 * precision + (*p - '0');
        }

        switch (*p) {
        case 'd':
            ival = va_arg(ap, int);
            printf("%*d", width, ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%*.*f", width, precision, dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            printf("%*s", width, sval);
            break;
        case 'c':
            putchar(va_arg(ap, int));
            break;
        default:
            putchar(*p);
            break;
        }
    }

    va_end(ap);
}

/* test driver */
int main(void)
{
    minprintf("int: %5d\n", 42);
    minprintf("float: %8.2f\n", 3.14159);
    minprintf("string: %10s\n", "hello");
    minprintf("char: %c\n", 'A');
    return 0;
}
