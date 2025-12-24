#include <stdio.h>

int main(void)
{
    double vars[26] = {0};
    double last = 0;
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
