/* calloc: allocate and clear memory */

#include <stdio.h>
#include <stdlib.h>

char *mycalloc(int,int);

main()
{
    int n, size, i;
    char *p;

    printf("Enter number of objects: ");
    scanf("%d", &n);

    printf("Enter size of each object: ");
    scanf("%d", &size);

    p = mycalloc(n, size);

    if (p == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    /* demonstrate that memory is zeroed */
    for (i = 0; i < n * size; i++)
        printf("%d ", p[i]);

    printf("\n");

    free(p);
    return 0;
}

char *mycalloc(int n, int size)
{
    char *p;
    int i, total;

    total = n * size;
    p = malloc(total);

    if (p == NULL)
        return NULL;

    for (i = 0; i < total; i++)
        p[i] = 0;

    return p;
}
