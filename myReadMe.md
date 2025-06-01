Priority queue structure:
  My implementation of a priority queue consists solely of a dynamic array heap to store the node structures I made (pqnode) that each have an int priority and a void* value

pq_free():
  This function just frees the heap with dynarray_free() and then frees the priority queue itself

pq_isempty():
  This function returns whether dynarray_length(pq -> heap) is zero or not to determine whether the priority queue is empty

dynarray_swap():
  I implemented this to efficiently swap two elements in the dynamic array for the priority queue

percolatedown():
  This loops through the heap, swapping the current node with its highest-priority child node if it has lower priority than either of the child nodes.  The loop ends when the
  current node has a higher priority than any child nodes it has or when the current node is a leaf.

pq_insert():
  This inserts the new node at the end of the array, percolating up as needed by comparing the new node's priority with the priority of its parent node until the heap property
  is satisfied

pq_max returns the value from the front of the priority queue, and pq_max_priority returns its priority

pq_max_dequeue():
  This removes the front element fro mthe priority queue (the first one in the dynamic array heap) and then checks if the heap is now empty or consisting of only one element.
  If these are the case, the function just immediately returns the value that was dequeued.  If not, it moves the very last item in the dynamic array to the front and then
  percolates down to restore the heap property.
