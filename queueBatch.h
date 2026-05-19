#ifndef QUEUE_H
#define QUEUE_H
#define NULL_OFFSET -1

#include "arena.h"

typedef struct Queue {
    int front;
    int rear;
} Queue;

typedef struct printJob {
    int id;
    char document[32];
    int next;
} printJob;

void queue_init(Queue *queue);
int queue_create(Arena *arena);
int create_job(Arena *arena, int jobId, const char *documentName);
void search_job(Arena *arena, Queue *queue, int targetId);
void enqueue(Arena *arena, Queue *queue, int jobOffset);
void dequeue(Arena *arena, Queue *queue);
void display_queue(Arena *arena, Queue *queue);
void process_batch(Arena *arena, Queue *queue, int batchSize);

#endif