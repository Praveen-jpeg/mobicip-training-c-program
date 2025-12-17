#include <stdio.h>

#define STACKSIZE 1000

int main() {
    int stack[STACKSIZE], top = 0;
    int c;
    char quote = 0;

    while ((c = getchar()) != EOF) {
        if (quote) {
            if (c == quote) quote = 0;
            else if (c == '\\') getchar(); // skip escaped char
        } else {
            if (c == '"' || c == '\'') quote = c;
            else if (c == '(' || c == '{' || c == '[') stack[top++] = c;
            else if (c == ')' || c == '}' || c == ']') {
                if (top == 0) {
                    printf("Unmatched %c\n", c);
                } else {
                    char open = stack[--top];
                    if ((open == '(' && c != ')') ||
                        (open == '{' && c != '}') ||
                        (open == '[' && c != ']')) {
                        printf("Mismatched %c and %c\n", open, c);
                    }
                }
            } else if (c == '/') {
                int next = getchar();
                if (next == '/') {
                    while ((c = getchar()) != EOF && c != '\n'); // skip line comment
                } else if (next == '*') {
                    int prev = 0;
                    while ((c = getchar()) != EOF) {
                        if (prev == '*' && c == '/') break;
                        prev = c;
                    }
                } else if (next != EOF) {
                    ungetc(next, stdin);
                }
            }
        }
    }

    while (top > 0) {
        printf("Unmatched %c\n", stack[--top]);
    }

    return 0;
}
