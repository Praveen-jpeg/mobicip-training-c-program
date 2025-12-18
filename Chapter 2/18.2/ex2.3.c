#include <stdio.h>

/* htoi: convert hexadecimal string s to integer */
int htoi(char s[]) {
    int i = 0;
    int n = 0;
    int digit;

    /* Skip optional "0x" or "0X" prefix */
    if (s[i] == '0') {
        i++;
        if (s[i] == 'x' || s[i] == 'X') {
            i++;
        }
    }

    /* Convert hex digits until a non-hex character is reached */
    for (; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            digit = s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            digit = s[i] - 'a' + 10;
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            digit = s[i] - 'A' + 10;
        } else {
            /* Stop if an invalid hexadecimal character is found */
            break;
        }
        n = 16 * n + digit;
    }

    return n;
}

int main() {
    char* s;
    printf("Enter the string:");
    scanf("%s",s);
    printf("%s: %d\n",s,htoi(s)); //hexadecimal string to integer
    return 0;
}
