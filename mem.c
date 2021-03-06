/* mem.c 
 *
 * Huzefa Dossaji
 * hdossaj
 * Lab4: Dynamic Memory Allocation
 * Version: 1
 * ECE 223, Fall 2015
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "mem.h"

// Global variables required in mem.c only
static chunk_t * Rover = NULL;
static chunk_t Dummy;
void *base = NULL;
static int calls = 0;
static int pages = 0;





#define PAGESIZE 4096

/* function to request 1 or more pages from the operating system.
 *
 * new_bytes must be the number of bytes that are being requested from
 *           the OS with the sbrk command.  It must be an integer 
 *           multiple of the PAGESIZE
 *
 * returns a pointer to the new memory location.  If the request for
 * new memory fails this function simply returns NULL, and assumes some
 * calling function will handle the error condition.  Since the error
 * condition is catastrophic, nothing can be done but to terminate 
 * the program.
 */
chunk_t *morecore(int new_bytes) 
{
	calls++;
	char *cp;
	chunk_t *new_p;
	// preconditions
	assert(new_bytes % PAGESIZE == 0 && new_bytes > 0);
	assert(PAGESIZE % sizeof(chunk_t) == 0);
	cp = sbrk(new_bytes);
	if (cp == (char *) -1)  /* no space available */
		return NULL;
	new_p = (chunk_t *) cp;

	// You should add some code to count the number of calls
	// to sbrk, and the number of pages that have been requested
	// Ex: NumSbrkCalls++; NumPages += new_bytes/PAGESIZE;
	return new_p;
}

/* deallocates the space pointed to by return_ptr; it does nothing if
 * return_ptr is NULL.  
 *
 * This function assumes that the Rover pointer has already been 
 * initialized and points to some memory block in the free list.
 */
void Mem_free(void *return_ptr)
{
	// precondition
	assert(Rover != NULL);
	chunk_t *temp_comp = &Dummy;
	chunk_t *q;
	int one, two, three; 
	int coal_left = FALSE;
	int coal_right = FALSE;
	
	chunk_t *p;
	chunk_t *before;
	
	// to go to the header you have to decrement
	p = (chunk_t *) return_ptr;
	p--;
	
	if(Coalescing){
            while(!(p > temp_comp && p < temp_comp->next) && temp_comp->next != &Dummy){
                temp_comp = temp_comp->next;
             }   
             q=temp_comp->next;
             temp_comp->next=p;
             p->next = q;
             Rover = &Dummy;
             
             
             // check if next to each other in memory
             // left side
             one = temp_comp->size;
             temp_comp = temp_comp + one;
             if(temp_comp == p && Dummy.next != p)
             {
                    coal_left=TRUE;
             }
             temp_comp = temp_comp - one;
             
             // check same thing with right side
             two = p->size;
             p = p + two;
             if (p == q){
                coal_right = TRUE;
             }
             p = p - two;
             three = q->size; 
             
             // coalesing if certain parts are true
             if(coal_left == TRUE && coal_right == FALSE){
                p->next = NULL;
                temp_comp->next = q;
                temp_comp->size = temp_comp->size + two;
                p = NULL;
             }else if(coal_right == TRUE && coal_left == FALSE){
                p->next = q->next; 
                q->next = NULL;
                p->size = p->size + three; 
                q = NULL;
             }else if (coal_left == TRUE && coal_right == TRUE){
                temp_comp->next = q->next;
                temp_comp->size = temp_comp->size + two + three;
                p->next = NULL;
                q->next = NULL;
                p=NULL;
                q=NULL;
             }
            
             
	
	}else{

	before = find_prev(Rover);
	p->next = Rover;
	before->next = p;
	Rover = p;
	
	}
	// sanity check:
//assert(p->size > 1);  //comment out // cannot be 1 since must have at least a header and one additional unit
	//assert(p->next == NULL); // comment out  // if you were careful to null the pointer in mem_alloc


	// obviously the next line is WRONG!!!!  You must fix it.
	// free(return_ptr);
}

/* returns a pointer to space for an object of size nbytes, or NULL if the
 * request cannot be satisfied.  The memory is uninitialized.
 *
 * This function assumes that there is a Rover pointer that points to
 * some item in the free list.  The first time the function is called,
 * Rover is null, and must be initialized with a dummy block whose size
 * is one, but set the size field to zero so this block can never be 
 * removed from the list.  After the first call, the Rover can never be null
 * again.
 */
void *Mem_alloc(const int nbytes)
{
	chunk_t *q;
	chunk_t *before;
	int num_pages;
	int new_bytes;
	int units = nbytes/(sizeof(chunk_t));

	if(nbytes < sizeof(chunk_t)){
		units = 1;
	}else if(nbytes == sizeof(chunk_t)){
		units = 1;
	}
	if(nbytes % sizeof(chunk_t) != 0 ){
		units++;

	}
	units++;
	// precondition
	assert(units*sizeof(chunk_t)>=nbytes);
	assert(nbytes > 0);

	if (Rover == NULL) {
		// if Rover is null, there is a one-time initialization


		num_pages = (nbytes/PAGESIZE);
		if(nbytes%PAGESIZE != 0){
			num_pages++;

		}
		pages=pages + num_pages;


		new_bytes = PAGESIZE * num_pages;                // num_pages is an int
		Rover = morecore(new_bytes);
		Rover->next = &Dummy;
		Rover->size = new_bytes / sizeof(chunk_t);    // num header-sized units
		Dummy.size = 0;
		Dummy.next = Rover;

		q = split_chunk(Rover,units);

		return (q+1);
		//Rover++;
	}   

	else{
		// Here is one strategy to add the new memory to the free list
		//q = Rover + 1;                // move to one unit past start of block 

		q = find_chunk(Rover, units);

		if(q==NULL){


			num_pages = (nbytes/PAGESIZE);
			if(nbytes%PAGESIZE != 0){
				num_pages++;
			}

			pages=pages + num_pages;
			new_bytes = PAGESIZE * num_pages;
			q = morecore(new_bytes);
			q->size = new_bytes/sizeof(chunk_t);
			before = find_prev(Rover);
			q->next = Rover;
			before->next = q; 


			//Mem_free(q);


			q= find_chunk(Rover, units);
		}

		if(q->size == units){
			before = find_prev(Rover);
			before->next = Rover->next;
			Rover = Rover->next;
			q->next = NULL;
			return (q+1); 
		}
		q = split_chunk(q, units);
		return (q+1);




		// q->next= Dummy.next;
		// Dummy.next=q;

		//Mem_free( q );                        // add new segment to free list

		// a temporary line to see the new memory.  Delete this!
		printf("Temporary print to initialize free list\n");
		printf("p=%p, size=%d, end=%p, next=%p\n", 
				Rover, Rover->size, Rover + Rover->size, Rover->next);
	}



	// here are possible post-conditions, depending on your design
	//
	// assume p is a pointer to memory block that will be given to the user
	// and q is the address given to the user
	// assert(p + 1 == q);
	// the minus one in the next two tests is for the header
	//assert((p->size - 1)*sizeof(chunk_t) >= nbytes);
	//assert((p->size - 1)*sizeof(chunk_t) < nbytes + sizeof(chunk_t));
	// assert(p != Rover);
	// return q;

	// obviously the next line is WRONG!!!!  You must fix it.
	//return malloc(nbytes);
}

// this function takes as paramaters a chunkt and the the number of units needed. 
// this function does a certain sort based on the command line input. the sorts could be 
// worst fit, best fit, or first fit. 
chunk_t *find_chunk(chunk_t *last, int units){

	if(Rover->size == units){
		return Rover;
	}

	if(SearchPolicy == BEST_FIT){
		chunk_t *final = NULL;
		chunk_t *end;
		end= Rover;
		int first_difference;
		int new_difference;

		do{
			if(Rover->size >= units){
				final = Rover; 
			}
			if(Rover->size == units){
				Rover = final;
				return Rover;
			}
			Rover = Rover->next;
		}while(Rover!=end);

		if(final == NULL){
			return final; 
		}
		Rover = final;
		end = Rover; 
		first_difference = final->size-units;
		new_difference = first_difference;
		do{
			if((new_difference < first_difference)&&(Rover->size >= units)){
				final = Rover; 
				first_difference = new_difference;
			}
			Rover = Rover->next;
			new_difference = Rover->size - units;

		}while(Rover != end);

		Rover = final;
		return Rover;


	}else if(SearchPolicy == FIRST_FIT){

		chunk_t *end;
		end= Rover;
		do{
			if(Rover->size >= units){
				return Rover;
			}
			Rover = Rover->next;

		}while(Rover!=end);
		return NULL;

	}else if(SearchPolicy == WORST_FIT){
		chunk_t *biggest= NULL;
		chunk_t *end;
		end= Rover;

		do{
			if(Rover->size >= units){
				biggest = Rover; 
				if(Rover->size == units){
				    Rover = biggest; 
				    return Rover;
				}
			}
			Rover = Rover->next;
		}while(Rover!=end);


		if(biggest == NULL){
			return biggest; 
		}
		end = Rover; 

		do{
			if(Rover->size > biggest->size){
				biggest = Rover;
			}   
			Rover = Rover->next;
		}while(Rover!=end);
		Rover = biggest;
		return Rover;
	}
	return NULL;
}

// 
chunk_t * split_chunk(chunk_t *block, int units){
	chunk_t * split;
	//split = Rover;
	if (Rover->size == units){
		split = find_prev(Rover);
		split -> next = Rover -> next;
		split = Rover; 
		Rover=Rover->next;


		return split;
	}
	else{
		split = Rover + Rover->size - units;
		split->next = NULL;
		split->size = units;
		Rover->size = Rover->size - units;
		Rover = Rover->next;
		return split;
	}

}

// function that just finds the previous block of memory to what ever chunk_t is inputted as paramaters
// usefeul since not using two way linked list
chunk_t * find_prev(chunk_t *Rover){
	chunk_t *r;
	r= Rover;
	do{
		r=r->next;
	}while(r->next != Rover);
	return r;

}


/* prints stats about the current free list
 *
 * -- number of items in the linked list including dummy item
 * -- min, max, and average size of each item (in bytes)
 * -- total memory in list (in bytes)
 * -- number of calls to sbrk and number of pages requested
 *
 * A message is printed if all the memory is in the free list
 */
void Mem_stats(void)
{
	//printf("the student must implement mem stats\n");

	printf("The total number of pages that have been requested are: %d\n", pages);
	printf("The total number of calls to sbrk() are: %d\n", calls);

	chunk_t *r;
	r= Rover;
	int items = 0; 
	int total_bytes_allocated = pages*PAGESIZE; 
	int M=0; 
	int average;


	do{
		r=r->next;
		items++;   
		M = r->size + M;

	}while(r != Rover);
	M = M * 16;
	average = M/items;

	printf("The total number of items in the free list are: %d\n", items);

	chunk_t *biggest=r; 
	do{
		if(r->size > biggest->size){
			biggest = r;
		}   
		r = r->next;
	}while(r!=Rover);

	printf("Max = %d\n", biggest->size);

	chunk_t *smallest=r; 
	do{
		if(r->size < smallest->size && (r!=&Dummy)){
			smallest = r;
		}   
		r = r->next;
	}while(r!=Rover);

	printf("Min = %d\n", smallest->size);
	printf("Total Memory in free list = %d\n", M);
	printf("Average = %d\n", average);

	if(total_bytes_allocated == M){

		printf("all memory is in the heap -- no leaks are possible\n");

	}





	// One of the stats you must collect is the total number
	// of pages that have been requested using sbrk.
	// Say, you call this NumPages.  You also must count M,
	// the total number of bytes found in the free list 
	// (including all bytes used for headers).  If it is the case
	// that M == NumPages * PAGESiZE then print
}

/* print table of memory in free list 
 *
 * The print should include the dummy item in the list and should
 * indicate where the Rover in pointing.
 *
 * example format
 *     chunk_t *p;
 *     printf("p=0x%p, size=%d, end=0x%p, next=0x%p\n", 
 *              p, p->size, p + p->size, p->next);
 */
void Mem_print(void)
{
	//printf("the student must implement mem print\n");

	// the following is junk code that must be deleted
	// It just illustrates the format required for the print command
	/*chunk_t *p;
	  p = Rover;

	  do{

	  printf("p=%p, size=%d, end=%p, next=%p\n", 
	  p, p->size, p + p->size, p->next);
	  p = p->next;
	  }while(p!=Rover);*/

	// prints out all information of the free list and the rovers spot at that point
	
	printf("\nRover=%p, size=%d, end=%p, next=%p\n\n", Rover, Rover->size, Rover + Rover->size, Rover->next);	    
	chunk_t *p;
	p = &Dummy;
        printf("FREE LIST\n");
	do{

		printf("p=%p, size=%d, end=%p, next=%p\n", 
				p, p->size, p + p->size, p->next);
		p = p->next;
	}while(p!=&Dummy);

	printf("\n");        

}
/* vi:set ts=8 sts=4 sw=4 et: */

