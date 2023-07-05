#include "cs136.h"

const char first_printable_char = 32;
const char last_printable_char = 95;
const char interval_size = 64;
const char chunk = 4;

// printable_to_cords(ch, x, y, z) given a valid char, mutates x,y,z so that
//  they are coordinates that would cause coords_to_printable(x,y,z)
//  to return printable
// effects: modifies *x and *y and *z
// requires: x and y and z are not null.
//           first_printable_char <= ch && ch <= last_printable_char
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

// Do not modify these struct definitions.
struct row {
	int c0;
	int c1;
	int c2;
	int c3;
};

struct matrix {
	struct row c0;
	struct row c1;
	struct row c2;
	struct row c3;
};

struct lattice {
	struct matrix c0;
	struct matrix c1;
	struct matrix c2;
	struct matrix c3;
};

// print_row(prefix, r, suffix) prints a row 1 x 4 vector.
// requires: r is not null and r components has at max 5 digits and positive.
// effects: produces output
void print_row(char prefix, const struct row *r, char suffix) {
  assert(r);
  assert(r->c0 >= 0);
  assert(r->c0 <= 99999);
  assert(r->c1 >= 0);
  assert(r->c1 <= 99999);
  assert(r->c2 >= 0);
  assert(r->c2 <= 99999);
  assert(r->c3 >= 0);
  assert(r->c3 <= 99999);
  printf("%c", prefix);
  
  printf("%5d", r->c0);
  printf("%5d", r->c1);
  printf("%5d", r->c2);
  printf("%5d", r->c3);
  
  printf("%c", suffix);
  printf("\n");
}

// print_matrix(m) prints a row 4x4 matrix.
// requires: m is not null
// effects: produces output
void print_matrix(const struct matrix *m) {
  assert(m);
  print_row('/', &(m->c0), '\\');
  print_row('|', &(m->c1), '|');
  print_row('|', &(m->c2), '|');
  print_row('\\', &(m->c3), '/');
}

// print_lattice(latt) prints a row 4 matrix values.
// requires: latt is not null
// effects: produces output
void print_lattice(const struct lattice *latt) {
  assert(latt);
  printf("/--------------------");
  printf("%c", '\\');
  printf("\n");
  print_matrix(&(latt->c0));
  printf("\n");
  print_matrix(&(latt->c1));
  printf("\n");
  print_matrix(&(latt->c2));
  printf("\n");
  print_matrix(&(latt->c3));

  printf("%c", '\\');
  printf("--------------------/");
  printf("\n");
}

// element_selector(row1, x, num) selects an element through [x] to write to num
// requires: row1 is not null
//           0 <= x && x <= 3
//           0 <= num && num <= 99999
// effects: modifies *row1
void element_selector(struct row *row1, int x, int num){
  assert(row1);
  assert(0 <= x && x <= 3);
  assert(0 <= num && num <= 99999);
  if (x == 0){
    row1->c0 = num;
  }
  else if (x == 1){
    row1->c1 = num;
  }
  else if (x == 2){
    row1->c2 = num;
  }
  else if (x == 3){
    row1->c3 = num;
  }
}

// row_selector(mat, x, y, num) selects a row through [y] to determine which 
//  row to write in
// requires: mat is not null
//           0 <= x && x <= 3
//           0 <= y && y <= 3
//           0 <= num && num <= 99999
// effects: modifies *mat
void row_selector(struct matrix *mat, int x, int y, int num){
  assert(mat);
  assert(0 <= x && x <= 3);
  assert(0 <= y && y <= 3);
  assert(0 <= num && num <= 99999);
  if (y == 0){
    element_selector(&(mat->c0), x, num);
  }
  else if (y == 1){
    element_selector(&(mat->c1), x, num);
  }
  else if (y == 2){
    element_selector(&(mat->c2), x, num);
  }
  else if (y == 3){
    element_selector(&(mat->c3), x, num);
  }
}

// matrix_selector(latt, x, y, z, num) selects a matrix through [z] to determine
//  which matrix to write in
// requires: latt is not null
//           0 <= x && x <= 3
//           0 <= y && y <= 3
//           0 <= z && z <= 3
//           0 <= num && num <= 99999
// effects: modifies *latt
void matrix_selector(struct lattice *latt, int x, int y, int z, int num){
  assert(latt);
  assert(0 <= x && x <= 3);
  assert(0 <= y && y <= 3);
  assert(0 <= z && z <= 3);
  assert(0 <= num && num <= 99999);
  if (z == 0){
    row_selector(&(latt->c0), x, y, num);
  }
  else if (z == 1){
    row_selector(&(latt->c1), x, y, num);
  }
  else if (z == 2){
    row_selector(&(latt->c2), x, y, num);
  }
  else if (z == 3){
    row_selector(&(latt->c3), x, y, num);
  }
}

// lattice_IO() has a local variable latt of type struct and reads a series of 
//  commands. Each command shall consist of optional whitespace, then one of 
//  the following:
//  1. P, followed by nothing. This command causes it to print the contents of 
//     latt, using print_lattice.
//  2. W, followed by a printable char between 32 and 95 corresponding to 
//     coordinate (x,y,z), followed by a non-negative int of at most 5 digits. 
//     This shall cause it to write the int value to position x, in row y, of 
//     matrix z, of latt.
// side effects: reads input
//               produces output
void lattice_IO(void) {
  struct lattice latt = {};
  
  while (1) {
    char letter = '0';
    char command = '0';
    char x = '0';
    char y = '0';
    char z = '0' ;
    int num = 0;
    
    scanf(" %c", &letter); //ignores whitespace and reads first character
  
    if (letter == 'P') {
      print_lattice(&latt);
    }
    
    else if (letter == 'W') {
      scanf("%c", &command);
      assert(32 <= command);
      assert(command <= 95);
      scanf("%d", &num);
      assert(num >= 0);
      assert(num <= 99999);
      printable_to_coords(command, &x, &y, &z);
      matrix_selector(&latt, x, y, z, num);
    }
    
    else {
      break;
    }
  }
}

int main(void) {
  // Do not modify the main function!
  lattice_IO();
}
