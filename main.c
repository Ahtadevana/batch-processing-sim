#include <stdio.h>
#include "arena.h"

int main()  {
    Arena mainArena = arenaInit(256);
    arenaPrint(&mainArena);

    arenaAlloc(&mainArena, 128);
    arenaPrint(&mainArena);

    char *convertedPtr = arenaGet(&mainArena, 64);
    printf("\nArena get result test: %p\n", convertedPtr);  //test get

    arenaReset(&mainArena);
    arenaPrint(&mainArena);

    arenaFree(&mainArena);

    return 0;
}