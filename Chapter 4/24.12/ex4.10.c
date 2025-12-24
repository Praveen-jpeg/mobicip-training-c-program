#include <stdio.h>

int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 &&
         (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    s[i] = '\0';
    return i;
}

int main(void)
{
    char line[100];
    double x, y;

    printf("Enter two numbers: ");
    getline(line, 100);

    sscanf(line, "%lf %lf", &x, &y);
    printf("Sum = %g\n", x + y);

    return 0;
}
