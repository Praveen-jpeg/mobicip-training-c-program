#include <stdio.h>

#define MAXVAL 100
double val[MAXVAL];
int sp = 0;

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    return 0.0;
}

void peek(void)
{
    if (sp > 0)
        printf("Top element: %.2f\n", val[sp - 1]);
}

void dup(void)
{
    if (sp > 0 && sp < MAXVAL)
        val[sp++] = val[sp - 1];
}

void swap(void)
{
    if (sp > 1) {
        double t = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = t;
    }
}

void clear(void)
{
    sp = 0;
}

int main(void)
{
    push(10);
    push(20);
    swap();
    peek();
    clear();
    return 0;
}
