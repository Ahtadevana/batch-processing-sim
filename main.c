#include <stdio.h>
#include "arena.h"

int main()  {
    Arena mainArena = arena_init(256);
    arena_print(&mainArena);

    arena_alloc(&mainArena, 128);
    arena_print(&mainArena);

    char *convertedPtr = arena_get(&mainArena, 64);
    printf("\nArena get result test: %p\n", convertedPtr);  //test get

    arena_reset(&mainArena);
    arena_print(&mainArena);

    arena_free(&mainArena);

    return 0;
}