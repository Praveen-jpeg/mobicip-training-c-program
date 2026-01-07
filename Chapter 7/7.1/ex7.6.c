/* compare: compare two files, print first differing line */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char line1[MAXLINE], line2[MAXLINE];
    int lineno = 0;

    if (argc != 3) {
        printf("usage: compare file1 file2\n");
        exit(1);
    }

    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        printf("error: cannot open %s\n", argv[1]);
        exit(1);
    }

    if ((fp2 = fopen(argv[2], "r")) == NULL) {
        printf("error: cannot open %s\n", argv[2]);
        exit(1);
    }

    while (1) {
    char *r1 = fgets(line1, MAXLINE, fp1);
    char *r2 = fgets(line2, MAXLINE, fp2);

    lineno++;

    if (r1 == NULL && r2 == NULL) {
        printf("Files are identical\n");
        break;
    }

    if (r1 == NULL || r2 == NULL) {
        printf("Files differ in length\n");
        break;
    }

    if (strcmp(line1, line2) != 0) {
        printf("Files differ at line %d:\n", lineno);
        printf("%s: %s", argv[1], line1);
        printf("%s: %s", argv[2], line2);
        break;
    }
}


    /* check if one file ended before the other */
    if (fgets(line1, MAXLINE, fp1) != NULL ||
        fgets(line2, MAXLINE, fp2) != NULL) {
        printf("Files differ in length\n");
    } else {
        printf("Files are identical\n");
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
