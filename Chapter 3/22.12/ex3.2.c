#include <stdio.h>

/* escape: convert special characters to visible escape sequences */
void escape(char s[], const char t[])
{
    int i, j;

    for (i = j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
        case '\n': s[j++] = '\\'; s[j++] = 'n'; break;
        case '\t': s[j++] = '\\'; s[j++] = 't'; break;
        default:   s[j++] = t[i]; break;
        }
    }
    s[j] = '\0';
}

/* unescape: convert escape sequences to real characters */
void unescape(char s[], const char t[])
{
    int i, j;

    for (i = j = 0; t[i] != '\0'; i++) {
        if (t[i] == '\\') {
            switch (t[++i]) {
            case 'n': s[j++] = '\n'; break;
            case 't': s[j++] = '\t'; break;
            default:  s[j++] = t[i];  break;
            }
        } else
            s[j++] = t[i];
    }
    s[j] = '\0';
}

int main(void)
{
    char t[200], s[400];

    printf("Enter text (use real tabs/newlines):\n");
    fgets(t, sizeof(t), stdin);

    escape(s, t);
    printf("Escaped   : %s\n", s);

    unescape(t, s);
    printf("Unescaped : %s\n", t);

    return 0;
}
