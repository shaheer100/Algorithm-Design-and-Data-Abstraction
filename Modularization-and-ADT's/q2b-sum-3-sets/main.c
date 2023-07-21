#include <stdio.h>
#include "stack.h"
#include <assert.h>

// build_stack (s, n) creates a stack realting to the sets that are scanned in
//  from input.
//  requires: s is a valid pointer
//            n >= 0
//  side effects: modifies s
void build_stack(struct stack *s, int n) {
  assert(s);
  assert(n >= 0);
  int input = 0;
  for (int count = 0; count < n; ++count) {
    scanf("%d", &input);
    stack_push(input, s);
  }
}

int main(void) {
  struct stack *s1 = stack_create();
  struct stack *s2 = stack_create();
  struct stack *s3 = stack_create();
  struct stack *sums = stack_create();
  int n = 0;
  scanf("%d", &n);

  // reading input into the 3 sets.
  build_stack(s1, n);
  build_stack(s2, n);
  build_stack(s3, n);

  while (!stack_is_empty(s2)) {
    int stack1 = stack_pop(s1);
    int stack2 = stack_pop(s2);
    int stack3 = stack_pop(s3);
    stack_push(stack1 + stack2 + stack3, sums);
  }
  while (!stack_is_empty(sums)) {
    printf("%d\n", stack_pop(sums));
  }
  stack_destroy(s1);
  stack_destroy(s2);
  stack_destroy(s3);
  stack_destroy(sums);
}
