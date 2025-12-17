#include <stdio.h>
#define MAXLINE 1000
#define FOLDWIDTH 40

int main() {
    int c, col = 0;
    char line[MAXLINE];
    int i = 0;

    while ((c = getchar()) != EOF) {
        line[i++] = c;
        col++;
        if (c == '\n' || col >= FOLDWIDTH) {
            int fold_pos = i - 1;
            while (fold_pos > 0 && line[fold_pos] != ' ' && line[fold_pos] != '\t')
                fold_pos--;
            if (fold_pos == 0) fold_pos = i; // hard break if no space
            for (int j = 0; j < fold_pos; j++)
                putchar(line[j]);
            putchar('\n');
            int k = 0;
            for (int j = fold_pos; j < i; j++)
                if (line[j] != ' ' && line[j] != '\t')
                    line[k++] = line[j]; // shift remainder
            i = k;
            col = i;
        }
    }
    for (int j = 0; j < i; j++) // print remaining characters
        putchar(line[j]);
    return 0;
}
    