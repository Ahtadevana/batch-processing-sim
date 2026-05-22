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
int dequeue(Arena *arena, Queue *queue);

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

void enqueue(Arena *arena, Queue *queue, int jobOffset) {
    if(queue->rear == NULL_OFFSET){
        queue->front = jobOffset;
        queue->rear = jobOffset;
        return;
    }

    PrintJob *newJob = (PrintJob*)arena_get(arena, queue->rear);

    newJob->next = jobOffset;
    queue->rear = jobOffset;
}

int dequeue(Arena *arena, Queue *queue) {
    if(queue->front == NULL_OFFSET){
        printf("Queue is empty.\n");
        return NULL_OFFSET;
    }

    int removedOffset = queue->front;

    PrintJob *frontJob = (PrintJob*)arena_get(arena, queue->front);
    queue->front = frontJob->next;
    
    if(queue->front == NULL_OFFSET){
        queue->rear = NULL_OFFSET;
    }

    return removedOffset;
}

void display_queue(Arena *arena, Queue *queue) {
    if(arena->base == NULL){
        printf("displayQueue: Arena is uninitiallized.\n");
        return;
    }

    if(queue->front == NULL_OFFSET){
        printf("displayQueue: Queue is empty.\n");
        return;
    }

    int current = queue->front;

    printf("===Queue Jobs===\n");
    while(current != NULL_OFFSET){
        PrintJob *job = (PrintJob*)arena_get(arena, current);

        printf("Job ID: %d | Name: %s\n", job->id, job->document);
        current = job->next;
    }

    printf("================\n");
}

void process_batch(Arena *arena, Queue *queue, int batchSize) {
    printf("===Process Batch===\n");

    for(int i=0; i < batchSize; i++){
        int jobOffset = dequeue(arena, queue);
        if(jobOffset == NULL_OFFSET){
            break;
        }

        PrintJob *job = (PrintJob*)arena_get(arena, jobOffset);

        printf("Processing job ID: %d | Name: %s . . .\n", job->id, job->document);
    }

    printf("===================\n");
}