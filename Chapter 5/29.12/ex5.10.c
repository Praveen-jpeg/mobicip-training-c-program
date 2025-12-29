#include <stdio.h>
#include <stdlib.h>

#define MAXVAL 100

double stack[MAXVAL];
int sp = 0;

void push(double f) { stack[sp++] = f; }
double pop(void) { return stack[--sp]; }

int main(int argc, char *argv[])
{
    double op2;

    while (--argc > 0) {
        argv++;
        switch ((*argv)[0]) {
        case '+': push(pop() + pop()); break;
        case '*': push(pop() * pop()); break;
        case '-': op2 = pop(); push(pop() - op2); break;
        case '/': op2 = pop(); push(pop() / op2); break;
        default:  push(atof(*argv)); break;
        }
    }
    printf("Result: %.8g\n", pop());
    return 0;
}
