#include <stdio.h>

int main(void)
{
    char line[100];
    double x, y;
    printf("Enter two numbers: ");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%lf %lf", &x, &y);
    printf("Sum = %g\n", x + y);
    return 0;
}
