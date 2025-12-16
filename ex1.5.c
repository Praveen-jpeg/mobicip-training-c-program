#include <stdio.h>
void main()
{
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;
    upper = 300;
    step = 20;
    
    printf("fahrenheit celsius\n");
    for(fahr = upper; fahr >=lower; fahr-= step){
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f %12.1f\n", fahr, celsius);
    }
}