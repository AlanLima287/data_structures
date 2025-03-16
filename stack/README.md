# Stack

Stack is an _abstract data structure_ that is a collection of object of some kind. The Stack has two main operations defined over it:

* push: An object is added to the top of the collection; and
* pop: An object is remove from the top of the stack and gives back that object.

Other operation may be defined in a stack, however these are the main ones.

> [!WARNING]
> This is an ongoing project!

# Table of Content

- [Implementation](#implementation)
   - [Structure](#structure)
   - [Macros](#macros)
      - [`stack_default`](#stack_default)
      - [`stack_typedef`](#stack_typedef)
      - [`__stack_min_allocation_size`](#__stack_min_allocation_size)
      - [`__stack_scalling_function`](#__stack_scalling_function)
   - [Functions](#functions)
      - [Initialization function `__stack_init`](#initialization-function-__stack_init)
      - [Reserve function `__stack_reserve`](#reserve-function-__stack_reserve)
      - [Reserve exact function `__stack_reserve_exact`](#reserve-exact-function-__stack_reserve_exact)
      - [Clear stack function `__stack_clear`](#clear-stack-function-__stack_clear)
      - [Free stack function `__stack_free`](#free-stack-function-__stack_free)
      - [Is stack empty function `__stack_is_empty`](#is-stack-empty-function-__stack_is_empty)
      - [Stack size function `__stack_size`](#stack-size-function-__stack_size)
      - [Remaining stack size function `__stack_remaining_size`](#remaining-stack-size-function-__stack_remaining_size)
      - [Return frame function `__stack_frame`](#return-frame-function-__stack_frame)
      - [Push function `__stack_push`](#push-function-__stack_push)
      - [Peek function `__stack_peek`](#peek-function-__stack_peek)
      - [Pop function `__stack_pop`](#pop-function-__stack_pop)
      - [Disown function `__stack_disown`](#disown-function-__stack_disown)
- [References](#references)

# Implementation

## Structure

The default stack structure is defined:

```C
typedef struct {
   void* frame;
   size_t capacity;
   size_t top;
} __Stack;
```

* frame: stores a (malloced) pointer to the stack;
* capacity: stores the current size (in bytes) of the frame;
* top: stores the current position (in bytes) of the top of the stack;

## Macros

| Macro name                    | Parameters                     | Predefinable |
| ----------------------------- | ------------------------------ | ------------ |
| `stack_default`               | _`prefix`_                     | no           |
| `stack_typedef`               | _`decl`_, _`type`_, _`prefix`_ | no           |
| `__stack_min_allocation_size` | none                           | yes          |
| `__stack_scalling_function`   | _`x`_                          | yes          |

### `stack_default`

It's a function-like macro used to define the typeless stack, not quite useful.

### `stack_typedef`

It's a function-like macro used to define the typed stack.

### `__stack_min_allocation_size`

It's a object-like macro that defines a integer value, preferably of `size_t` type, the default value is 0x20 (32).

### `__stack_scalling_function`

It's a function-like macro that calculates value, the default is defined `x + (x << 1)`, which is equivalent to floor of `x * 1.5`.

### Functions

| Function name            | Type                       |
| ------------------------ | -------------------------- |
| `__stack_init`           | `bool (__Stack*, size_t)`  |
| `__stack_reserve`        | `bool (__Stack*, size_t)`  |
| `__stack_reserve_exact`  | `bool (__Stack*, size_t)`  |
| `__stack_clear`          | `void (__Stack*)`          |
| `__stack_free`           | `void (__Stack*)`          |
| `__stack_is_empty`       | `bool (__Stack*)`          |
| `__stack_size`           | `size_t (__Stack*)`        |
| `__stack_remaining_size` | `size_t (__Stack*)`        |
| `__stack_frame`          | `void* (__Stack*)`         |
| `__stack_push`           | `void* (__Stack*, size_t)` |
| `__stack_peek`           | `void* (__Stack*, size_t)` |
| `__stack_pop`            | `void* (__Stack*, size_t)` |
| `__stack_disown`         | `void* (__Stack*)`         |

### Initialization function `__stack_init`

```C
bool __stack_init(__Stack* stack, size_t size);
```

This function initializes, i.e., allocates a memory for the `frame` pointer. The size of this memory, in bytes, will depend both in the `size` parameter and the macro `__stack_min_allocation_size`, the actual size will be `size` < `__stack_min_allocation_size` ? `__stack_min_allocation_size` : `size`, that is, their maximum.

> [!NOTE]
> All other functions in regard to stacks present _Undefined Behavior_ before a call to this function.

> [!WARNING]
> Calling this function on a already initialized stack will generate a _dangling pointer_.

### Reserve function `__stack_reserve`

```C
bool __stack_reserve(__Stack* stack, size_t size);
```

This function reserves _at least_ for `size` new bytes in the stack. It does nothing if there is enough space. The new allocated space can be defined the following way: If the top of the stack plus `size` is less or equal the the capacity, then we will allocate that capacity if it isn't already allocated. Otherwise, `capacity = __stack_scalling_function(capacity)`, then this condition is tested again.

> [!WARNING]
> Accessing any pointers related to this stack after calling this function is _Undefined Behabior_.

### Reserve exact function `__stack_reserve_exact`

```C
bool __stack_reserve_exact(__Stack* stack, size_t size);
```

This function reserves _exactly_ for `size` new bytes in the stack. It does nothing if there is already enough space. Otherwise, it sums the top offset to `size`, thus obtaining the new capacity.

> [!WARNING]
> Accessing any pointers related to this stack after calling this function is _Undefined Behabior_

### Clear stack function `__stack_clear`

```C
void __stack_clear(__Stack* stack);
```

This function sets the top to zero, effectively clearing the stack. No memory operations are done by this function.

### Free stack function `__stack_free`

```C
void __stack_free(__Stack* stack);
```

This function calls free (the stdlib function) on the stack frame.

> [!WARNING]
> Must NOT be called twice nor have been disowned previously.

### Is stack empty function `__stack_is_empty`

```C
bool __stack_is_empty(__Stack*)
```

Returns whether the stack is empty, equivalent to `__stack_size(stack) == 0`.

### Stack size function `__stack_size`

```C
size_t __stack_size(__Stack*)
```

Returns the size of the stack, that is, the amount of elements in the stack.

### Remaining stack size function `__stack_remaining_size`

```C
size_t __stack_remaining_size(__Stack*)
```

Returns the remaining size of the stack, that is, the amount elements that the stack can still fit.

### Return frame function `__stack_frame`

```C
void* __stack_frame(__Stack*)
```

Returns the stack frame.

> [!WARNING]
> Acessing this frame pointer _Undefined Behavior_ after a push or resize operation.

### Push function `__stack_push`

```C
void* __stack_push(__Stack*, size_t)
```

Returns a pointer to the start of the allocated block.

### Peek function `__stack_peek`

```C
void* __stack_peek(__Stack*, size_t)
```

Returns a pointer to the start of the last n allocated elements.

### Pop function `__stack_pop`

```C
void* __stack_pop(__Stack*, size_t)
```

Returns a pointer to the start of the last n allocated elements and deallocated that region.

> [!WARNING]
> If another push happens after the pop, the memory will likely be rewritten, since it is NOT copied somewhere else for popping.

### Disown function `__stack_disown`

```C
void* __stack_disown(__Stack*)
```

This functions shrinks the stack frame size to be as small as possible, removes its reference from the stack and returns it.

> [!NOTE]
> The stack must be initialized again to be used again.

> [!WARNING]
> Must NOT have been freed previously.

# References

* [Wikipedia - Stack (abstract data type)](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))