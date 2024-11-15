#ifndef _priorityQueueDepartment_h
#define _priorityQueueDepartment_h
#include <stdlib.h>
#include <stdbool.h>

#include "department.h"

typedef Department* priorityQueueType;

typedef struct PQNode {
  priorityQueueType qt;  // priorityQueueType contained in this node
  int priority;          // priority of node contained in this node
  struct PQNode *pNext;  // pointer to the next node in the linked list
} PQNode;

typedef struct PriorityQueue {
  PQNode *qFront;  // pointer to the first element of the queue
  PQNode *qRear;   // pointer to the last element of the queue
} PriorityQueue;

void printPriorityQueue(PriorityQueue *pq);

PriorityQueue *createPQ();
void freePQ(PriorityQueue *pq);

int getFrontPriority(PriorityQueue *pq);
priorityQueueType getNextPQ(PriorityQueue *pq);
priorityQueueType dequeuePQ(PriorityQueue *pq);
void enqueueByPriority(PriorityQueue *pq, priorityQueueType qt, int priority);

bool isEmptyPQ(PriorityQueue *pq);

int sizeOfPriorityQueue(PriorityQueue *pq);

#endif
