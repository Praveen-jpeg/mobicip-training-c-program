#include <stdio.h>

/* swap: interchange x and y of type t */
#define swap(t, x, y)           \
    do {                        \
        t temp = (x);           \
        (x) = (y);              \
        (y) = temp;             \
    } while (0)

int main(void)
{
    int a = 10, b = 20;
    double x = 1.5, y = 2.5;

    swap(int, a, b);
    swap(double, x, y);

    printf("a = %d, b = %d\n", a, b);
    printf("x = %.1f, y = %.1f\n", x, y);

    return 0;
}
