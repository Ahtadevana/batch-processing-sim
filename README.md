# Print Job Batch Processor Simulation
A memory efficient print job management system that simulates printer queue using a custom arena allocator made by me! This project demonstrates low-level memory management and taking an advantage of the use of offsets within the arena.

## My Arena Allocator
A custom memory allocator that pre-allocates a memory block within that arena using arena APIs. Because i've made them:
- O(1) resetting using arena_reset(),
- All of its contents are linear/contiguous, so way more faster with spatial caching,
- Arena visualization per 2 bytes that spans around 32 bytes per line.

## The Queue Manager
A linked list based queue using offsets to navigate arena easier. I've made them:
- Offset based addressing as explained above,
- Job searching is O(n) since i didn't know much about data structures yet and linked list is my current best friend,
- Queue visualization that displays its id and document name.

## Features I Added
Just some of the extra unneeded features that i made for learning purposes:
- Interactive CLI menu,
- Dynamic arena sizing at runtime,
- Job management,
- Arena and queue visualization like mentioned above.

## Data Structures Used
An arena structure for containing its metadatas:
```
typedef struct Arena {
    char *base;        // Arena main pointer (WONT CHANGE)
    size_t totalSize;  // Total size of arena in bytes
    size_t offset;     // Current allocation position
} Arena;
```
A linked list based queue:
```
typedef struct Queue {
    int front;    // Offset to first job
    int rear;     // Offset to last job  
} Queue;

```

## Stuff I Use
- IDE: Visual Studio Code
- Compiler: gcc.exe (x86_64-posix-seh-rev0, Built by MinGW-Builds project) 15.2.
- C standard: c23 - `#define __STDC_VERSION__ 202311L`
- Build: No build systems

## Notes From Xervii
I just wanna say first, excuse my bad english in making these readmes. I have my own limitations. This project have teach me a lot. A lot about memory management, basic low level stuff, and hours of debugging skills. Licensing? I don't care about licensing. Feel free to steal it since this is a relatively small project and everyone can make them. But do ur best to credit! I'd luv dat. 

Thanks for reading, and toodles!
