/* list.h  
 * Huzefa Dossaji         <<-- many updates required
 * hdossaj
 * ECE 223 Fall 2015 
 * MP3
 *
 * Public functions for two-way linked list
 *
 * You should not need to change any of the code this file.  If you do, you
 * must get permission from the instructor.
 */

typedef struct llist_node_tag {
    // Private members for list.c only
    data_t *data_ptr;
    struct llist_node_tag *prev;
    struct llist_node_tag *next;
} llist_node_t;

typedef struct list_tag {
    // Private members for list.c only
    llist_node_t *llist_head;
    llist_node_t *llist_tail;
    int llist_size;     // number of items in list
    int llist_sort;     // a flag if list is sorted or unsorted
    // Private method for list.c only
    int (*comp_proc)(const data_t *, const data_t *);
} list_t;

// Public definition of pointer into linked list
typedef llist_node_t * pIterator;
typedef list_t * pList;

// Public prototype definitions for list.c

// build and cleanup lists
pList list_construct(int (*fcomp)(const data_t *, const data_t *));
void list_destruct(pList list_ptr);

// iterators into positions in the list
pIterator list_iter_first(pList list_ptr);
pIterator list_iter_tail(pList list_ptr);
pIterator list_iter_next(pIterator idx_ptr);

data_t * list_access(pList list_ptr, pIterator idx_ptr);
pIterator list_elem_find(pList list_ptr, data_t *elem_ptr);

void list_insert(pList list_ptr, data_t *elem_ptr, pIterator idx_ptr);
void list_insert_sorted(pList list_ptr, data_t *elem_ptr);

void list_sort(pList list_ptr, int sort_type); // added for MP3
void insertion_sort(pList list_ptr); // added for MP3
void SelectionSort(list_t *A, llist_node_t *m, llist_node_t *n); // added for MP3
llist_node_t * FindMax(list_t *A, llist_node_t *m, llist_node_t *n); // added for MP3
void IterativeSelectionSort(list_t *A, llist_node_t *m, llist_node_t *n); // added for MP3
void MergeSort(list_t *A);  // added for MP3
void SplitList(list_t *A, list_t * temp, int sp); // added for MP3
void CombineList(list_t * A,list_t * first, list_t * second); // added for MP3


data_t * list_remove(pList list_ptr, pIterator idx_ptr);

int list_size(pList list_ptr);

/* commands for vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
