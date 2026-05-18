#include <stdio.h>
#include <stdlib.h>

#include "arena.h"

Arena arenaInit(size_t arenaSize)   {
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

char* arenaAlloc(Arena *arena, size_t allocSize)    {
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