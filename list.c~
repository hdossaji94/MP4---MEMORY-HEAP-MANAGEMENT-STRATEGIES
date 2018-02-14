    /* list.c                  <<-- A template to be updated and 
 * Huzefa Dossaji         <<-- changed
 * hdossaj
 * ECE 223 Fall 2015
 * MP3
 *
 * Purpose: A template for list.c. The two-way linked list ADT. The interface functions must be exactly defined as
 * described below. You can include additional functions but the interface cannot be changed. 
 *
 * Assumptions: There are many inputs that the functions in this code will accept, it can be packet_t structures, it can be node_t structures
 * most of the functions have the list as one of the inputs so you can modify it. 
 *
 * Bugs: THERE ARE NO BUGS DETECTED EVEN WITH ALL MY EXTENSIVE TESTING
 */

#include <stdlib.h>
#include <assert.h>

#include "datatypes.h"   /* defines data_t */
#include "list.h"        /* defines public functions for list ADT */

/* definitions for private constants used in list.c only */

#define LIST_SORTED   -1234
#define LIST_UNSORTED -4132

/* prototypes for private functions used in list.c only */
void list_validate(list_t *L);

/* ----- below are the functions  ----- */

/* Allocates a new, empty list 
 *
 * By convention, the list is initially assumed to be sorted.  The field sorted
 * can only take values LIST_SORTED or LIST_UNSORTED
 *
 * The inital empty list must have
 * 1.  a dummy head llist_node_t
 * 2.  a dummy tail llist_node_t
 * 3.  llist_size = 0
 * 4.  llist_sort = LIST_SORTED
 * 4.  comp_proc = pointer to comparison function
 *
 * Use list_decontruct to remove and deallocate all elements on a list,
 * the dummy head and tail, and the header block.
 */
list_t * list_construct(int (*fcomp)(const data_t *, const data_t *))
{

    list_t *L = NULL;
   
    
    L = (list_t*)malloc(sizeof(list_t));
   
    
    L->llist_head = (llist_node_t *)malloc(sizeof(llist_node_t));
    L->llist_tail = (llist_node_t *)malloc(sizeof(llist_node_t));
    
    
    
    L->llist_size = 0;
    L->llist_sort = LIST_SORTED;
    L->comp_proc = fcomp;
    
    L->llist_head->data_ptr = NULL; //Dummy head
    L->llist_tail->data_ptr = NULL;
    L->llist_head->next = L->llist_tail;
    L->llist_tail->prev = L->llist_head;
    L->llist_head->prev = NULL;
    L->llist_tail->next = NULL;
    /* the last line of this function must call validate */
    //list_validate(L); //commented out for effeciecny for mp3
    return L;
}

/* Deallocates the contents of the specified list, releasing associated memory
 * resources for other purposes.
 *
 * Free all elements in the list, the dummy head and tail, and the header 
 * block.
 */
void list_destruct(list_t *list_ptr)
{
    /* the first line must validate the list */
    //list_validate(list_ptr); //commented out for effeciecny for mp3
    
    llist_node_t * fire = NULL;
    fire = list_iter_first(list_ptr);
    free(list_ptr->llist_head);
    
    
    while(fire != NULL && fire != list_ptr->llist_tail){
        free(fire->data_ptr);
        fire->data_ptr=NULL;
        fire->prev=NULL;
        fire=fire->next;
        fire->prev->next=NULL;
        free(fire->prev);
    
     }
    list_ptr->llist_tail->prev=NULL;
    free(list_ptr->llist_tail);
    list_ptr->llist_tail=NULL;
    list_ptr->llist_head=NULL;
    free(list_ptr);


}

/* Return an Iterator that points to the first element in the list.  If the
 * list is empty the pointer that is returned is equal to the dummy tail
 * llist_node_t.
 */
llist_node_t * list_iter_first(list_t *list_ptr)
{
    assert(list_ptr != NULL);
   // list_validate(list_ptr); //commented out for effeciecny for mp3
    return list_ptr->llist_head->next;

}

/* Return an Iterator that always points to the dummy tail llist_node_t. 
 */
llist_node_t * list_iter_tail(list_t *list_ptr)
{
    assert(list_ptr != NULL);
   // list_validate(list_ptr); //commented out for effeciecny for mp3
    return list_ptr->llist_tail;
}

/* Advance the Iterator to the next item in the list.  The Iterator must not be
 * pointing to the dummy tail llist_node_t.
 *
 * To determine if an Iterator is past the last element and pointing to the
 * tail compare the Iterator to list_iter_tail.  Only if they are equal has
 * the Iterator moved past the last element.
 *
 * It is only valid to compare the Iterator to list_iter_first or 
 * list_iter_tail
 *
 * It is a catastrophic error to call this function if the
 * iterator, idx_ptr, is null or points to the tail.
 */
llist_node_t * list_iter_next(llist_node_t * idx_ptr)
{
   
    assert(idx_ptr != NULL && idx_ptr->next != NULL);
    return idx_ptr->next;
}

/* Obtains a pointer to an element stored in the specified list, at the
 * specified Iterator position
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from list_construct.
 *
 * idx_ptr: pointer to position of the element to be accessed.  This pointer
 *          must be obtained from list_elem_find, list_iter_first, or
 *          list_iter_next.  
 *
 * return value: pointer to the data_t element found in the list at the 
 * iterator position. A value NULL is returned if 
 *     1.  the list is empty 
 *     2.  the idx_ptr points to the dummy head or dummy tail
 */
data_t * list_access(list_t *list_ptr, llist_node_t * idx_ptr)
{
    assert(list_ptr != NULL);
    assert(idx_ptr != NULL);

    if(list_ptr->llist_head->next==NULL){
        return NULL;
    }

    /* debugging function to verify that the structure of the list is valid */
  //  list_validate(list_ptr); //commented out for effeciecny for mp3

    return idx_ptr->data_ptr;   
}

/* Finds an element in a list and returns a pointer to it.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: element against which other elements in the list are compared.
 *           Note: use the comp_proc function pointer found in the list_t 
 *           header block. 
 *
 * The function returns an Iterator pointer to the llist_node_t that contains 
 * the first matching element if a match if found.  If a match is not found 
 * the return value is NULL.
 *
 * Note: to get a pointer to the matching data_t memory block pass the return
 *       value from this function to the list_access function.
 */
llist_node_t * list_elem_find(list_t *list_ptr, data_t *elem_ptr)
{
   // list_validate(list_ptr); //commented out for effeciecny for mp3

    // Your code starts here
    llist_node_t *find = NULL;
    llist_node_t *comp = NULL;
    
    int compare;
    
    
    
    comp=list_ptr->llist_head->next;
    
        while((comp!=NULL) || (comp!=list_ptr->llist_tail) ){
            if(comp == list_ptr->llist_tail){
                break;
            }
            compare = (list_ptr->comp_proc)(elem_ptr, comp->data_ptr);
            if(compare ==0){
             return comp;
            }
            comp = comp->next;
        }
    free(find);
 
    return NULL;
}

/* Inserts the data element into the list in front of the llist_node_t 
 * iterator position.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * idx_ptr: pointer to a llist_node_t.  The element is to be inserted as a 
 *          member in the list at the position that is immediately in front 
 *          of the position of the provided Iterator pointer.
 *
 * If idx_ptr is set using 
 *    -- list_iter_first, then the new element becomes the first item in 
 *       the list.
 *    -- list_iter_tail, then the new element becomes the last item in 
 *       the list.
 *    -- for any other idx_ptr, the new element is insert before the 
 *       Iterator
 *
 * For example, to insert at the tail of the list do
 *      list_insert(mylist, myelem, list_iter_tail(mylist))
 * to insert at the front of the list do
 *      list_insert(mylist, myelem, list_iter_first(mylist))
 *
 * Note that use of this function results in the list to be marked as unsorted,
 * even if the element has been inserted in the correct position.  That is, on
 * completion of this subroutine the list_ptr->llist_sort must be equal 
 * to LIST_UNSORTED.
 */
void list_insert(list_t *list_ptr, data_t *elem_ptr, llist_node_t * idx_ptr)
{
    assert(list_ptr != NULL);
    llist_node_t *new = NULL;
    
    new = (llist_node_t*)malloc(sizeof(llist_node_t));
    new->data_ptr=elem_ptr;

    if(list_ptr->llist_size==0){

	    list_ptr->llist_head->next=new;
	    list_ptr->llist_tail->prev = new;
	    new->prev=list_ptr->llist_head;
	    new->next=list_ptr->llist_tail;

	    list_ptr->llist_size++;
    }
    else if(idx_ptr == list_ptr->llist_head->next)
    {
	    new->next=list_ptr->llist_head->next;
	    new->prev=list_ptr->llist_head;
	    new->next->prev=new;
	    list_ptr->llist_head->next = new;
	    list_ptr->llist_size++;

    }
    else if(idx_ptr==list_ptr->llist_tail)
    {
	    new->next=list_ptr->llist_tail;
	    new->prev=list_ptr->llist_tail->prev;
	    new->prev->next=new;
	    list_ptr->llist_tail->prev=new;
	    list_ptr->llist_size++;
    }



    /* the last three lines of this function must be the following */
    if (list_ptr->llist_sort == LIST_SORTED) 
	    list_ptr->llist_sort = LIST_UNSORTED;
   // list_validate(list_ptr); //commented out for effeciecny for mp3
}

/* Inserts the element into the specified sorted list at the proper position,
 * as defined by the compare_proc.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * If you use list_insert_sorted, the list preserves its sorted nature.
 *
 * If you use list_insert, the list will be considered to be unsorted, even
 * if the element has been inserted in the correct position.
 *
 * If the list is not sorted and you call list_insert_sorted, this subroutine
 * must generate a system error and the program should immediately stop.
 *
 * The comparison procedure must accept two arguments (A and B) which are both
 * pointers to elements of type data_t.  The comparison procedure returns an
 * integer code which indicates the precedence relationship between the two
 * elements.  The integer code takes on the following values:
 *    1: A should be closer to the list head than B
 *   -1: B should be closer to the list head than A
 *    0: A and B are equal in rank
 *
 * Note: if the element to be inserted is equal in rank to an element already
 * in the list, the newly inserted element will be placed after all the
 * elements of equal rank that are already in the list.
 */
void list_insert_sorted(list_t *list_ptr, data_t *elem_ptr)
{
	assert(list_ptr != NULL);
	assert(list_ptr->llist_sort == LIST_SORTED);

	llist_node_t *A = NULL;
	llist_node_t *B = NULL;

	int compare;
	int times=0;
	int match = 0;



	/* insert your code here */
	A = (llist_node_t*)malloc(sizeof(llist_node_t));
	 

	A->data_ptr=elem_ptr;
	// for the first packet to be inserted
	if(list_ptr->llist_size==0){

		list_ptr->llist_head->next=A;
		list_ptr->llist_tail->prev = A;
		A->prev=list_ptr->llist_head;
		A->next=list_ptr->llist_tail;

		list_ptr->llist_size++;
	}
	// the rest of the function when list has multiple packets
	else{
		B=list_ptr->llist_head->next;
		while((B!=NULL) || (B!=list_ptr->llist_tail)){
			// compare_proc will receive either 1, -1, or 0 based on order
			if(B->data_ptr == NULL){
				A->next=list_ptr->llist_tail;
				A->prev=list_ptr->llist_tail->prev;
				A->prev->next=A;
				list_ptr->llist_tail->prev=A;
				list_ptr->llist_size++;    
				break;       
			}
			compare = (list_ptr->comp_proc)(A->data_ptr, B->data_ptr);

			// when A needs to be placed in front of B
			if(compare == 1)
			{
				A->next=B;
				A->prev=B->prev;
				B->prev->next=A;
				B->prev=A;
				list_ptr->llist_size++;
				break;
			}
			// When B needs to be placed in front of A
			else if(compare == -1)
			{
				//when the node right after B is the llist tail
				B=B->next;
				times++;
			}
			else if(compare == 0){
                                    
				if((list_ptr->comp_proc)(B->data_ptr, list_ptr->llist_tail->prev->data_ptr) == 0){

					while((compare == 0) && (B->data_ptr != NULL)){
						compare = (list_ptr->comp_proc)(A->data_ptr, B->data_ptr);
						B=B->next;
						match++;

					}

					B = B->prev;

				}else{
					while((compare == 0) && (B->data_ptr != NULL)){
						compare = (list_ptr->comp_proc)(A->data_ptr, B->data_ptr);
						B=B->next;
						match++;
						compare = (list_ptr->comp_proc)(A->data_ptr, B->data_ptr);
					}

					B = B->prev;

				}   

				A->next=B->next;
				A->prev=B;
				B->next->prev=A;
				B->next=A;
				list_ptr->llist_size++;

				match = 0;
				break;
			}
		}
	}
	/* the last line of this function must be the following */
	// list_validate(list_ptr); //commented out for effeciecny for mp3
}

/*

These are the new codes from C Programs from Chapter 5. Change them to deal with pointers not arrays. 





*/

void list_sort(pList list_ptr, int sort_type)
{
   
    if(list_size(list_ptr)==0){
        // DO NOTHING
    }
    else if(sort_type==1){
        insertion_sort(list_ptr);
       
        
    }
    else if(sort_type ==2){
        SelectionSort(list_ptr, list_iter_first(list_ptr), list_iter_tail(list_ptr)->prev);
       
    }
    else if(sort_type == 3){
        IterativeSelectionSort(list_ptr, list_iter_first(list_ptr), list_iter_tail(list_ptr)->prev);
        
    }
    else if(sort_type==4){
        MergeSort(list_ptr);
        
    }
    
    
    list_ptr->llist_sort = LIST_SORTED;
    list_validate(list_ptr);
}

void insertion_sort(pList list_ptr){

        list_t *new_list;
        new_list = list_construct(list_ptr->comp_proc);
        while(list_size(list_ptr) != 0){
            list_insert_sorted(new_list, list_remove(list_ptr, list_iter_first(list_ptr)));
        }
        free(list_ptr->llist_head);
        free(list_ptr->llist_tail);
        list_ptr->llist_head = new_list->llist_head;
        list_ptr->llist_tail = new_list->llist_tail;
        list_ptr->comp_proc= new_list->comp_proc;
        list_ptr->llist_size = new_list->llist_size;
        list_ptr->llist_sort = LIST_SORTED;
        free(new_list);
        new_list=NULL;

}

// FUNCTION TO FIND MAX DATA PTR IN THE LIST. USED IN THE RECURSIVCE FUNCTION SELECTION SORT
llist_node_t * FindMax(list_t *A, llist_node_t *m, llist_node_t *n)   /* assume m<n */
{
    llist_node_t * a = m;
    llist_node_t * b = m;
    int compare;
      
  do{    
     a=a->next;
     compare = (A->comp_proc)(a->data_ptr, b->data_ptr);     
         if(compare == -1){
            b=a;
            }
           
   }while(a->next!=n->next);
   
   return b;                       /* return j == position of the largest */
}                                                /* number A[j] in A[m:n] */

// RECURSIVE FUNCTION THAT SORTS THE LIST IN ASSCENDING ORDER BY FINDING THE MAX AND PUTTING IT THE BACK OF THE LIST
void SelectionSort(list_t *A, llist_node_t *m, llist_node_t *n)
{
   llist_node_t * MaxPosition=NULL;    /* MaxPosition is the index of A's biggest item  */
       data_t * temp = NULL;        /* temp is used to exchange items in A */
   
   
     
   if (n!=list_iter_first(A)) {             
   
     
         MaxPosition = FindMax(A,m,n);
      
      
         temp = MaxPosition->data_ptr;
         MaxPosition->data_ptr=n->data_ptr;
         n->data_ptr=temp;
      
     
         SelectionSort(A, m, n->prev);
   }
   //free(MaxPosition);
   //free(temp);
   //MaxPosition = NULL;
   //temp=NULL;
   
}

// ITERATIVE FUNCTION THAT DOES THE SAME THING AS THE SELECION SORT EXCEPT WITHOUT RECURSION, MUCH MORE EFFECIENT.
void IterativeSelectionSort(list_t *A, llist_node_t *m, llist_node_t *n)
{
   llist_node_t * MaxPosition;
    data_t *temp = NULL;
    int compare;

   while (n!=list_iter_first(A)) {
   
      MaxPosition = FindMax(A,m,n);

         compare = (A->comp_proc)(n->data_ptr, MaxPosition->data_ptr);
         if ( compare == 1 ) {
            temp = MaxPosition->data_ptr;
            MaxPosition->data_ptr=n->data_ptr;
            n->data_ptr=temp;
            }
            
            n=n->prev;
      
      }
     
     // free(MaxPosition);
     // free(temp);
      temp=NULL;
      MaxPosition = NULL;
}

// 4TH OPTION IN LIST_SORT, MERGE SORT WHICH WILL SPLIT THE LISTS IN HALF THEN SORT THEM AND THEN ADD THE TWO SORTED LIST INTO 1 BIGGER LIST. 
void MergeSort(list_t *A)
{
    list_t *first_list;
    list_t *second_list;
    first_list = list_construct(A->comp_proc);
    second_list = list_construct(A->comp_proc);
    int sp1, sp2;
    
   if (list_size(A) > 1) {
      sp1 = list_size(A)/2;
      sp2 = sp1;
      if(list_size(A)%2 != 0){
        sp1 = sp1+1;
      }
      
      SplitList(A,first_list, sp1);
      SplitList(A,second_list, sp2);
      MergeSort(first_list);
      MergeSort(second_list);
      CombineList(A,first_list,second_list);
      
   } else {
      //(do nothing, since the list is already sorted)
     
   }
   list_destruct(first_list);
   list_destruct(second_list);
}

void SplitList(list_t *A, list_t * temp, int sp){

int a=1;

    llist_node_t * rover = NULL;
    temp->llist_head->next=A->llist_head->next;
    temp->llist_sort=LIST_UNSORTED;
    temp->comp_proc=A->comp_proc;
    rover = A->llist_head->next;
    rover->prev=temp->llist_head;
    

   
    
    while(a<sp) {
            rover = rover->next;
           a++;
          
    }
    rover->next->prev=A->llist_head;
    A->llist_head->next=rover->next;
    rover->next=temp->llist_tail;
    temp->llist_tail->prev = rover;
    temp->llist_size=sp;
    A->llist_size=A->llist_size-sp;
    
   // free(rover);
    rover=NULL;
    
    
}

void CombineList(list_t * A,list_t * first, list_t * second){
    llist_node_t *fp=NULL;
    llist_node_t *sp=NULL;
    fp=first->llist_head->next;
    sp=second->llist_head->next;
 
    
    
    while((first->llist_size != 0) && (second->llist_size != 0)){
        
        
        if((A->comp_proc)(fp->data_ptr,sp->data_ptr)==1){
            list_insert(A, list_remove(first, fp), A->llist_tail);
            fp=list_iter_first(first);
        }
        else{
            list_insert(A, list_remove(second, sp), A->llist_tail);
            sp=list_iter_first(second);
        }   
    }   
    while(first->llist_size > 0){
        list_insert(A, list_remove(first, fp), A->llist_tail);
            fp=list_iter_first(first);
    }
    while(second->llist_size > 0){
        list_insert(A, list_remove(second, sp), A->llist_tail);
            sp=list_iter_first(second);
    }
    
    
    fp=NULL;
    sp=NULL;
   
    
}


/* Removes the element from the specified list that is found at the 
 * Iterator llist_node_t index.  A pointer to the data element is returned.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * idx_ptr: pointer to position of the element to be accessed.  This pointer
 *          must be obtained from list_elem_find, list_iter_first, 
 *          list_iter_next, or list_iter_tail.  
 *
 * If the list is empty, then the function should return NULL.
 *
 * Note: it is easy to remove the element at the front of the list using
 *     list_remove(mylist, list_iter_first(mylist))
 *
 * However, removing the element at the end of the list is not easy since
 * there is no way to get the pointer to the last element in the list.  
 * Notice that list_iter_tail returns a pointer to the dummy tail, not the 
 * last element in the list.
 *
 * Note: a significant danger with this function is that once
 * an element is removed from the list, the idx_ptr is dangling.  That
 * is, the idx_ptr now points to memory that is no longer valid.
 * You should not call list_iter_next on an iterator after there
 * has been a call to list_remove with the same iterator.
 *
 * When you remove the llist_node_t in this function, you should null the next
 * and prev pointers before you free the memory block to avoid accidental use
 * of these now invalid pointers. 
 */
data_t * list_remove(list_t *list_ptr, llist_node_t * idx_ptr)
{
	if (idx_ptr == NULL)
		return NULL;
	assert(idx_ptr != list_ptr->llist_head && idx_ptr != list_ptr->llist_tail);

	/* insert your code here */
	data_t *remove = NULL;
	


	if(list_ptr->llist_size==0){
		
		return NULL;
	}
	// conditional when the element right before the tail needs to be removed
	if(idx_ptr == list_ptr->llist_tail){  
		remove = list_ptr->llist_tail->prev->data_ptr;
		list_ptr->llist_tail->prev->data_ptr = NULL;
		list_ptr->llist_tail->prev = list_ptr->llist_tail->prev->prev;
		list_ptr->llist_tail->prev->next = list_ptr->llist_tail;
		idx_ptr->next = NULL;
		idx_ptr->prev = NULL;
		free(idx_ptr);
		list_ptr->llist_size--;

		return remove;
	}
	// conditional for every other element removal.
	else{
		remove = idx_ptr->data_ptr;
		idx_ptr->data_ptr = NULL;
		idx_ptr->prev->next = idx_ptr->next;
		idx_ptr->next->prev = idx_ptr->prev;
		idx_ptr->next = NULL;
		idx_ptr->prev = NULL;
		free(idx_ptr);
		list_ptr->llist_size--;

		return remove;

	}
	/* the last line should verify the list is valid after the remove */
	//list_validate(list_ptr); //commented out for effeciecny for mp3
	return NULL;  
}

/* Obtains the length of the specified list, that is, the number of elements
 * that the list contains.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * Returns an integer equal to the number of elements stored in the list.  An
 * empty list has a size of zero.
 */
int list_size(list_t *list_ptr)
{
	assert(list_ptr != NULL);
	assert(list_ptr->llist_size >= 0);
	return list_ptr->llist_size;
}


/* This function verifies that the pointers for the two-way linked list are
 * valid, and that the list size matches the number of items in the list.
 *
 * If the linked list is sorted it also checks that the elements in the list
 * appear in the proper order.
 *
 * The function produces no output if the two-way linked list is correct.  It
 * causes the program to terminate and print a line beginning with "Assertion
 * failed:" if an error is detected.
 *
 * The checks are not exhaustive, so an error may still exist in the
 * list even if these checks pass.
 *
 * YOU MUST NOT CHANGE THIS FUNCTION.  WE USE IT DURING GRADING TO VERIFY THAT
 * YOUR LIST IS CONSISTENT.
 */
void list_validate(list_t *L)
{
	llist_node_t *N;
	int count = 0;
	assert(L != NULL && L->llist_head != NULL && L->llist_tail != NULL);
	assert(L->llist_head != L->llist_tail);
	assert(L->llist_head->prev == NULL && L->llist_tail->next == NULL);
	assert(L->llist_head->data_ptr == NULL && L->llist_tail->data_ptr == NULL);
	assert(L->llist_head->next != NULL && L->llist_tail->prev != NULL);
	assert(L->llist_sort == LIST_SORTED || L->llist_sort == LIST_UNSORTED);

	N = L->llist_head->next;
	assert(N->prev == L->llist_head);
	while (N != L->llist_tail) {
		assert(N->data_ptr != NULL);
		assert(N->next->prev == N);
		count++;
		N = N->next;
	}
	assert(count == L->llist_size);
	if (L->llist_sort == LIST_SORTED && L->llist_size > 0) {
		N = L->llist_head->next;
		while (N->next != L->llist_tail) {
			assert((L->comp_proc)(N->data_ptr, N->next->data_ptr) != -1);
			N = N->next;
		}
	}
}
/* commands for vim. ts: tabstop, sts: softtabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */

