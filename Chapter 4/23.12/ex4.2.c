#include <stdio.h>
#include <ctype.h>

/*
 atof:
  - Converts a string into a double value
  - Handles decimal numbers
  - Handles scientific notation (e / E)
*/
double atof(char s[])
{
    double val = 0.0;     /* accumulated value */
    double power = 1.0;   /* decimal divisor */
    int i = 0;
    int sign, exp, expsign;

    /* Skip leading whitespace */
    while (isspace(s[i]))
        i++;

    /* Handle optional sign */
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    /* Integer part */
    while (isdigit(s[i])) {
        val = 10.0 * val + (s[i] - '0');
        i++;
    }

    /* Fractional part */
    if (s[i] == '.')
        i++;

    while (isdigit(s[i])) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
        i++;
    }

    val = sign * val / power;

    /* Scientific notation */
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
