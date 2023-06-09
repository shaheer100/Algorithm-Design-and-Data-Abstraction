#include "cs136.h"

// odd_adder(odd) calculates the sum of the odd digits of the 
//  UPC barcode and returns that value to the main
long odd_adder(long odd) {
  if (odd == 0) {
    return odd;
  } else {
    return ((odd % 10) + odd_adder(odd/100));
  }
}

// even_adder(even) calculates the sum of the even digits of the
//  UPC barcode and returns that value to the main
long even_adder(long even) {
  if (even == 0) {
    return even;
  } else {
    return ((even % 10) + even_adder(even/100));
  }
}

// check_digit_calc(potenial_check) calculates the check digit and
//  returns it's value.
long check_digit_calc(potential_check) {
  if (potential_check % 10 == 0) {
    return 0;
  } else {
    return 10 - potential_check % 10;
 }
}

// validate_upc(upc) returns true if the last digit of upc is the correct
//   check digit and false otherwise.
// requires: upc is a 12 digit positive number
bool validate_upc(long upc) {
  assert(upc > 0);
  long check_digit = upc % 10;
  long eleven = upc / 10;
  long sum_even_odd = odd_adder(eleven) * 3 + even_adder(upc / 100);
  long pot_check = check_digit_calc(sum_even_odd);
  if (pot_check == check_digit) {
    return true;
  } else {
    return false;
  }
}


int main(void) {
  // public tests
  assert(validate_upc(725272730706));
  assert(!validate_upc(640754291001));
  assert(validate_upc(693508003156));

  // add your own tests below
  
  assert(validate_upc(123456789012));
  assert(!validate_upc(131940329104));
  assert(validate_upc(981276340000));

  return EXIT_SUCCESS;
}
