#include "priorityQueueDepartment.h"

#define LINUX_PRINT_COLOR false /* JESS: Set this to true to make your debug outputs more visible on the lab machines */

/* printPriorityQueue
 * input: a pointer to a PriorityQueue
 * output: none
 *
 * Prints the elements in the PriorityQueue.
 */
void printPriorityQueue(PriorityQueue *pq) {
  if( LINUX_PRINT_COLOR )
    printf("\033[0;31m");

  PQNode *curr;
  if (pq == NULL)
    printf("Priority Queue pointer is NULL\n");

  else if (pq->qFront == NULL) 
    printf("Priority Queue is empty\n");

  else{
    printf("Priority Queue of events:\n");
    curr = pq->qFront;
    while (curr != NULL) {
      printDepartment(curr->qt);
      curr = curr->pNext;
    }
  }
  

  if( LINUX_PRINT_COLOR )
    printf("\033[0m");
}

/* createPQ
 * input: none
 * output: a pointer to a queue (this is malloc-ed so must be freed eventually!)
 *
 * Creates a new empty queue and returns a pointer to it.
 */
PriorityQueue *createPQ() {
  PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
  if (pq != NULL) {
    pq->qFront = NULL;
    pq->qRear = NULL;
  }

  return pq;
}

/* freePQ
 * input: a pointer to a PriorityQueue
 * output: none
 *
 * frees the given PriorityQueue pointer.  Also, you should remember to remove and free the
 * elements in the linked list first!
 */
void freePQ(PriorityQueue *pq) { 
	free(pq); 
}

/* getFrontPriority
 * input: a pointer to a PriorityQueue
 * output: the priority of the front element
 *
 * Returns the priority of the front of the PriorityQueue.  It does not remove
 * the element from the PriorityQueue.
 */
int getFrontPriority(PriorityQueue *pq) {
  if (isEmptyPQ(pq)) {
    /* no element to return */
    fprintf(stderr,
            "ERROR - getFrontPriority: attempt to get priority of empty "
            "priority queue.\n");
    return -1;
  }
  return pq->qFront->priority;
}

/* getNextPQ
 * input: a pointer to a PriorityQueue
 * output: a pointer to process
 *
 * Returns the process stored at the front of the PriorityQueue.  It does not
 * remove the element from the PriorityQueue.
 */
priorityQueueType getNextPQ(PriorityQueue *pq) {
  if (isEmptyPQ(pq)) {
    /* no element to return */
    return NULL;
  }
  return pq->qFront->qt;
}

/* dequeuePQ
 * input: a pointer to a PriorityQueue
 * output: a pointer to process
 *
 * Dequeues and returns the process stored at the front of the PriorityQueue. It
 * does not free the dequeue-ed element.
 */
priorityQueueType dequeuePQ(PriorityQueue *pq) {
  PQNode *temp;
  priorityQueueType qt;

  if (isEmptyPQ(pq)) {
    /* no element to return */
    return NULL;
  }
  temp = pq->qFront;
  pq->qFront = pq->qFront->pNext;
  if (pq->qFront == NULL) {
    pq->qRear = NULL;
  }
  qt = temp->qt;
  free(temp);

  return qt;
}

/* enqueueByPriority
 * input: a pointer to a PriorityQueue, a priorityQueueType
 * output: none
 *
 * Inserts the process based on its priority.
 */
void enqueueByPriority(PriorityQueue *pq, priorityQueueType qt, int priority) {
  PQNode *curr;
  PQNode *node = (PQNode *)malloc(sizeof(PQNode));
  if (node == NULL) {
    fprintf(stderr,
            "ERROR - enqueueByPriority: Failed to allocate memory\n");
    exit(-1);
  }

  node->pNext = NULL;
  node->qt = qt;
  node->priority = priority;

  // Insert in empty list
  if (isEmptyPQ(pq)) {
    pq->qFront = node;
    pq->qRear = node;
    return;
  }

  // Insert at front
  if (node->priority < pq->qFront->priority) {
    node->pNext = pq->qFront;
    pq->qFront = node;
    return;
  }

  curr = pq->qFront;
  while (curr->pNext != NULL && curr->pNext->priority <= node->priority) {
    curr = curr->pNext;
  }

  // Insert after curr
  node->pNext = curr->pNext;
  curr->pNext = node;
}

/* isEmptyPQ
 * input: a pointer to a PriorityQueue
 * output: a boolean
 *
 * returns TRUE if the PriorityQueue is empty and FALSE otherwise
 */
bool isEmptyPQ(PriorityQueue *pq) {
  if (pq->qFront == NULL && pq->qRear == NULL) {
    return true;
  } else if (pq->qFront == NULL || pq->qRear == NULL) {
    fprintf(stderr,
            "ERROR - isEmptyPQ: PriorityQueue had inconsistent values for "
            "front and rear.\n");
    exit(-1);
  }
  return false;
}

/* sizeOfPriorityQueue
 * input: a pointer to a PriorityQueue
 * output: int
 *
 * Returns the number of elements in the PriorityQueue.
 */
int sizeOfPriorityQueue(PriorityQueue *pq) {
	int cnt = 0;
  PQNode *curr;
  curr = pq->qFront;
  
	while (curr != NULL) {
		cnt++;
		curr = curr->pNext;
	}
  
  return cnt;
}
