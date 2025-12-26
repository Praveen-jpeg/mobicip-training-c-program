#include <stdio.h>

int strend(char *s, char *t);

/* main: test strend */
int main(void)
{
    char s[100], t[100];

    printf("Enter main string: ");
    fgets(s, 100, stdin);

    printf("Enter test string: ");
    fgets(t, 100, stdin);

    if (strend(s, t))
        printf("\nThe string t occurs at the end of s.\n");
    else
        printf("\nThe string t does NOT occur at the end of s.\n");

    return 0;
}

/* strend: return 1 if t occurs at end of s */
int strend(char *s, char *t)
{
    char *bs = s;
    char *bt = t;

    while (*s)
        s++;
    while (*t)
        t++;

    while (t > bt && s > bs)
        if (*--t != *--s)
            return 0;

    return (t == bt);
}
