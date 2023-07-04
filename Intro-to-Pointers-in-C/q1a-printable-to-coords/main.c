#include "cs136.h"

const char first_printable_char = 32;
const char last_printable_char = 95;
const char interval_size = 64;
const char chunk = 4;

// coords_to_printable(x, y, z) Return a printable char, between 32 and 95,
//   corresponding to the coordinates (x, y, z).
// requires: 0 <= x, y, z < 4
char coords_to_printable(char x, char y, char z) {
  assert(0 <= x && x < chunk);
  assert(0 <= y && y < chunk);
  assert(0 <= z && z < chunk);
	return first_printable_char + z * chunk * chunk + y * chunk + x;
}

// printable_to_cords(ch, x, y, z) given a valid char, mutates x,y,z so that
//  they are coordinates that would cause coords_to_printable(x,y,z)
//  to return printable
// requires: x and y and z are not null.
//           first_printable_char <= ch && ch <= last_printable_char
// effects: modifies *x and *y and *z
void printable_to_coords(char ch, char *x, char *y, char *z) {
  assert(x);
  assert(y);
  assert(z);
  assert(first_printable_char <= ch);
  assert(ch <= last_printable_char);
 
  int val = ch - first_printable_char;
  *x = val % chunk;
  val = val / chunk;
  *y = val % chunk;
  *z = val / chunk;
}

int main(void) {
  char x = 0;
  char y = 0;
  char z = 0;
  char printable = 0;

	// Tests to verify that printable_to_coords reverses coords_to_printable.
	printable = coords_to_printable(1,2,3);
	printable_to_coords(printable, &x, &y, &z);
	assert(x == 1 && y == 2 && z == 3);

	printable = coords_to_printable(0,1,1);
	printable_to_coords(printable, &x, &y, &z);
	assert(x == 0 && y == 1 && z == 1);
	
	printable = coords_to_printable(1,1,1);
	printable_to_coords(printable, &x, &y, &z);
	assert(x == 1 && y == 1 && z == 1);
	
	printable = coords_to_printable(3,3,3);
	printable_to_coords(printable, &x, &y, &z);
	assert(x == 3 && y == 3 && z == 3);
  
}
