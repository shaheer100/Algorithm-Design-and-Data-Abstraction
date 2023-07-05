#include "cs136.h"

// Do not modify these struct definitions.
struct row {
	int c0;
	int c1;
	int c2;
	int c3;
};
// requires: 0 <= c0, c1, c2, c3, and each has at most 5 digits

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
// requires: r is not null and r components at max 5 digits and positive. 
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

int main(void) {
  struct row test_row = {54321, 999, 8888, 12345};
	printf("print_row prints:\n");	
  print_row('[', &test_row, ']');

	printf("\nprint_matrix prints:\n");		
  struct matrix test_matrix = {
    {1, 1, 2, 5},
    {14, 42, 132, 429},
    {1430, 4862, 16796, 58786},
    {54321, 4321, 321, 21}
  };
  print_matrix(&test_matrix);
  
	printf("\nprint_lattice prints:\n");
  struct lattice latt = {};
  print_lattice(&latt);
}
