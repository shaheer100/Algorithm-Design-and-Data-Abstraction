#include "cs136.h"

// draw_box(width, height, c)  (prints) a solid box with the given positive
//   dimensions, and the non-whitespace printable ASCII character c.
// requires: ASCII character 33 and 136.
//           height > 0
//           width > 0
// side effects: produces output
void draw_box(int width, int height, char c) {
  assert(height > 0);
  assert(width > 0);
  assert(c >= 33 && c <= 126);
  int hcount = 1;
  int wcount = 1;
  while (hcount <= height && wcount <= width) {
   int i = 1;
   for (; i <= width; ++i) {
     printf("%c", c);
   }
   printf("\n");
   ++hcount;
  }
  return;
}

// draw_spaces(spa) prints out the number of spaces, from [spa]
// requires: spaces >= 0
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

// draw_top_half(height, size) prints the top half of the fancy box.
//  requires: size > 0
// side effects: produces output
void draw_top_half(int height, int size) {
  int spaces_in = 0;
  int spaces_out = size - 2;
  while (height > 0) {
    printf("|");
    draw_spaces(spaces_out);
    printf("/");
    draw_spaces(spaces_in);
    printf("\\");
    draw_spaces(spaces_out);
    printf("|\n");
    spaces_in = spaces_in + 2;
    --spaces_out;
    --height;
  }
  return;
}

// draw_bottom_half(height, size) prints the bottom half of the fancy box.
//  requires: size > 0
// side effects: produces output
void draw_bottom_half(height, size) {
  assert(size > 0);
  int spaces_in = size * 2 - 4;
  int spaces_out = 0;
  while (height > 0) {
    printf("|");
    draw_spaces(spaces_out);
    printf("\\");
    draw_spaces(spaces_in);
    printf("/");
    draw_spaces(spaces_out);
    printf("|\n");
    spaces_in = spaces_in - 2;
    ++spaces_out;
    --height;
  }
  return;
}

// draw_fancy_box(size) prints a fancy box
// requires: size > 0
// side effects: produces output
void draw_fancy_box(int size) {
  assert(size > 0);
  int dimensions = size * 2;
  
  printf("+");
  for (int hyphen = dimensions - 2; hyphen > 0; --hyphen) {
    printf("-");
  }
  printf("+\n");
  
  draw_top_half(size - 1, size);
  draw_bottom_half(size - 1, size);
  
  printf("+");
  for (int hyphen = dimensions - 2; hyphen > 0; --hyphen) {
    printf("-");
  }
  printf("+\n");
  
  return;
}

///////////////////////////////////
// DO NOT CHANGE THE BELOW CODE! //
///////////////////////////////////

int main(void) {
  int BOX = lookup_symbol("box");
  int FANCY_BOX = lookup_symbol("fancybox");
  // if there is any invalid input, the program simply stops
  //   with no error message
  while (1) {
    int cmd = read_symbol();
    if (cmd == BOX) {
      int width = read_int();
      int height = read_int();
      int c = read_char(true);
      if (height == READ_INT_FAIL || c == READ_CHAR_FAIL) {
        break;
      }
      draw_box(width, height, c);
    } else if (cmd == FANCY_BOX) {
      int size = read_int();
      if (size == READ_INT_FAIL) {
        break;
      }
      draw_fancy_box(size);
    } else {
      break;
    }
    printf("\n");
  }
}
