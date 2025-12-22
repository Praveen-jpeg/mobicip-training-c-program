#include <stdio.h>
#include <ctype.h>

/* expand: expand shorthand notations like a-z */
void expand(const char s1[], char s2[])
{
    int i, j;
    char c1, c2;

    j = 0;
    for (i = 0; s1[i] != '\0'; i++) {
        if (s1[i] == '-' && i > 0 && s1[i+1] != '\0') {
            c1 = s1[i-1];
            c2 = s1[i+1];

            if ((islower(c1) && islower(c2)) ||
                (isupper(c1) && isupper(c2)) ||
                (isdigit(c1) && isdigit(c2))) {

                if (c1 < c2) {
                    while (++c1 < c2)
                        s2[j++] = c1;
                    continue;
                }
            }
        }
        s2[j++] = s1[i];
    }
    s2[j] = '\0';
}

int main(void)
{
    char s1[100], s2[300];

    printf("Enter shorthand string: ");
    scanf("%99s", s1);

    expand(s1, s2);
    printf("Expanded: %s\n", s2);

    return 0;
}
