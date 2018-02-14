# MP4---MEMORY-HEAP-MANAGEMENT-STRATEGIES

[PLEASE SEE mp4.pdf FILE FOR FULL INSTRUCTIONS AND EXPLANATION!](mp4.pdf)

The goal of this machine problem is to investigate strategies for managing a memory heap.


Management of memory heap

You are to design four procedures to manage the memory heap.

void *Mem_alloc(const int nbytes);
Returns a pointer to space for an object of size nbytes, or NULL if the request cannot be satisfied. The space is uninitialized. It should first check your free list to determine if the requested memory can be allocated from the free list. If there is no memory block available to accommodate the request, then a new segment of memory should be requested from the system using the system call sbrk() and the memory should be put in the free list. After adding the additional memory to the free list, a memory block of the correct size can now be found. So, the Mem_alloc function will return NULL only if the sbrk() call fails because the system runs out of memory.

void Mem_free(void *return_ptr);
Deallocates the space pointed to by return_ptr by returning the memory block to the free list; it does nothing if return_ptr is NULL. return_ptr must be a pointer to space previously allocated by Mem_alloc

void Mem_stats(void);
Prints statistics about the current free list at the time the function is called. At the time the function is called scan the free list and determine the following information. (You can print additional information)
• number of items in the list
• min, max, and average size (in bytes) of the chunks of memory in the free list
• total memory stored in the free list (in bytes). Define this to be M.
• number of calls to sbrk() and the total number of pages requested (define as P)
• If M is equal to P * PAGESIZE, then print the message “all memory is in the heap – no leaks are possible”

void Mem_print(void);
Print a table of the memory in the free list. Here is an example for the format, but you must modify this to suit your design. The pointer “chunk_t *p” points to one memory chunk in the list

printf("p=%p, size=%d, end=%p, next=%p\n", p, p->size, p + p->size, p->next);
