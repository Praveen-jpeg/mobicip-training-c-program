/* postfix calculator using scanf/sscanf */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP   100
#define MAXVAL  100

/* stack */
int sp = 0;
double val[MAXVAL];

void push(double f);
double pop(void);

int main(void)
{
    char op[MAXOP];
    double op2;

    while (scanf("%s", op) == 1) {
        if (sscanf(op, "%lf", &op2) == 1) {
            /* number */
            push(op2);
        } else {
            /* operator */
            switch (op[0]) {
            case '+':
                push(pop() + pop());
                break;

            case '*':
                push(pop() * pop());
                break;

            case '-':
                op2 = pop();
                push(pop() - op2);
                break;

            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;

            case '=':
                printf("\t%.8g\n", pop());
                break;

            default:
                printf("error: unknown command %s\n", op);
                break;
            }
        }
    }
    return 0;
}

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full\n");
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
