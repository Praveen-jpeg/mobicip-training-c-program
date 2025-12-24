#include <stdio.h>
#include <string.h>

/*
 strindex:
  - Finds the RIGHTMOST occurrence of string t in string s
  - Returns the starting index if found
  - Returns -1 if t is not found
*/
int strindex(char s[], char t[])
{
    int i, j, k;
    int pos = -1;   /* stores last matching position */

    /* Scan string s */
    for (i = 0; s[i] != '\0'; i++) {

        /* Try matching t starting at position i */
        for (j = i, k = 0;
             t[k] != '\0' && s[j] == t[k];
             j++, k++)
            ;

        /* If end of t reached, match found */
        if (t[k] == '\0')
            pos = i;
    }
    return pos;
}

int main(void)
{
    char s[200], t[50];

    printf("Enter string s: ");
    fgets(s, sizeof(s), stdin);

    printf("Enter string t: ");
    fgets(t, sizeof(t), stdin);

    /* Remove newline characters */
    s[strcspn(s, "\n")] = '\0';
    t[strcspn(t, "\n")] = '\0';

    printf("Rightmost index: %d\n", strindex(s, t));
    return 0;
}
