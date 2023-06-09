#include "cs136.h"

// nth_hexagonal(n) returns the n-th hexagonal number
// requires: n > 0
int nth_hexagonal(int n) {
  assert(n > 0);
  return 2 * (n * n) - n;
}

// hexagonal_2(n, h) compares the hexagoanal value [n], searching
// from h and returns true if it finds a value equal but if it
// leaves the range it returns false
int hexagonal_2(int n, int h) {
  int hexa = nth_hexagonal(h);
  if (n == hexa) {
    return 1;
  } else if (h < n) {
    return hexagonal_2(n, h + 1);
  } else {
    return 0;
  }
}

// is_hexagonal(n) determines whether a number [n] is hexagonal
// returns true, false otherwise
// requires: n > 0
bool is_hexagonal(int n) {
  assert(n > 0);
  return hexagonal_2(n, 1);
}

int main(void) {
  // public tests
  assert(is_hexagonal(6));
  assert(nth_hexagonal(3) == 15);

  // add your own tests below
  assert(is_hexagonal(15));
  assert(!is_hexagonal(16));
  assert(is_hexagonal(28));
  assert(nth_hexagonal(2) == 6);
  assert(nth_hexagonal(4) == 28);
  
  return EXIT_SUCCESS;
}
