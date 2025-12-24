#include <stdio.h>

#define MAXVAL 100

/* Stack array and stack pointer */
double val[MAXVAL];
int sp = 0;

/* push: push value onto stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
}

/* pop: remove and return top value */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    return 0.0;
}

/* peek: print top element without popping */
void peek(void)
{
    if (sp > 0)
        printf("Top element: %.2f\n", val[sp - 1]);
}

/* dup: duplicate top stack element */
void dup(void)
{
    if (sp > 0 && sp < MAXVAL)
        val[sp++] = val[sp - 1];
}

/* swap: swap top two elements */
void swap(void)
{
    if (sp > 1) {
        double t = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = t;
    }
}

/* clear: clear entire stack */
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
