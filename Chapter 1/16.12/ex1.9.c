#include <stdio.h>

int main()
{
    int c;
    int prev_blank = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            if (!prev_blank)
            {
                putchar(c);
                prev_blank = 1;
            }
        }
        else
        {
            putchar(c);
            prev_blank = 0;
        }
    }

    return 0;
}
