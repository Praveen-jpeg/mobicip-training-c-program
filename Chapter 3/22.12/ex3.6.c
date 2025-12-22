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

/* itoa: convert n to string with minimum width */
void itoa(int n, char s[], int width)
{
    int i, sign, digit;

    sign = n;
    i = 0;

    do {
        digit = n % 10;
        if (digit < 0)
            digit = -digit;
        s[i++] = digit + '0';
    } while ((n /= 10) != 0);

    if (sign < 0)
        s[i++] = '-';

    while (i < width)
        s[i++] = ' ';

    s[i] = '\0';
    reverse(s);
}

int main(void)
{
    int n, width;
    char s[50];

    printf("Enter number: ");
    scanf("%d", &n);

    printf("Enter minimum width: ");
    scanf("%d", &width);

    itoa(n, s, width);
    printf("Result: '%s'\n", s);

    return 0;
}
