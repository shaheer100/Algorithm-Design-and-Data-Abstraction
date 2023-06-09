#include "cs136.h"

// sum_digits_simple(n) returns the sum of all digits in a number
//   using simple recursion.
// requires: n must be non-negative
int sum_digits_simple(int n) {
  assert(n >= 0);
  if (n == 0) {
    return 0;
  } else {
    return (n % 10) + sum_digits_simple(n / 10);
  }
}


// sum_digits_acc_helper(n, acc) returns the sum of all digits 
//   in a number using accumulative recursion.
// requires: n must be non-negative
int sum_digits_acc_helper(int n, int acc) {
  assert(n >= 0);
  if (n == 0) {
    return acc;
  } else {
    return sum_digits_acc_helper(n / 10, (n % 10 + acc));
  }
}

// sum_digits_acc(n) calls the helper function which returns the 
//   the sum of all digits in a number using accumulative recursion.
int sum_digits_acc(int n) {
  assert(n >= 0);
  return sum_digits_acc_helper(n, 0);
}

int main(void) {
  // public tests
  assert(sum_digits_simple(44) == 8);
  assert(sum_digits_acc(44) == 8);

  // add your own tests below
  
  assert(sum_digits_simple(246) == 12);
  assert(sum_digits_simple(100) == 1);
  assert(sum_digits_simple(0) == 0);
  assert(sum_digits_simple(1) == 1);
  assert(sum_digits_acc(246) == 12);
  assert(sum_digits_acc(100) == 1);
  assert(sum_digits_acc(0) == 0);
  assert(sum_digits_acc(1) == 1);
  
  return EXIT_SUCCESS;
}
