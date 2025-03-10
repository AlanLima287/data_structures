#include <stdlib.h>
#include "arena.h"

static struct Region* __arena_new_region(size_t);
static void __arena_free_region(struct Region*);

extern Arena arena_create() {
   return (Arena) { .head = NULL, .tail = NULL };
}

extern void arena_free(Arena* arena) {
   struct Region* curr = arena->head;

   while (curr) {
      struct Region* tmp = curr->next;
      __arena_free_region(curr);
      curr = tmp;
   }

   arena->head = NULL;
   arena->tail = NULL;
}

// ArenaCheckpoint arena_create_checkpoint(Arena* arena) { return NULL; }
// void arena_free_checkpoint(Arena* arena, ArenaCheckpoint checkpoint) {}

static struct Region* __arena_new_region(size_t capacity) {
   capacity = capacity == 0
      ? __arena_region_capacity
      : (capacity + (__arena_region_capacity - 1)) & -__arena_region_capacity;

   struct Region* region = (struct Region*)malloc(sizeof(struct Region) + capacity);
   if (region == NULL) return NULL;

   region->capacity = capacity;
   region->allocated = 0;
   region->next = NULL;

   return region;
}

static void __arena_free_region(struct Region* region) {
   free(region);
}

extern void* arena_alloc(Arena* arena, size_t size) {
   if (arena->head == NULL) {
      arena->head = __arena_new_region(size);
      if (arena->head == NULL) return NULL;
      arena->tail = arena->head;
   }

   struct Region* tail = arena->tail;

   if (tail->allocated + size >= tail->capacity) {
      if (tail->next == NULL) {
         tail->next = __arena_new_region(size);
         if (tail->next == NULL) return NULL;
      }

      tail = tail->next;
   }

   void* pointer = (void*)((uintptr_t)tail->buffer + (uintptr_t)tail->allocated);
   tail->allocated += size;

   return pointer;
}

extern void* arena_alloc_aligned(Arena* arena, size_t size, size_t alignment) {
   if (arena->head == NULL) {
      arena->head = __arena_new_region(size);
      if (arena->head == NULL) return NULL;
      arena->tail = arena->head;
   }

   struct Region* tail = arena->tail;
   size_t pos_w_padding = ((tail->allocated + alignment - 1) & -alignment) - tail->allocated;

   if (pos_w_padding + size >= tail->capacity) {
      tail->next = __arena_new_region(size);

      tail->allocated = size;
      return (void*)tail->next->buffer;
   }

   tail->allocated = pos_w_padding + size;
   return (void*)((uintptr_t)tail->buffer + (uintptr_t)pos_w_padding);
}

extern void arena_align(Arena* arena, size_t alignment) {
   if (arena->head == NULL) return;
   arena->tail->allocated = (arena->tail->allocated + alignment - 1) & -alignment;
}

extern size_t arena_available_space(Arena* arena) {
   if (arena->head == NULL) return 0;
   return arena->tail->capacity - arena->tail->allocated;
}