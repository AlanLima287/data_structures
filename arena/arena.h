#pragma once

#ifndef __ARENA_H__
#define __ARENA_H__

// Alan Lima (https://github.com/AlanLima287/data_structures/tree/main/arena)
// Arena - 0.0.2

#include <stdbool.h>
#include <stdint.h>

#ifndef __arena_region_capacity
#define __arena_region_capacity 0x1000ull
#endif

struct Region {
   struct Region* next;

   size_t allocated;
   size_t capacity;

   uint8_t buffer[];
};

typedef struct {
   struct Region* head;
   struct Region* tail;
} Arena;

// typedef void* ArenaCheckpoint;

Arena arena_create();
void arena_free(Arena*);

// ArenaCheckpoint arena_create_checkpoint(Arena*);
// void arena_free_checkpoint(Arena*, ArenaCheckpoint);

void* arena_alloc(Arena*, size_t);
void* arena_alloc_aligned(Arena*, size_t, size_t);

void arena_align(Arena*, size_t);
size_t arena_available_space(Arena*);

#endif