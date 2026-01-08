/* Exercise 7-8
 * Print files with page headers and page count.
 */

#include <stdio.h>

#define LINESPERPAGE 20
#define MAXLINE 1000

void printfile(FILE *fp, char *fname);

int main(int argc, char *argv[])
{
    FILE *fp;
    int i;

    if (argc < 2) {
        printf("usage: print file ...\n");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "cannot open %s\n", argv[i]);
            continue;
        }
        printfile(fp, argv[i]);
        fclose(fp);
    }
    return 0;
}

void printfile(FILE *fp, char *fname)
{
    char line[MAXLINE];
    int lineno = 0;
    int page = 1;

    /* start new page */
    printf("\f");  /* form feed */
    printf("File: %s    Page: %d\n\n", fname, page);

    while (fgets(line, MAXLINE, fp) != NULL) {
        if (lineno >= LINESPERPAGE) {
            lineno = 0;
            page++;
            printf("\f");
            printf("File: %s    Page: %d\n\n", fname, page);
        }
        fputs(line, stdout);
        lineno++;
    }
}
