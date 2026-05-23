#include <stdio.h>
#include "arena.h"
#include "queueBatch.h"

/*
Arena arena_init(size_t arenaSize);
char* arena_alloc(Arena *arena, size_t allocSize);
char* arena_get(Arena *arena, size_t offset);
void arena_reset(Arena *arena);
void arena_print(Arena *arena);
void arena_free(Arena *arena);

void queue_init(Queue *queue);
int queue_create(Arena *arena);
int create_job(Arena *arena, int jobId, const char *documentName);
void search_job(Arena *arena, Queue *queue, int targetId);
void enqueue(Arena *arena, Queue *queue, int jobOffset);
void dequeue(Arena *arena, Queue *queue);
void display_queue(Arena *arena, Queue *queue);
void process_batch(Arena *arena, Queue *queue, int batchSize);
*/

int main()  {
    interactive();
    return 0;
}