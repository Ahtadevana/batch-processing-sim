#ifndef ARENA_H
#define ARENA_H

#include <stdio.h>

typedef struct Arena {
    char *base;
    size_t totalSize;
    size_t offset;
} Arena;

Arena arenaInit(size_t arenaSize);

char* arenaAlloc(Arena *arena, size_t allocSize);
char* arenaGet(Arena *arena, size_t offset);    //convert offset->ptr
void arenaReset(Arena *arena);

void arenaPrint(Arena *arena);
void arenaFree(Arena *arena);

#endif