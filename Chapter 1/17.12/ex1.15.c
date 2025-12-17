#include <stdio.h>

float f_to_c(float fahr);   /* convert Fahrenheit to Celsius */

int main(void)
{
    float fahr;
    float lower = 0, upper = 300, step = 20;   /* range and step */

    printf("fahrenheit celsius\n");
    for (fahr = lower; fahr <= upper; fahr += step)
        printf("%3.0f %12.1f\n", fahr, f_to_c(fahr));

    return 0;
}

float f_to_c(float fahr)
{
    return (5.0 / 9.0) * (fahr - 32.0);   /* conversion formula */
}
