#include "cs136.h"

// check_sub(result, num) returns a bool (0 or 1) depending on whether
//  integer addition will result in integer overflow.
//  requires: result <= INT_MAX && result >= INT_MIN
//            num <= INT_MAX && results >= INT_MIN
bool check_add(int result, int num) {
  assert(result >= -2147483648);
  assert(result <= 2147483647);
  assert(num >= -2147483648);
  assert(num <= 2147483647);
  
  if (num >= 0) {
    return (result > 2147483647 - num);
  }
  else {
    return (result < -2147483648 - num);
  }
}

// check_sub(result, num) returns a boolean (0 or 1) depending on whether 
//  integer subtraction will result integer overflow.
//  requires: result <= INT_MAX && result >= INT_MIN
//            num <= INT_MAX && results >= INT_MIN
bool check_sub(int result, int num) {
  assert(result >= -2147483648);
  assert(result <= 2147483647);
  assert(num >= -2147483648);
  assert(num <= 2147483647);
  
  if (num >= 0) {
    return (result < -2147483648 + num);
  }
  else {
    return (result > 2147483647 + num);
  }
}

// check_div(result, num) prints the error's (edge-cases) that can happen
//  through integer division and exits, if no errors found it returns to main.
//  requires: result <= INT_MAX && result >= INT_MIN
//            num <= INT_MAX && results >= INT_MIN
//  side effects: produces output
//                may terminate the program
void check_div(int result, int num) {
  assert(result >= -2147483648);
  assert(result <= 2147483647);
  assert(num >= -2147483648);
  assert(num <= 2147483647);
  
  if (num == 0) {
    printf("DIVIDE BY ZERO\n");
    exit(EXIT_SUCCESS);
  }
  else if ((result == -2147483648) && (num == -1)) {
    printf("OVERFLOW\n");
    exit(EXIT_SUCCESS);
  }
  else {
    return;
  }
}

// check_mult(result, num) returns either true or false, or prints "OVERFLOW" 
//  depending on whether the multuplication is possible (return false), else
//  return true. returns "OVERFLOW" for one main edge case and exits as well.
//  requires: result <= INT_MAX && result >= INT_MIN
//            num <= INT_MAX && results >= INT_MIN
//  side effects: produces output
//                may terminate the program
bool check_mult(int result, int num) {
  assert(result >= -2147483648);
  assert(result <= 2147483647);
  assert(num >= -2147483648);
  assert(num <= 2147483647);
  
  if (num > 1) {
    if (result > 0) {
      return (result > 2147483647 / num);
    } 
    else {
      return (result < -2147483648 / num);
    }
  } 
  else if (num < -1) {
    if (result < 0) {
      return (result < 2147483647 / num);
    }
    else {
      return (result > -2147483648 / num);
    }
  }
  else if ((result == -2147483648) && (num == -1)) {
    printf("OVERFLOW\n");
    exit(EXIT_SUCCESS);
  }
  else {
    return 0;
  }
}

/////////////////////////////////////////////////////////////////////////////
// Do not modify this function

// You MUST use this function to read in an int from input
// (it uses a method from section 4 -- you don't have to understand it yet)

// read_int_or_exit() reads in an integer from input, or exits (terminates)
//   the program if an int cannot be successfully read in
// note: terminates the program quietly with no output displayed
// effects: reads input
//          may terminate program (a rare side effect we don't normally
//                                 worry about in this course)
int read_int_or_exit(void) {
  int n = 0;
  if (scanf("%d", &n) != 1) {
    exit(EXIT_SUCCESS);
  }
  return n;
}
/////////////////////////////////////////////////////////////////////////////

int main(void) {
  int ADD = lookup_symbol("add");
  int SUB = lookup_symbol("sub");
  int MULT = lookup_symbol("mult");
  int DIV = lookup_symbol("div");
  
  // if there is any invalid input, the program simply stops
  //   with no error message
 int result = 0;
  while (1) {
    int cmd = read_symbol();
    int num = read_int_or_exit();
    if (cmd == ADD) {
      if (check_add(result, num) == 1) {
        printf("OVERFLOW\n");
        exit(EXIT_SUCCESS);
      }
      result = result + num;
    } 
    else if (cmd == SUB) {
      if (check_sub(result,num) == 1) {
        printf("OVERFLOW\n");
        exit(EXIT_SUCCESS);
      }
      result = result - num;
    } 
    else if (cmd == MULT) {
      if (check_mult(result, num) == 1) {
        printf("OVERFLOW\n");
        exit(EXIT_SUCCESS);
      }
      result = result * num;
    }
    else if (cmd == DIV) {
      check_div(result, num);
      result = result / num;
    }
    else {
      exit(EXIT_SUCCESS);
    }
    printf("%d\n", result);
  }
}
