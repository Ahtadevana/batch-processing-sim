#ifndef ARENA_H
#define ARENA_H

#include <stdio.h>

typedef struct Arena {
    char *base;
    size_t totalSize;
    size_t offset;  //could be int or size_t
} Arena;

Arena arena_init(size_t arenaSize);

char* arena_alloc(Arena *arena, size_t allocSize);
char* arena_get(Arena *arena, size_t offset);    //convert offset->ptr
void arena_reset(Arena *arena);

void arena_print(Arena *arena);  //per 2 bytes visuallization
void arena_free(Arena *arena);

#endif