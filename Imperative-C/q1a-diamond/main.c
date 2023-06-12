#include "cs136.h"

// This program recursively reads integres from the keyboards and
// draws diamonds.

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

// draw_o(os) prints out the number of o's depending on the [os]
// requires: os >= 0;
// effects: produces output
void draw_o(int os) {
 assert(os >= 0);
 if (os == 0) {
   return;
 } else {
   printf("o");
   draw_o(os - 1);
 }
}

// draw_top_diamond(n, first_odd, spaces) draws the top half
//  of the diamond according to the specifications
// requires: n % 2 != 0 and n >= 1 and spaces >= 0
//.          first_odd <= n && first_odd >= 1
// effects: produces output
void draw_top_diamond(int n, int first_odd, int spaces) {
  assert(n % 2 != 0);
  assert(n >= 1);
  assert(first_odd <= n && n >= 1);
  assert(spaces >= 0);
  if (first_odd == n) {
    printf("/");
    draw_o(n);
    printf("\\\n");
    return;
  } else {
    draw_spaces(spaces);
    printf("/");
    draw_o(first_odd);
    printf("\\\n");
        
    first_odd = first_odd + 2;
    draw_top_diamond(n, first_odd, spaces - 1);
  }
}

// draw_bottom_diamond(n, last_odd, spaces) draws the bottom half
//  of the diamond according to the specifications
// requires: n % 2 != 0 and n >= 1 and spaces >= 0
//           last_odd <= n && last_odd >= 1
// effects: produces output
void draw_bottom_diamond(int n, int last_odd, int spaces) {
  assert(last_odd <= n && last_odd >= 1);
  assert(spaces >= 0);
  assert(n % 2 != 0);
  assert(n >= 1);
  if (last_odd == 1) {
    draw_spaces(spaces);
    printf("\\");
    draw_o(1);
    printf("/\n");
    draw_spaces(spaces + 1); //draw space for star
    return;
  } else {
    draw_spaces(spaces);
    printf("\\");
    draw_o(last_odd);
    printf("/\n");
    
    last_odd = last_odd - 2;
    draw_bottom_diamond(n, last_odd, spaces + 1);
  }
}

// draw_diamond(n) consumes a positive odd integer and will draw
//  a diamond of the specified size, meaning number of o's printed
//  accross a single line
// requires: n % 2 != 0 and n >= 1
// effects: produces output
void draw_diamond(int n) {
  assert(n % 2 != 0);
  assert(n >= 1);
  int spaces = (n / 2) + 1;
  draw_spaces(spaces); 
  printf("*\n");
  spaces -= 1;
  draw_top_diamond(n, 1, spaces);
  draw_bottom_diamond(n, n, 0);
  printf("*\n");
}

// read_int_rec() reads from input and draws a diamond for each value
// effects: reads input
//          produces output
void read_int_rec(void) {
  int n = read_int();
  if (n == READ_INT_FAIL) {
    return;
  } else {
    draw_diamond(n);
    read_int_rec();
  }
}

int main(void) {
    read_int_rec();
}
