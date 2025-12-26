#include <stdio.h>

void mystrncpy(char *s, char *t, int n);
void mystrncat(char *s, char *t, int n);
int mystrncmp(char *s, char *t, int n);

/* main: test string functions */
int main(void)
{
    char s[100], t[100];
    int n;

    printf("Enter first string: ");
    fgets(s, 100, stdin);

    printf("Enter second string: ");
    fgets(t, 100, stdin);

    printf("Enter n: ");
    scanf("%d", &n);

    mystrncpy(s, t, n);
    printf("\nAfter strncpy:\n%s\n", s);

    mystrncat(s, t, n);
    printf("After strncat:\n%s\n", s);

    printf("Result of strncmp: %d\n", mystrncmp(s, t, n));

    return 0;
}

/* mystrncpy: copy at most n characters */
void mystrncpy(char *s, char *t, int n)
{
    while (n-- > 0 && (*s++ = *t++))
        ;
    while (n-- > 0)
        *s++ = '\0';
}

/* mystrncat: concatenate at most n characters */
void mystrncat(char *s, char *t, int n)
{
    while (*s)
        s++;

    while (n-- > 0 && (*s++ = *t++))
        ;
    *s = '\0';
}

/* mystrncmp: compare at most n characters */
int mystrncmp(char *s, char *t, int n)
{
    for (; n > 0; s++, t++, n--)
        if (*s != *t || *s == '\0')
            return *s - *t;

    return 0;
}
