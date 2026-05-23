#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "arena.h"
#include "queueBatch.h"

/*
void queue_init(Queue *queue);
int queue_create(Arena *arena);
int create_job(Arena *arena, int jobId, const char *documentName);
void search_job(Arena *arena, Queue queue, int targetId);

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

void search_job(Arena *arena, Queue queue, int targetId) {
    if(arena->base == NULL){
        return;
    }

    if(queue.front == NULL_OFFSET){
        return;
    }

    int current = queue.front;
    bool isExist = false;

    while(current != NULL_OFFSET){
        PrintJob *currJob = (PrintJob*)arena_get(arena, current);

        if(currJob->id == targetId){
            printf("Job found.\n");
            printf("Job ID: %d | Name: %s\n", currJob->id, currJob->document);
            
            isExist = true;
            break;
        }

        current = currJob->next;
    }

    if(!isExist){
        printf("Job %d is not found.\n", targetId);
    }    
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

void display_queue(Arena *arena, Queue queue) {
    if(arena->base == NULL){
        printf("displayQueue: Arena is uninitiallized.\n");
        return;
    }

    if(queue.front == NULL_OFFSET){
        printf("displayQueue: Queue is empty.\n");
        return;
    }

    int current = queue.front;

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

void interactive() {
    Arena arena = arena_init(0);
    Queue *queue = NULL;

    bool isRunning = true;

    while(isRunning){
        int option = -1;

        printf("===Batch Processor===\n");
        printf("1. Init arena\n");
        printf("2. Init queue\n");
        printf("3. Add print job\n");
        printf("4. Process batch\n");
        printf("5. Search job by ID\n");
        printf("6. Print queue\n");
        printf("7. Print arena\n");
        printf("8. Reset arena\n");
        printf("9. Free arena\n");
        printf("0. Exit Program\n");

        printf("Option: ");
        scanf("%d", &option);

        switch(option){
            case 1: {
                size_t arenaSize;

                printf("Arena size:");
                scanf("%zu", &arenaSize);

                arena = arena_init(arenaSize);

                printf("1: Arena initiallized.\n");
                break;
            }
            
            case 2: {
                if(arena.totalSize == 0){
                    printf("2: Arena size uninitiallized.\n");
                    break;
                }

                int queueOffset = queue_create(&arena);
                if(queueOffset != NULL_OFFSET){
                    queue = (Queue*)arena_get(&arena, queueOffset);
                    printf("2: Queue initiallized.\n");
                }

                break;
            }

            case 3: {
                if(queue == NULL){
                    printf("3: Queue is uninitiallized.\n");
                    break;
                }

                int id;
                char document[32];

                printf("ID job:");
                scanf("%d, &id");

                getchar();

                printf("Nama dokumen: ");
                fgets(document, sizeof(document), stdin);

                document[strcspn(document, "\n")] = '\0';

                int jobOffset = create_job(&arena, id, document);
                if(jobOffset != NULL_OFFSET){
                    enqueue(&arena, queue, jobOffset);
                    printf("3: Job added.\n");
                }

                break;
            }

            case 4: {
                if(queue == NULL){
                    printf("4: Queue is uninitiallized.\n");
                    break;
                }

                if(queue->front == NULL_OFFSET){
                    printf("4: Queue is empty.\n");
                    break;
                }
                
                int batch;

                printf("Batch amount: ");
                scanf("%d", &batch);

                process_batch(&arena, queue, batch);
                break;
            }

            case 5: {
                if(queue == NULL){
                    printf("5: Queue is uninitiallized.\n");
                    break;
                }

                if(queue->front == NULL_OFFSET){
                    printf("5: Queue is empty.\n");
                    break;
                }

                int targetId;

                printf("Enter job ID: ");
                scanf("%d", &targetId);

                search_job(&arena, *queue, targetId);
                break;
            }

            case 6: {
                if(queue == NULL){
                    printf("6: Queue is uninitiallized.\n");
                    break;
                }
                if(queue->front == NULL_OFFSET){
                    printf("5: Queue is empty.\n");
                    break;
                }

                display_queue(&arena, *queue);
                break;
            }

            case 7: {
                if(arena.base == NULL){
                    printf("7: Arena is uninitiallized.\n");
                    break;
                }
                
                if(arena.totalSize == 0){
                    printf("[0]\n");
                    break;
                }

                arena_print(&arena);
                break;
            }

            case 8: {
                if(arena.offset == 0){
                    printf("8: Arena is already empty.\n");
                    break;
                }
                
                arena_reset(&arena);
                queue = NULL;

                printf("8: Arena is emptied.\n");
                break;
            }

            case 9: {
                if(arena.base == NULL || arena.totalSize == 0){
                    printf("9: Arena is already NULL.\n");
                    break;
                }

                arena_free(&arena);
                queue = NULL;

                printf("9: Arena is freed.\n");
                break;
            }

            case 0: {
                isRunning = false;
                break;
            }

            default: {
                printf("Error: Invalid option.\n");
            }
        }
    }

    printf("Program terminated.\n");
    return;
}