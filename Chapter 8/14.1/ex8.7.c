#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* 
 * Align type to ensure proper memory alignment for all data types.
 * Using 'long' guarantees that each block header is aligned on
 * the largest required boundary.
 */
typedef long Align; 

/*
 * Header structure for each memory block.
 * - 'next' points to the next free block in the free list.
 * - 'size' stores the size of the allocated block in bytes.
 * - 'magic' is used to detect double free or invalid free operations.
 */
union header {
    struct {
        union header *next;  
        size_t size;         
        unsigned int magic;  
    } s;
    Align x; // ensures proper memory alignment of the header
};

typedef union header Header;

/* Magic numbers for allocation state */
#define MAGIC_ALLOC 0xABCDEF01  // block is currently allocated
#define MAGIC_FREE  0x10FEDCBA  // block is currently free

/* Pointer to the start of the free list */
static Header *freep = NULL; 

/* 
 * Allocate memory of at least nbytes.
 * Returns a pointer to usable memory (after the header).
 */
void *my_malloc(size_t nbytes) {
    if (nbytes == 0) return NULL; // no zero-size allocations

    // allocate a block large enough for the header + requested bytes
    Header *bp = (Header *)malloc(sizeof(Header) + nbytes);
    if (!bp) return NULL; // malloc failed

    bp->s.size = nbytes;    // store the requested size
    bp->s.next = NULL;      // not currently in free list
    bp->s.magic = MAGIC_ALLOC; // mark as allocated

    return (void *)(bp + 1); // return pointer to memory after the header
}

/*
 * Free a previously allocated block.
 * Performs checks for double free or invalid pointer.
 */
void my_free(void *ap) {
    if (!ap) return; // NULL pointer, nothing to free

    Header *bp = (Header *)ap - 1; // get pointer to header

    // check for invalid or double free
    if (bp->s.magic != MAGIC_ALLOC) {
        fprintf(stderr, "free error: invalid or double free!\n");
        return;
    }

    bp->s.magic = MAGIC_FREE; // mark the block as free

    // add the freed block to the start of the free list
    bp->s.next = freep;
    freep = bp;
}

/* ------------------ test program ------------------ */
int main(void) {
    int n;
    printf("Enter number of integers to allocate: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0; // invalid input

    // allocate memory for n integers
    int *arr = (int *)my_malloc(n * sizeof(int));
    if (!arr) {
        printf("Allocation failed.\n");
        return 1;
    }

    // initialize the array
    for (int i = 0; i < n; i++) arr[i] = i + 1;

    // print the array
    printf("Array contents: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    // free the array
    my_free(arr);

    // intentionally try to free again to test error detection
    printf("Trying double free...\n");
    my_free(arr); // will print an error

    printf("Program finished safely.\n");
    return 0;
}
