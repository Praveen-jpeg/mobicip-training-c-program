#include <stdio.h>
#include <string.h>

/* reverse: reverse string */
void reverse(char s[])
{
    int i, j;
    char temp;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

/* itob: convert integer n to base b */
void itob(int n, char s[], int b)
{
    int i, sign, digit;

    sign = n;
    i = 0;

    do {
        digit = n % b;
        if (digit < 0)
            digit = -digit;
        s[i++] = (digit < 10) ? digit + '0' : digit - 10 + 'A';
    } while ((n /= b) != 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

int main(void)
{
    int n, b;
    char s[50];

    printf("Enter number: ");
    scanf("%d", &n);

    printf("Enter base (2–16): ");
    scanf("%d", &b);

    itob(n, s, b);
    printf("Result: %s\n", s);

    return 0;
}
