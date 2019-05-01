/** queue.c
**  implements queue using definitions in queue.h
**  author: Prionti Nasir pdn3628@rit.edu
**/


#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


///creates an empty queue and returns a pointer
Queue *createQueue(){
  Queue *queue = malloc(sizeof(Queue));
  queue->front = NULL;
  queue->back = NULL;
  queue->size = 0;
  return queue;
}

Node *createNode(void *contents){
	Node *node = malloc(sizeof(Node));
	node->contents = contents;
	node->next = NULL;
	return node;
}

void enqueue(Queue *queue, void *contents){
	Node *node = createNode(contents);
	if (queue->size == 0){
		queue->front = node;
		queue->back = node;
	}
  	else{
		queue->back->next = node;
		queue->back = node;
	}

	queue->size++;
}


void *dequeue(Queue *queue){
	Node *node = queue->front;
	if (queue->size == 0) return NULL;
	queue->front = queue->front->next;
        void *contents = node->contents;
	if(queue->size == 1){
		queue->back = NULL;
		queue->front = NULL;
    	}
	queue->size--;
	free(node);
	return contents;
}


void destroyQueue(Queue *queue){
	while(queue->size != 0){
		dequeue(queue);
  	}
	free(queue);
}

int queueSize(Queue * queue){
	return queue->size;
}

