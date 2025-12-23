#include <stdio.h>
#include <string.h>

int strindex(char s[], char t[])
{
    int i, j, k, pos = -1;
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
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
    s[strcspn(s, "\n")] = '\0';
    t[strcspn(t, "\n")] = '\0';
    printf("Rightmost index: %d\n", strindex(s, t));
    return 0;
}
