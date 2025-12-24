#include <stdio.h>
#include <string.h>

/* recursive helper to reverse string */
void reverse_rec(char s[], int left, int right)
{
    char temp;

    if (left >= right)
        return;

    temp = s[left];
    s[left] = s[right];
    s[right] = temp;

    reverse_rec(s, left + 1, right - 1);
}

/* reverse: recursive version */
void reverse(char s[])
{
    reverse_rec(s, 0, strlen(s) - 1);
}

int main(void)
{
    char s[100];

    printf("Enter string: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';

    reverse(s);
    printf("Reversed: %s\n", s);

    return 0;
}
