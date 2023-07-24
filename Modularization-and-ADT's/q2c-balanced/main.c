#include "cs136-trace.h"
#include <stdio.h>
#include <assert.h>
#include "stack.h"

int main(void) {
  struct stack *open = stack_create();
  struct stack *close = stack_create();
  struct stack *temp = stack_create();
  char c = '0';

  while (scanf("%c", &c) == 1) {
    if (c == '(' || c == '{' || c == '[' || c == '<') {
      stack_push(c, open);
    } else if (c == ')' || c == '}' || c == ']' || c == '>') {
      stack_push(c, close);
    }
  }

  // reverse open stack to temp stack
  while (!stack_is_empty(open)) {
    stack_push(stack_top(open), temp);
    stack_pop(open);
  }

  int is_balanced = 1;
  while (!stack_is_empty(temp) && !stack_is_empty(close)) {
  char stack_temp = stack_pop(temp);
  char stack_close = stack_pop(close);
    if (((stack_temp == '(') && (stack_close == ')')) ||
        ((stack_temp == '[') && (stack_close == ']')) ||
        ((stack_temp == '{') && (stack_close == '}')) ||
        ((stack_temp == '<') && (stack_close == '>'))) {
      continue;
    } else {
      is_balanced = 0;
      break;
    }
  }

  if (!is_balanced || !stack_is_empty(temp) || !stack_is_empty(close)) {
    printf("unbalanced\n");
  } else {
    printf("balanced\n");
  }

  stack_destroy(open);
  stack_destroy(close);
  stack_destroy(temp);
  return 0;
}
