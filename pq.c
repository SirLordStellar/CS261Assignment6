/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Sophia Pole
 * Email: poles@oregonstate.edu
 */

#include <stdlib.h>
#include <math.h>
#include "dynarray.h"

#include "pq.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 * in addition, you want to define an element struct with both data and priority, 
 * corresponding to the elements of the priority queue. 
 */
struct pq {
  struct dynarray* heap;
};


struct pqnode {
  void* value;
  int priority; 
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* retpq = malloc(sizeof(struct pq));
  retpq -> heap = dynarray_create();
  return retpq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  dynarray_free(pq -> heap);
  free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  if (dynarray_length(pq -> heap) == 0) {
    return 1;
  }
  return 0;
}

void dynarray_swap(struct dynarray* dynarray, int index1, int index2) {
  void* temp1 = dynarray_get(dynarray, index1);
  dynarray_set(dynarray, index1, dynarray_get(dynarray, index2));
  dynarray_set(dynarray, index2, temp1);
}


int percdown(struct dynarray* dy, int i) {
  int garbage = 0;
  if (dynarray_length(dy) == 0) {
    return 0;
  }
  int p = ((struct pqnode*)(dynarray_get(dy, i))) -> priority;
  int left = (2 * i) + 1;
  int right = (2 * i) + 2;
  //If the node we're looking at has no child nodes, we're done here
  if (left >= dynarray_length(dy)) {
    return 0;
  }
  int leftp = ((struct pqnode*)(dynarray_get(dy, 2 * i + 1))) -> priority;
  //If the node we're looking at has only one child node, we'll just think about switching them
  if (right >= dynarray_length(dy)) {
    if (leftp > p) {
      dynarray_swap(dy, i, left);
      percdown(dy, left);
      return 0;
    }
  }
  int rightp = ((struct pqnode*)(dynarray_get(dy, 2 * i + 2))) -> priority;
  //Else, we have to look at both
  if (leftp > p || rightp > p) {
    //Swap with whichever is higher if not heap
    if (leftp > rightp) {
      dynarray_swap(dy, right, left);
      dynarray_swap(dy, i, right);
    } else {
      dynarray_swap(dy, i, right);
    }
    percdown(dy, left);
    percdown(dy, right);
    return 0;
  }
}

void percolatedown(struct dynarray* dy) {
  int i = 0;
  while (i < dynarray_length(dy) - 1) {
    if (2 * i + 1 > dynarray_length(dy) - 1) {
      break;
    }
    if (2 * i + 2 > dynarray_length(dy) - 1) {
      if (((struct pqnode*)(dynarray_get(dy, i))) -> priority < ((struct pqnode*)(dynarray_get(dy, 2 * i + 1))) -> priority) {
        dynarray_swap(dy, i, 2 * i + 1);
        i = 2 * i + 1;
      }
      break;
    }
    if (((struct pqnode*)(dynarray_get(dy, i))) -> priority < ((struct pqnode*)(dynarray_get(dy, 2 * i + 1))) -> priority || ((struct pqnode*)(dynarray_get(dy, i))) -> priority < ((struct pqnode*)(dynarray_get(dy, 2 * i + 2))) -> priority) {
      if (((struct pqnode*)(dynarray_get(dy, 2 * i + 1))) -> priority > ((struct pqnode*)(dynarray_get(dy, 2 * i + 2))) -> priority) {
        dynarray_swap(dy, i, 2 * i + 1);
        i = 2 * i + 1;
      } else {
        dynarray_swap(dy, i, 2 * i + 2);
        i = 2 * i + 2;
      }
    } else {
      break;
    }
  }
}




/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, higher priority
 * values are given precedent, and higher place in the queue.  In other words, the
 * element in the priority queue with the highest priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   data - the data value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, higher priority values
 *     should correspond to the first elements.  In other words,
 *     the element in the priority queue with the highest priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* data, int priority) {
  struct pqnode* inser = malloc(sizeof(struct pqnode));
  inser -> priority = priority;
  inser -> value = data;
  dynarray_insert(pq -> heap, -1, inser);
  int i = dynarray_length(pq -> heap) - 1;
  while (i != 0 && ((struct pqnode*)(dynarray_get(pq -> heap, i))) -> priority >= ((struct pqnode*)(dynarray_get(pq -> heap, floor((i - 1)/2)))) -> priority) {
    dynarray_swap(pq -> heap, i, floor((i - 1)/2));
    i = floor((i - 1)/2);
  }
}



/*
 * This function should return the data of the first element in a priority
 * queue, i.e. the data associated with the element with highest priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the data of the first item in pq, i.e. the item with
 *   max priority value.
 */
void* pq_max(struct pq* pq) {
  return ((struct pqnode*)(dynarray_get(pq -> heap, 0))) -> value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with highest priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with highest priority value.
 */
int pq_max_priority(struct pq* pq) {
  return ((struct pqnode*)(dynarray_get(pq -> heap, 0))) -> priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with highest priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   highest priority value.
 */
void* pq_max_dequeue(struct pq* pq) {
  void* temp = ((struct pqnode*)(dynarray_get(pq -> heap, 0))) -> value;
  dynarray_remove(pq -> heap, 0);
  //If there are no elements left or only one element, the heap property must be already satisfied
  if (dynarray_length(pq -> heap) == 0 || dynarray_length(pq -> heap) == 1) {
    return temp;
  }
  //The rest of the cases, we gotta do that moving the highest-priority element to the end thing
  dynarray_insert(pq -> heap, 0, dynarray_get(pq -> heap, dynarray_length(pq -> heap) - 1));
  dynarray_remove(pq -> heap, dynarray_length(pq -> heap) - 1);
  //Then we can percolate down yippee yahoo ha ha ho ho
  percolatedown(pq -> heap);
  return temp;
}
