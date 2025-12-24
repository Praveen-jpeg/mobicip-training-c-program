#include <stdio.h>

/* recursive helper for itoa */
void itoa_rec(int n, char s[], int *i)
{
    int digit;

    if (n / 10)
        itoa_rec(n / 10, s, i);

    digit = n % 10;
    if (digit < 0)
        digit = -digit;

    s[(*i)++] = digit + '0';
}

/* itoa: recursive version */
void itoa(int n, char s[])
{
    int i = 0;

    if (n < 0)
        s[i++] = '-';

    itoa_rec(n, s, &i);
    s[i] = '\0';
}

int main(void)
{
    int n;
    char s[50];

    printf("Enter an integer: ");
    scanf("%d", &n);

    itoa(n, s);
    printf("String: %s\n", s);

    return 0;
}
