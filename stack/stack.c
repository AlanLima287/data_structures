#include <stdlib.h>
#include "stack.h"

extern bool __stack_init(__Stack* stack, size_t size) {
   stack->top = 0;
   stack->capacity = size < __stack_min_allocation_size
      ? __stack_min_allocation_size
      : size;

   stack->frame = malloc(stack->capacity);
   return stack->frame != NULL;
}

extern bool __stack_reserve(__Stack* stack, size_t size) {
   if (stack->top + size <= stack->capacity) return true;

   do stack->capacity = __stack_scalling_function(stack->capacity);
   while (stack->capacity < size + stack->top);

   void* new_pointer = realloc(stack->frame, stack->capacity);
   if (new_pointer == NULL) return false;

   stack->frame = new_pointer;
   return true;
}

extern bool __stack_reserve_exact(__Stack* stack, size_t size) {
   if (stack->top + size <= stack->capacity) return true;

   stack->capacity = stack->top + size;
   void* new_pointer = realloc(stack->frame, stack->capacity);
   if (new_pointer == NULL) return false;

   stack->frame = new_pointer;
   return true;
}

extern void* __stack_push(__Stack* stack, size_t size) {
   if (stack->capacity < stack->top + size) __stack_reserve(stack, size);

   void* pointer = (void*)((uintptr_t)stack->frame + stack->top);
   stack->top += size;

   return pointer;
}

extern void* __stack_peek(__Stack* stack, size_t size) {
   return stack->top < size ? NULL : (void*)((uintptr_t)stack->frame + stack->top - size);
}

extern void* __stack_pop(__Stack* stack, size_t size) {
   if (stack->top < size) return NULL;

   stack->top -= size;
   return (void*)((uintptr_t)stack->frame + stack->top);
}

extern void* __stack_disown(__Stack* stack) {
   void* pointer = realloc(stack->frame, stack->top);
   if (pointer == NULL) return NULL;

   stack->frame = NULL;
   return pointer;
}