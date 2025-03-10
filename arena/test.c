#include <stdlib.h>
#include <stdio.h>

#include "arena.h"

int main() {
   Arena arena = arena_create();
   printf("%p %p\n", (void*)arena.head, (void*)arena.tail);
}