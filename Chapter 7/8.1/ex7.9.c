/* Exercise 7-9
 * Compare different implementations of isupper:
 * 1) Space-saving (logic only)
 * 2) Time-saving (lookup table)
 * 3) Macro version (inline, fastest but unsafe)
 */

#include <stdio.h>

/* ---------- space-saving version ---------- */
int isupper_space(int c)
{
    return (c >= 'A' && c <= 'Z');
}

/* ---------- time-saving version ---------- */
static char upper_table[128] = {
    ['A'] = 1, ['B'] = 1, ['C'] = 1, ['D'] = 1, ['E'] = 1,
    ['F'] = 1, ['G'] = 1, ['H'] = 1, ['I'] = 1, ['J'] = 1,
    ['K'] = 1, ['L'] = 1, ['M'] = 1, ['N'] = 1, ['O'] = 1,
    ['P'] = 1, ['Q'] = 1, ['R'] = 1, ['S'] = 1, ['T'] = 1,
    ['U'] = 1, ['V'] = 1, ['W'] = 1, ['X'] = 1, ['Y'] = 1,
    ['Z'] = 1
};

int isupper_time(c)
int c;
{
    if (c < 0 || c >= 128)
        return 0;
    return upper_table[c];
}

/* ---------- macro version (inline, no function call) ---------- */
#define isupper_macro(c) ((c) >= 'A' && (c) <= 'Z')

/* ---------- test program ---------- */
int main()
{
    int c;

    printf("Enter characters, EOF to stop:\n");

    while ((c = getchar()) != EOF) {
        if (c == '\n')
            continue;

        printf("Character '%c' (%d): ", c, c);

        printf("space=%d, ", isupper_space(c));
        printf("time=%d, ", isupper_time(c));
        printf("macro=%d\n", isupper_macro(c));
    }
    return 0;
}
