#include <stdio.h>
#include <stdlib.h>   /* atof */
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP   100
#define NUMBER  '0'
#define NAME    'n'
#define MAXVAL  100
#define BUFSIZE 100

/* function prototypes */
int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

/* stack */
int sp = 0;
double val[MAXVAL];

/* reverse Polish calculator */
int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    printf("Enter RPN expression (Ctrl+D to end):\n");

    while ((type = getop(s)) != EOF) {
        switch (type) {

        case NUMBER:
            push(atof(s));
            break;

        case NAME:          /* library functions */
            if (strcmp(s, "sin") == 0)
                push(sin(pop()));
            else if (strcmp(s, "exp") == 0)
                push(exp(pop()));
            else if (strcmp(s, "pow") == 0) {
                op2 = pop();
                push(pow(pop(), op2));
            } else
                printf("error: unknown function %s\n", s);
            break;

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

        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push((int)pop() % (int)op2);
            else
                printf("error: zero divisor\n");
            break;

        case '\n':
            printf("\t%.8g\n", pop());
            break;

        default:
            printf("error: unknown command %s\n", s);
            break;
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

/* pop: pop and return top value */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: get next operator, number, or name */
int getop(char s[])
{
    int i, c, next;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (islower(c)) {        /* function name */
        i = 0;
        while (islower(s[i++] = c))
            c = getch();
        s[i-1] = '\0';
        if (c != EOF)
            ungetch(c);
        return NAME;
    }

    if (c == '-') {          /* minus or negative number */
        next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            return '-';
        }
        s[0] = '-';
        c = next;
        i = 1;
    } else {
        s[0] = c;
        i = 0;
    }

    if (!isdigit(c) && c != '.')
        return c;

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

/* input buffer */
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch: too many characters\n");
}
