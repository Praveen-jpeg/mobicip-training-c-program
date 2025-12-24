#include <stdio.h>

/*
 Exercise 4-6:
  - Provides 26 variables (A-Z)
  - Stores the most recently assigned value
*/
int main(void)
{
    double vars[26] = {0};  /* variables A-Z */
    double last = 0;        /* last stored value */
    char name;
    double value;

    printf("Enter variable (A-Z) and value: ");
    scanf(" %c %lf", &name, &value);

    vars[name - 'A'] = value;
    last = value;

    printf("%c = %.2f\n", name, vars[name - 'A']);
    printf("Last value = %.2f\n", last);
    return 0;
}
