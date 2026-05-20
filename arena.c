#include <stdio.h>
#include <stdlib.h>

#include "arena.h"

/*
Arena arena_init(size_t arenaSize);
char* arena_alloc(Arena *arena, size_t allocSize);
char* arena_get(Arena *arena, size_t offset);
void arena_reset(Arena *arena);
void arena_print(Arena *arena);
void arena_free(Arena *arena);
*/

Arena arena_init(size_t arenaSize) {
    char *memoryBlock = (char*)malloc(arenaSize);
    if(!memoryBlock){
        printf("arenaInit: Allocation Failed. Exiting . . .\n");
        exit(1);
    }

    Arena newArena;
    newArena.base = memoryBlock;
    newArena.totalSize = arenaSize;
    newArena.offset = 0;

    return newArena;
}

char* arena_alloc(Arena *arena, size_t allocSize) {
    if(arena->base == NULL){
        printf("arenaAlloc: Arena uninitiallized.\n");
        return NULL;
    }

    if(arena->offset + allocSize > arena->totalSize){
        printf("arenaAlloc: Allocation request too big.\n");
        return NULL;
    }

    char *newPtr = arena->base + arena->offset;
    arena->offset += allocSize;

    return newPtr;
}

char* arena_get(Arena *arena, size_t offset) {
    if(offset > arena->offset){
        printf("arenaGet: Requested offset outside allocated space. Exiting . . .\n");
        exit(1);
    }

    char *offsetPtr = arena->base + offset; //convert
    return offsetPtr;
}

void arena_reset(Arena *arena) {
    arena->offset = 0;
}

void arena_print(Arena *arena) {
    size_t blocks = arena->totalSize / 2; //making it per 2 bytes per square.

    printf("\n===\nTotal Size: %zu\n", arena->totalSize);
    printf("Bytes Used: %zu\n", arena->offset);
    printf("Current Offset Addr: %p\n", arena_get(arena, arena->offset));
    printf("Legend:\n[##]: Used\n[..]: Empty\n===\n");

    for(size_t i=0; i < blocks; i++){
        if(i * 2 < arena->offset){  //before offset
            printf("[##]");
        } else {
            printf("[..]");
        }

        if((i+1) % 16 == 0){    //per 16 blocks inline
            printf("\n");
        }
    }

    if(blocks % 16 != 0){
        printf("\n");
    }
}

void arena_free(Arena *arena) {
    if(arena->base == NULL){
        printf("arenaFree: Arena uninitiallized.\n");
        return;
    }

    free(arena->base);
    arena->base = NULL;

    arena_reset(arena);
    arena->totalSize = 0;
}