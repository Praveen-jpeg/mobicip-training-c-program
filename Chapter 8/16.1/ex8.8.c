/*
 * Memory allocator with bfree
 * Exercise 8-8
 *
 * Uses my_malloc / my_free (does NOT redefine system malloc/free)
 */

#include <stdio.h>

/* force alignment to long boundary */
typedef long Align;

/* block header */
union header {
    struct {
        union header *ptr;  /* next block on free list */
        unsigned size;      /* size of block (in Header units) */
    } s;
    Align x;                /* force alignment */
};

typedef union header Header;

static Header base;         /* empty list to get started */
static Header *freep = NULL;

/*
 * my_free: put block ap in free list
 */
void my_free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;  /* point to block header */

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;          /* freed block at start or end */
    }

    /* join to upper neighbor */
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }

    /* join to lower neighbor */
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }

    freep = p;
}

/*
 * my_malloc: general-purpose storage allocator
 */
void *my_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    /* number of Header-sized units needed */
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {     /* big enough */
            if (p->s.size == nunits)   /* exact fit */
                prevp->s.ptr = p->s.ptr;
            else {                     /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }

        if (p == freep)                /* wrapped around free list */
            return NULL;
    }
}

/*
 * bfree: add a block of n bytes starting at p
 *        to the free list used by my_malloc/my_free
 */
void bfree(void *p, unsigned n)
{
    Header *bp;
    unsigned nunits;

    if (n < sizeof(Header))
        return;

    /* initialize free list if not already done */
    if (freep == NULL) {
        base.s.ptr = freep = &base;
        base.s.size = 0;
    }

    bp = (Header *)p;
    nunits = n / sizeof(Header);

    if (nunits < 1)
        return;

    bp->s.size = nunits;

    /* free expects pointer to data area */
    my_free((void *)(bp + 1));
}

/* ---------------- example usage ---------------- */

#define MAXPOOL 2000000
static char pool[MAXPOOL];

int main()
{
    unsigned poolsize, allocsize;
    char *p;

    /* ask user for pool size */
    printf("Enter pool size (max %d bytes): ", MAXPOOL);
    scanf("%u", &poolsize);

    if (poolsize > MAXPOOL) {
        printf("Pool size too large. Using maximum %d bytes.\n", MAXPOOL);
        poolsize = MAXPOOL;
    }

    /* ask user for allocation size */
    printf("Enter allocation size (bytes): ");
    scanf("%u", &allocsize);

    /* donate the requested pool size to allocator */
    bfree(pool, poolsize);

    /* try to allocate user-requested memory */
    p = (char *)my_malloc(allocsize);
    if (p != NULL)
        printf("my_malloc succeeded: allocated %u bytes\n", allocsize);
    else
        printf("my_malloc failed: not enough memory\n");

    return 0;
}
