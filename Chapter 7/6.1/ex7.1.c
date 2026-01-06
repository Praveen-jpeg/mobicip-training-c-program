#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
 * Convert case depending on how the program is invoked.
 * If argv[0] contains "upper", convert to upper case.
 * If argv[0] contains "lower", convert to lower case.
 */
int main(int argc, char *argv[])
{
    int c;
    int to_upper = 0, to_lower = 0;

    if (strstr(argv[0], "upper") != NULL)
        to_upper = 1;
    else if (strstr(argv[0], "lower") != NULL)
        to_lower = 1;

    while ((c = getchar()) != EOF) {
        if (to_upper)
            putchar(toupper(c));
        else if (to_lower)
            putchar(tolower(c));
        else
            putchar(c);
    }
    return 0;
}
