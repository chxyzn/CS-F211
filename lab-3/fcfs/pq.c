#include "process_queue.h"
#include <stdlib.h>
#define Q_SIZE 1000

struct Queue
{
    int front;
    int rear;
    Process data[Q_SIZE];
};

Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL)
        return NULL;

    q->front = 0;
    q->rear = 0;

    return q;
}

bool enqueue(Queue *queue, Process element)
{
    if (size(queue) == Q_SIZE - 1)
        return false;

    queue->data[queue->rear] = element;
    queue->rear = (queue->rear + 1) % Q_SIZE;

    return true;
}

bool dequeue(Queue *queue)
{
    if (!size(queue))
        return false;

    queue->front = (queue->front + 1) % Q_SIZE;
    return true;
}

Process *front(Queue *queue)
{
    if (!size(queue))
        return NULL;

    return &(queue->data[queue->front]);
}

bool isEmpty(Queue *queue)
{
    return !size(queue);
}

int size(Queue *queue)
{
    return (queue->rear - queue->front + Q_SIZE) % Q_SIZE;
}

void destroyQueue(Queue *queue)
{
    free(queue);
}