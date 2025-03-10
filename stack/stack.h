#pragma once

#ifndef __STACK_H__
#define __STACK_H__

// Alan Lima - https://github.com/AlanLima287/data_structures/tree/main/stack
// Stack - 0.0.1

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define stack_default(prefix) \
   typedef __Stack Stack; \
   static inline bool prefix ## _init(Stack* stack, size_t size) { return __stack_init(stack, size); } \
   static inline bool prefix ## _reserve(Stack* stack, size_t size) { return __stack_reserve(stack, size); } \
   static inline bool prefix ## _reserve_exact(Stack* stack, size_t size) { return __stack_reserve_exact(stack, size); } \
   static inline void prefix ## _clear(Stack* stack) { __stack_clear(stack); } \
   static inline void prefix ## _free(Stack* stack) { __stack_free(stack); } \
   static inline size_t prefix ## _size(Stack* stack) { return __stack_size(stack); } \
   static inline void* prefix ## _push(Stack* stack, size_t size) { return __stack_push(stack, size); } \
   static inline void* prefix ## _peek(Stack* stack, size_t size) { return __stack_peek(stack, size); } \
   static inline void* prefix ## _pop(Stack* stack, size_t size) { return __stack_pop(stack, size); } \
   static inline void* prefix ## _disown(Stack* stack) { return __stack_disown(stack); }

#define stack_typedef(decl, type, prefix) \
   typedef __Stack decl; \
   static inline bool prefix ## _init(decl* stack, size_t n) { return __stack_init(stack, n * sizeof(type)); } \
   static inline bool prefix ## _reserve(decl* stack, size_t n) { return __stack_reserve(stack, n * sizeof(type)); } \
   static inline bool prefix ## _reserve_exact(decl* stack, size_t n) { return __stack_reserve_exact(stack, n * sizeof(type)); } \
   static inline void prefix ## _clear(decl* stack) { __stack_clear(stack); } \
   static inline void prefix ## _free(decl* stack) { __stack_free(stack); } \
   static inline size_t prefix ## _size(decl* stack) { return __stack_size(stack) / sizeof(type); } \
   static inline type* prefix ## _frame(decl* stack) { return (type*)__stack_frame(stack); } \
   static inline type* prefix ## _push(decl* stack, size_t n) { return (type*)__stack_push(stack, n * sizeof(type)); } \
   static inline type* prefix ## _peek(decl* stack, size_t n) { return (type*)__stack_peek(stack, n * sizeof(type)); } \
   static inline type* prefix ## _pop(decl* stack, size_t n) { return (type*)__stack_pop(stack, n * sizeof(type)); } \
   static inline type* prefix ## _disown(decl* stack) { return (type*)__stack_disown(stack); }

typedef struct __Stack {
   void* frame;
   size_t capacity;
   size_t top;
} __Stack;

#ifndef __stack_min_allocation_size
   #define __stack_min_allocation_size 16ull
#endif

#ifndef __stack_scalling_function
   #define __stack_scalling_function(x) (x + (x << 1))
#endif

/* Initializes the stack.
 * @param  stack: a pointer to a stack structure
 * @param  size:  the amount of bytes to be preallocated, if < `__stack_min_allocation_size`, then `__stack_min_allocation_size` bytes will be allocated
 * @return        returns `true` on success, `false` otherwise
 */
bool __stack_init(__Stack* stack, size_t size);

/* Reverse space for new elements at the top of the stack
 * @param  stack: a pointer to a stack structure
 * @param  size:  at least the amount of bytes to be reserved for the stack
 * @return        returns `true` on success, `false` otherwise
 */
bool __stack_reserve(__Stack* stack, size_t size);

/* Reverse space for exacly `size` new elements at the top of the stack
 * @param  stack: a pointer to a stack structure
 * @param  size:  the amount of bytes to be reserved for the stack
 * @return        returns `true` on success, `false` otherwise
 */
bool __stack_reserve_exact(__Stack* stack, size_t size);

/* Clears the stack, by setting the top back to zero.
 * @param  stack: a pointer to a stack structure
 */
static inline void __stack_clear(__Stack* stack) {
   stack->top = 0;
}

/* Releases the stack pointer, actions on the stack from here on are undefined.
 * @param  stack: a pointer to a stack structure
 */
static inline void __stack_free(__Stack* stack) {
   free(stack->frame);
}

/* Returns the size (top) of the stack
 * @param  stack: a pointer to a stack structure
 * @return        returns the size of the stack in bytes
 */
static inline size_t __stack_size(__Stack* stack) {
   return stack->top;
}

/* Returns the size (top) of the stack
 * @param  stack: a pointer to a stack structure
 * @return        returns a pointer to the stack
 */
static inline void* __stack_frame(__Stack* stack) {
   return stack->frame;
}

/* Pushes a new area at the top of the stack
 * @param  stack: a pointer to a stack structure
 * @param  size:  the amount of bytes to be allocated on the stack
 * @return        returns a pointer to the start of the pushed area
 */
void* __stack_push(__Stack* stack, size_t size);

/* Peeks at the top of the stack
 * @param  stack: a pointer to a stack structure
 * @param  size:  the amount of bytes to be peeked on the stack
 * @return        returns a pointer to the area at the top of the stack
 */
void* __stack_peek(__Stack* stack, size_t size);

/* Pops off the top of the stack
 * @param  stack: a pointer to a stack structure
 * @param  size:  the amount of bytes to be deallocated on the stack
 * @return        returns a pointer to the area at the top of the stack
 */
void* __stack_pop(__Stack* stack, size_t size);

/* Shrinks the frame to its minimal possible length and returns the frame
 * @param  stack: a pointer to a stack structure
 * @return        returns a pointer to the stack
 *
 * @warning once its called, the stack structure is no longer valid
 * @warning caller is responsible for freeing the returned pointer
 */
void* __stack_disown(__Stack* stack);

#ifdef IMPLEMENT
   #include "stack.c"
#endif

#endif