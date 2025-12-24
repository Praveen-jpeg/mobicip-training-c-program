#include <stdio.h>
#include <ctype.h>

double atof(char s[])
{
    double val = 0.0, power = 1.0;
    int i = 0, sign, exp, expsign;

    while (isspace(s[i]))
        i++;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    while (isdigit(s[i])) {
        val = 10.0 * val + (s[i] - '0');
        i++;
    }

    if (s[i] == '.')
        i++;

    while (isdigit(s[i])) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
        i++;
    }

    val = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        expsign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;

        for (exp = 0; isdigit(s[i]); i++)
            exp = 10 * exp + (s[i] - '0');

        while (exp-- > 0)
            val = (expsign == 1) ? val * 10 : val / 10;
    }
    return val;
}

int main(void)
{
    char s[100];

    printf("Enter number: ");
    scanf("%s", s);

    printf("Value = %g\n", atof(s));
    return 0;
}
