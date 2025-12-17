#include <stdio.h>
#define IN  1
#define OUT 0

int main(){
    int c;
    int state = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                putchar('\n');   /* end of a word */
                state = OUT;
            }
        } else {
            state = IN;          /* inside a word */
            putchar(c);
        }
    }
    return 0;
}
