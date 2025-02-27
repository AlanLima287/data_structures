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



### Functions

| Function name                                     | Type                      |
| ------------------------------------------------- | ------------------------- |
| [`__stack_init         `](#__stack_init)          | `bool   (__Stack, size_t) |
| [`__stack_reserve      `](#__stack_reserve)       | `bool   (__Stack, size_t) |
| [`__stack_reserve_exact`](#__stack_reserve_exact) | `bool   (__Stack, size_t) |
| [`__stack_clear        `](#__stack_clear)         | `void   (__Stack)         |
| [`__stack_free         `](#__stack_free)          | `void   (__Stack)         |
| [`__stack_size         `](#__stack_size)          | `size_t (__Stack)         |
| [`__stack_frame        `](#__stack_frame)         | `void*  (__Stack)         |
| [`__stack_push         `](#__stack_push)          | `void*  (__Stack, size_t) |
| [`__stack_peek         `](#__stack_peek)          | `void*  (__Stack, size_t) |
| [`__stack_pop          `](#__stack_pop)           | `void*  (__Stack, size_t) |
| [`__stack_disown       `](#__stack_disown)        | `void*  (__Stack)         |

#### Initialization function `__stack_init`

```C
bool __stack_init(__Stack* stack, size_t size);
```

This function behavior is, basically,

## References

* [Wikipedia - Stack (abstract data type)](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

```
┌ ┐        ┌ ┐        ┌ ┐        ┌ ┐        ┌ ┐
│ │        │ │        │ │        │%│        │ │
│D│  pop   │ │ push # │#│ push % │#│  pop   │#│
│C│ =====> │C│ =====> │C│ =====> │C│ =====> │C│
│B│        │B│        │B│        │B│        │B│
│A│        │A│        │A│        │A│        │A│
└─┘        └─┘        └─┘        └─┘        └─┘

```

<!--
┌┬┐
├┼┤
│┴│
└─┘
-->

```JS
const stack = ['A', 'B', 'C', 'D']

console.log(stack.pop()) // 'D'

stack.push('#'); console.log(stack) // (4) ['A', 'B', 'C', '#']

stack.push('%'); console.log(stack) // (5) ['A', 'B', 'C', '#', '%']

console.log(stack.pop()) // '%'
```