# Stack

Stack is a _abstract data structure_ that is a collection of object of some kind. The Stack has two main operations defined over it:

* push: An object is added to the top of the collection; and
* pop: An object is remove from the top of the stack and gives back that object.

Other operation may be defined in a stack, however these are the main ones.

## Implementation

### Structure

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

### Macros

| Macro name                                                  | Parameters         | Predefinable |
| ----------------------------------------------------------- | ------------------ | ------------ |
| `stack_default`(#stack_default)                             | _`prefix`_         | no           |
| `stack_typedef`(#stack_typedef)                             | _`decl`_, _`type`_ | no           |
| `__stack_min_allocation_size`(#__stack_min_allocation_size) | none               | yes          |
| `__stack_scalling_function`(#__stack_scalling_function)     | _`x`_              | yes          |

#### `stack_default`
#### `stack_typedef`

#### `__stack_min_allocation_size`

Is a object-like macro that defines a integer value, preferably of `size_t` type,   

#### `__stack_scalling_function`

### Functions

| Function name           | Type                      |
| ----------------------- | ------------------------- |
| `__stack_init`          | `bool (__Stack*, size_t)  |
| `__stack_reserve`       | `bool (__Stack*, size_t)  |
| `__stack_reserve_exact` | `bool (__Stack*, size_t)  |
| `__stack_clear`         | `void (__Stack*)          |
| `__stack_free`          | `void (__Stack*)          |
| `__stack_size`          | `size_t (__Stack*)        |
| `__stack_frame`         | `void* (__Stack*)         |
| `__stack_push`          | `void* (__Stack*, size_t) |
| `__stack_peek`          | `void* (__Stack*, size_t) |
| `__stack_pop`           | `void* (__Stack*, size_t) |
| `__stack_disown`        | `void* (__Stack*)         |

#### Initialization function `__stack_init`

```C
bool __stack_init(__Stack* stack, size_t size);
```

This function initializes, i.e., allocates a memory for the `frame` pointer. The size of this memory, in bytes, will depend both in the `size` parameter and the macro `__stack_min_allocation_size`, the actual size will be `size` < `__stack_min_allocation_size` ? `__stack_min_allocation_size` : `size`, that is, their maximum.

#### Reserve function `__stack_reserve`

```C
bool __stack_reserve(__Stack* stack, size_t size);
```

This function reserves _at least_ for `size` new bytes in the stack. It does nothing if there is enough space. The new allocated space can be defined the following way: If the top of the stack plus `size` is less or equal the the capacity, then we will allocate that capacity if it isn't already allocated. Otherwise, `capacity = __stack_scalling_function(capacity)`, then this condition is tested again.

#### Reserve exact function `__stack_reserve_exact`

```C
bool __stack_reserve_exact(__Stack* stack, size_t size);
```

This function reserves _exactly_ for `size` new bytes in the stack. It does nothing if there is already enough space. Otherwise, it sums the top offset to `size`, thus obtaining the new capacity.

[!WARN] Test

#### Clear stack function `__stack_clear`

```C
void __stack_clear(__Stack* stack);
```

This function sets the top to zero, effectively clearing the stack. No memory operations are done by this function.

#### Free stack function `__stack_free`

```C
void __stack_free(__Stack* stack);
```

This function calls free (the stdlib function) on the stack frame. It presents undefined behavior if call on a uninitialized stack structure.

#### Stack size function `__stack_size`
size_t __stack_size (__Stack*)
#### Return frame function `__stack_frame`
void* __stack_frame (__Stack*)
#### Push function `__stack_push`
void* __stack_push (__Stack*, size_t)
#### Peek function `__stack_peek`
void* __stack_peek (__Stack*, size_t)
#### Pop function `__stack_pop`
void* __stack_pop (__Stack*, size_t)
#### Disown function `__stack_disown`
void* __stack_disown (__Stack*)

## References

* [Wikipedia - Stack (abstract data type)](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))