#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "stack.h"
stack_typedef(StackInt, int, int_stack)

int main(int argc, char** argv) {

   StackInt stack; int_stack_init(&stack, 16);

   while (true) {
      printf("Insert a number: ");

      int num;
      scanf_s("%d", &num);

      if (num < 0) break;
      *int_stack_push(&stack, 1) = num;
   }

   size_t size = int_stack_size(&stack);
   int* buffer = int_stack_disown(&stack);

   int i = 0;
   if (size) while (true) {
      printf("%d", buffer[i]);
      if (++i >= size) break;
      printf(", ");
   }

   free(buffer);
   return 0;
}