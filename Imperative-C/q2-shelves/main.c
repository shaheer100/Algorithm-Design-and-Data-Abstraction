#include "cs136.h"

// max(a, b) finds the maximum of a and b
int max(int a, int b) {
  if (a > b){
    return a;
  } else { 
    return b;
  }
}

// max_shelves(ply_width, ply_length, shelf_width, shelf_length) returns the 
//  value of the number of shelves that can be cut from a sheet of plywood 
//  given the length and width of the shelves and the plywood.
// requires: ply_width >= shelf_width and ply_length >= shelf_length
//           ply_width > 0 and ply_length > 0 and shelf_width > 0
//           and shelf_length > 0
int max_shelves(int ply_width, int ply_length, int shelf_width, 
                int shelf_length) {
  assert(ply_length > 0);
  assert(ply_width > 0);
  assert(shelf_width > 0);
  assert(shelf_length > 0);
  assert(ply_length + ply_width >= shelf_width + shelf_length);

  int max_of_w = (ply_length / shelf_length) * (ply_width / shelf_width);
  int max_of_l = (ply_length / shelf_width) * (ply_width / shelf_length);
  
  return max(max_of_w, max_of_l);
}

// print_results(ply_width, ply_length, shelf_width, shelf_length) prints the
//  the output of max_shelves in a sentence
//  effects: produces output
void print_results(int ply_width, int ply_length, int shelf_width, 
                   int shelf_length) {
  assert(ply_length > 0);
  assert(ply_width > 0);
  assert(shelf_width > 0);
  assert(shelf_length > 0);
  assert(ply_length + ply_width >= shelf_width + shelf_length);
  printf("We can cut a maximum of %d %d x %d shelves", 
         (max_shelves(ply_width, ply_length, shelf_width, shelf_length)),
         shelf_width, shelf_length);
  printf (" from a %d x %d sheet of plywood.\n", ply_width, ply_length);
  return;
}

// shelf_test(void) reads input and produces the output from print_results
// effects: reads input
//          may produce output
void shelf_test(void) {
  int m = read_int();
  int n = read_int();
  int o = read_int();
  int p = read_int();
  if (n == READ_INT_FAIL) {
    return;
  } else {
    print_results(m, n, o, p);
    shelf_test();
  }
}

int main(void) {
  shelf_test();
}
