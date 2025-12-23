#include <stdio.h>

#define MAXVAL 100
double val[MAXVAL];
int sp = 0;

void push(double f) { if (sp < MAXVAL) val[sp++] = f; }
double pop(void) { return (sp > 0) ? val[--sp] : 0.0; }
void peek(void) { if (sp > 0) printf("Top: %.2f\n", val[sp-1]); }
void dup(void) { if (sp > 0) push(val[sp-1]); }
void swap(void)
{
    if (sp > 1) {
        double t = val[sp-1];
        val[sp-1] = val[sp-2];
        val[sp-2] = t;
    }
}
void clear(void) { sp = 0; }

int main(void)
{
    int ch;
    double x;
    do {
        printf("1.Push 2.Pop 3.Peek 4.Dup 5.Swap 6.Clear 0.Exit\n");
        scanf("%d", &ch);
        switch (ch) {
        case 1: scanf("%lf", &x); push(x); break;
        case 2: printf("Popped %.2f\n", pop()); break;
        case 3: peek(); break;
        case 4: dup(); break;
        case 5: swap(); break;
        case 6: clear(); break;
        }
    } while (ch != 0);
    return 0;
}
