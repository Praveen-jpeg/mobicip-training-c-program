/* Exercise 7-7
 * Simple pattern finding program.
 * Reads from named files or standard input.
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getline_kandr(char line[], int max);
void findpattern(FILE *fp, char *pattern, char *fname, int printname);

int main(int argc, char *argv[])
{
    FILE *fp;
    int i;

    if (argc < 2) {
        printf("usage: find pattern [file ...]\n");
        return 1;
    }

    /* No files: read from standard input */
    if (argc == 2) {
        findpattern(stdin, argv[1], NULL, 0);
    } else {
        /* Multiple files */
        for (i = 2; i < argc; i++) {
            if ((fp = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "cannot open %s\n", argv[i]);
                continue;
            }
            findpattern(fp, argv[1], argv[i], 1);
            fclose(fp);
        }
    }
    return 0;
}

/* search for pattern in file */
void findpattern(FILE *fp, char *pattern, char *fname, int printname)
{
    char line[MAXLINE];

    while (fgets(line, MAXLINE, fp) != NULL) {
        if (strstr(line, pattern) != NULL) {
            if (printname)
                printf("%s: ", fname);
            printf("%s", line);
        }
    }
}
