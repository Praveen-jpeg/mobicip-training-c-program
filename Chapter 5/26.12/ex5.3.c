#include <stdio.h>

void mystrcat(char *s, char *t);

/* main: test mystrcat */
int main(void)
{
    char s[100], t[100];

    printf("Enter first string: ");
    fgets(s, 100, stdin);

    printf("Enter second string: ");
    fgets(t, 100, stdin);

    mystrcat(s, t);

    printf("\nResulting string:\n%s", s);

    return 0;
}

/* mystrcat: copy t to end of s */
void mystrcat(char *s, char *t)
{
    while (*s)        /* find end of s */
        s++;

    while ((*s++ = *t++))  /* copy t */
        ;
}
