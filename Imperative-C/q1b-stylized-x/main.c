#include "cs136.h"

// This program recursively reads integres from the keyboards and
// draws a stylized X.

///////////////////////////////////
// DO NOT CHANGE THE BELOW CODE! //
///////////////////////////////////

// draw_spaces(spaces) prints out the number of spaces depending on
//  [spaces]
// requires: spaces >= 0
// effects: produces output
void draw_spaces(int spaces) {
  assert(spaces >= 0);
  if (spaces == 0) {
    return;
  } else {
    printf(" ");
    draw_spaces(spaces - 1);
  }
}

// draw_hyphens(n) prints out the number of hyphens based on the
//  [n] provided
//  requries: hyphens >= 0
// effects: produces output
void draw_hyphens(int hyphens) {
  assert(hyphens >= 0); 
  if (hyphens == 0) {
    return;
  } else {
    printf("-");
    draw_hyphens(hyphens - 1);
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
  if (n == row) {
    return;
  } else {
    const int space_in = 2 * n;
    draw_spaces(spaces);
    printf("\\");
    draw_spaces(space_in);
    printf("\\");
    draw_spaces(space_middle);
    printf("/");
    draw_spaces(space_in);
    printf("/\n");
    
    draw_middle_top(n, row + 1, spaces + 1, space_middle - 2);
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
  if (n == row) {
    return;
  } else {
    const int space_in = 2 * n;
    draw_spaces(spaces);
    printf("/");
    draw_spaces(space_in);
    printf("/");
    draw_spaces(space_middle);
    printf("\\");
    draw_spaces(space_in);
    printf("\\\n");
    
    draw_middle_bottom(n, row + 1, spaces - 1, space_middle + 2);
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

// read_int_rec() reads from input and draws a stylized x for each value
// effects: reads input
//          produces output
void read_int_rec(void) {
  int n = read_int();
  if (n == READ_INT_FAIL) {
    return;
  } else {
    draw_x(n);
    read_int_rec();
  }
}

int main(void) {
    read_int_rec();
}
