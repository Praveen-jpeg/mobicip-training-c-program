#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <ctype.h>

#define MAXOP   100   /* max size of operand or operator */
#define NUMBER  '0'   /* signal that a number was found */
#define MAXVAL  100   /* maximum depth of val stack */
#define BUFSIZE 100

/* function declarations */
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

        case '%':      /* modulus operator */
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
        printf("error: stack full, can't push %g\n", f);
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

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c, next;

    /* skip whitespace */
    while ((c = getch()) == ' ' || c == '\t')
        ;

    /* check for minus sign */
    if (c == '-') {
        next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            return '-';   /* subtraction operator */
        }
        s[0] = '-';
        c = next;
        i = 1;
    } else {
        s[0] = c;
        i = 0;
    }

    if (!isdigit(c) && c != '.')
        return c;        /* not a number */

    /* collect integer part */
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    /* collect fraction part */
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

/* getch: get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
