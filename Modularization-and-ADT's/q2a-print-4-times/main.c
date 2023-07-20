#include <stdio.h>
#include "stack.h"

int main(void) {
  int num = 0;
  struct stack *s = stack_create();
  struct stack *s2 = stack_create();
  while (scanf("%d", &num) == 1) {
    stack_push(num, s);
    printf("%d\n", stack_top(s));
  }
  
  while (!stack_is_empty(s)) {
    stack_push(stack_top(s), s2);
    printf("%d\n", stack_top(s2));
    stack_pop(s);
  } 
  
  while (!stack_is_empty(s2)) {
    stack_push(stack_top(s2), s);
    printf("%d\n", stack_top(s2));
    stack_pop(s2);
  }
  
  while (!stack_is_empty(s)) {
    stack_push(stack_top(s), s2);
    printf("%d\n", stack_top(s2));
    stack_pop(s);
  }
  
  stack_destroy(s);
  stack_destroy(s2);
}
