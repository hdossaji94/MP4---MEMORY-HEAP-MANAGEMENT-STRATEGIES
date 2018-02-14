/* mem.h 
 * Lab4: Dynamic Memory Allocation
 * Version: 1
 * ECE 223, Fall 2015
 * Huzefa Dossaji 
 * Harlan Russell 
 * hdossaj
 */

#define FIRST_FIT  0xFFFF 
#define BEST_FIT   0xBBBB
#define WORST_FIT  0x5555
#define TRUE 1
#define FALSE 0

/* must be FIRST_FIT or BEST_FIT or WORST_FIT */
int SearchPolicy;

/* TRUE if memory returned to free list is coalesced */
int Coalescing;

/* deallocates the space pointed to by return_ptr; it does nothing if
 * return_ptr is NULL.  
 */
void Mem_free(void *return_ptr);

/* returns a pointer to space for an object of size nbytes, or NULL if the
 * request cannot be satisfied.  The space is uninitialized.
 */
void *Mem_alloc(const int nbytes);

/* prints stats about the current free list
 *
 * number of items in the linked list
 * min, max, and average size of each item (bytes)
 * total memory in list (bytes)
 * number of calls to sbrk and number of pages requested
 */
void Mem_stats(void);

/* print table of memory in free list 
 * example format
 *     chunk_t *p;
 *     printf("p=%p, size=%d, end=%p, next=%p\n", 
 *              p, p->size, p + p->size, p->next);
 */
void Mem_print(void);
/* an example of a chunk_t definition.  You must modify this to
 * match your design
 *
 * We don't really need the definition of chunk_t in mem.h.  However,
 * for debugging it is nice to be able to print the size of chunk_t
 * in the drivers.
 * 
 */
typedef struct chunk_tag {
    struct chunk_tag *next;
    int size;
} chunk_t;


chunk_t *find_chunk(chunk_t *last,  int units);

chunk_t * split_chunk(chunk_t *block, int units);

chunk_t * find_prev(chunk_t *Rover);

/* vi:set ts=8 sts=4 sw=4 et: */
