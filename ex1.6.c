#include <stdio.h>

int main()
{
    int c;

    while ((c = getchar()) != EOF)
    {
        printf("getchar() != EOF evaluates to: %d\n", c != EOF);
    }

    return 0;
}
