#include <stdio.h>
#include <string.h>

#include "arena.h"
#include "queueBatch.h"

/*
void queue_init(Queue *queue);
int queue_create(Arena *arena);
int create_job(Arena *arena, int jobId, const char *documentName);
void search_job(Arena *arena, Queue *queue, int targetId);
void enqueue(Arena *arena, Queue *queue, int jobOffset);
void dequeue(Arena *arena, Queue *queue);
void display_queue(Arena *arena, Queue *queue);
void process_batch(Arena *arena, Queue *queue, int batchSize);
*/

void queue_init(Queue *queue) {
    queue->front = NULL_OFFSET;
    queue->rear = NULL_OFFSET;
}

int queue_create(Arena *arena) {
    Queue *queue = (Queue*)arena_alloc(arena, sizeof(Queue));
    if(queue == NULL){
        return NULL_OFFSET;
    }

    queue_init(queue);
    int queueOffset = (char*)queue - arena->base; //queue offset from base
    return queueOffset;
}

int create_job(Arena *arena, int jobId, const char *documentName) {
    PrintJob *newJob = (PrintJob*)arena_alloc(arena, sizeof(PrintJob));
    if(newJob == NULL){
        return NULL_OFFSET;
    }

    newJob->id = jobId;
    strncpy(newJob->document, documentName, 31);
    newJob->document[31] = '\0';

    newJob->next = NULL_OFFSET;
    int newJobOffset = (char*)newJob - arena->base;   //job offset from base

    return newJobOffset;
}