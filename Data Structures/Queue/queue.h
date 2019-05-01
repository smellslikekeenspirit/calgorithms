/** filename: queue.h
**  definition for a queue that can store any type of data 
**  author: Prionti Nasir, pdn3628@rit.edu
**/


typedef struct Node{
	void *contents;
  	struct Node *next;
}Node;


typedef struct Queue{ 
	Node *back;
	Node *front;
	int size;
}Queue;

///enqueues data to the back of the queue
void enqueue(Queue *, void *);

///dequeues and returns data at the front of the queue
///returns NULL if queue is empty
void *dequeue(Queue *);


///destroys the queue by dequeueing all elements and freeing the queue 
void destroyQueue(Queue *);

///create and return a pointer to an empty queue
Queue *createQueue();

///computes the amount of items in the queue
int queueSize(Queue *);

