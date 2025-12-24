#include <stdio.h>

/*
 getline:
  - Reads an entire line into array s
  - Returns length of the line
*/
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

    /* Extract numbers from input line */
    sscanf(line, "%lf %lf", &x, &y);

    printf("Sum = %g\n", x + y);
    return 0;
}
