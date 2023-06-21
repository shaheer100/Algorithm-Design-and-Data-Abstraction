#include "cs136.h"

// draw_spaces(spa) prints out the number of spaces, from [spa]
// requires: spa >= 0
// side effects: produces output
void draw_spaces(int spa) {
  assert(spa >= 0);
  int count = 1;
  while (count <= spa) {
    printf(" ");
    ++count;
  }
  return;
}

// draw_hyphens(n) prints out the number of hyphens based on the
//  [n] provided
//  requries: hyphens >= 0
// effects: produces output
void draw_hyphens(int hyphens) {
  assert(hyphens >= 0);
  for (int count = 1; count <= hyphens; ++count) {
    printf("-");
  }
}

// draw_middle_top(n, row, spaces, space_middle) prints out the 
//  top-middle portion of the X
//  requires: n >= row and spaces >= 0 and space_middle >= 0
// effects: produces output
void draw_middle_top(int n, int row, int spaces, int space_middle) {
  assert(n >= row);
  assert(spaces >= 0);
  assert(space_middle >= 0);
  
  const int space_in = 2 * n;
  while (row < n) {
    draw_spaces(spaces);
    printf("\\");
    draw_spaces(space_in);
    printf("\\");
    draw_spaces(space_middle);
    printf("/");
    draw_spaces(space_in);
    printf("/\n");
    ++row;
    ++spaces;
    space_middle = space_middle - 2;
  }
}

// draw_middle_bottom(n, row, spaces, space_middle) prints out the 
//  bottom-middle portion of the X
//  requires: n >= row and spaces >= 0 and space_middle >= 0
// effects: produces output
void draw_middle_bottom(int n, int row, int spaces, int space_middle) {
  assert(n >= row);
  assert(spaces >= 0);
  assert(space_middle >= 0);
  
  const int space_in = 2 * n;
  while (row < n) {
    draw_spaces(spaces);
    printf("/");
    draw_spaces(space_in);
    printf("/");
    draw_spaces(space_middle);
    printf("\\");
    draw_spaces(space_in);
    printf("\\\n");
    
    ++row;
    --spaces;
    space_middle = space_middle + 2;
  }
}

// draw_x(n) consumes a positive integer and will draw
//  a stylized x of the specified side, meaning number of rows's 
//  of / \ printed
// requires: n > 0
// effects: produces output
void draw_x(int n) {
  assert(n > 0);
  printf("+");
  draw_hyphens(n*2);
  printf("+");
  draw_spaces(2 * n + 2);
  printf("+");
  draw_hyphens(n*2);
  printf("+\n");
  
  draw_middle_top(n, 0, 1, 2 * n);
  
  draw_spaces(n + 1);
  printf(">");
  draw_hyphens(n*2);
  printf(">");
  printf("<");
  draw_hyphens(n*2);
  printf("<\n");
  
  draw_middle_bottom(n, 0, n, 2);
  
  printf("+");
  draw_hyphens(n*2);
  printf("+");
  draw_spaces(2 * n + 2);
  printf("+");
  draw_hyphens(n*2);
  printf("+\n");
}

///////////////////////////////////
// DO NOT CHANGE THE BELOW CODE! //
///////////////////////////////////

int main(void) {
  int n = read_int();
  while (n != READ_INT_FAIL) {
    draw_x(n);
    n = read_int();
  }
}
