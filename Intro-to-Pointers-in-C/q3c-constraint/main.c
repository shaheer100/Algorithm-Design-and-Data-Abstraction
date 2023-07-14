#include "cs136.h"

struct point {
	int x;
	int y;
};

struct rectangle {
	struct point top_left;
	struct point bottom_right;
};

// Here are some functions to use as function pointers.
// Do not modify width_rectangle, height_rectangle, or area_rectangle

// width_rectangle(r) Find the width of r.
int width_rectangle(const struct rectangle *r) {
	return abs(r->bottom_right.x - r->top_left.x);
}

// height_rectangle(r) Find the height of r.
int height_rectangle(const struct rectangle *r) {
	return abs(r->top_left.y - r->bottom_right.y);
}

// area_rectangle(r) Calculate the area of r.
int area_rectangle(const struct rectangle *r) {
	return width_rectangle(r) * height_rectangle(r);
}

// update_rectangle(x_left, y_top, x_right, y_bottom, bounds) updates the bounds
//  i.e the rectangle
// requires: top_left.x < bottom_right.x
//           top_left.y > bottom_right.y
//           bounds is not null.
// side effects: modfies bound
void update_rectangle(int x_left, int y_top, int x_right, int y_bottom,
                      struct rectangle *bounds) {
  assert(bounds);
  bounds->top_left.x = x_left;
  bounds->top_left.y = y_top;
  bounds->bottom_right.x = x_right;
  bounds->bottom_right.y = y_bottom;
  assert(bounds->top_left.x < bounds->bottom_right.x);
  assert(bounds->top_left.y > bounds->bottom_right.y);
}

// swap_greater(destination, r1, f) returns the rectangle, destination for 
//  which the f returns a greater value, and r1 for the one with the lesser 
//  value
// requires: destination, r1, f are all valid pointers and not null
//           destination.top_left.x < destination.bottom_right.x && 
//           destination.top_left.y > destination.bottom_right.y
//           r1.top_left.x < r1.bottom_right.x && 
//           r1.top_left.y > r1.bottom_right.y
// side effects: modifies destination
void swap_greater(struct rectangle* const destination, 
                 struct rectangle* const r1,
                 int (*f)(const struct rectangle*)) {
  assert(f);
  assert(destination);
  assert(r1);
  
  if(f(destination) >= f(r1)) {
    return;
  }
  else {
    *destination = *r1;
  }
  assert(destination->top_left.x < destination->bottom_right.x);
  assert(destination->top_left.y > destination->bottom_right.y);
  assert(r1->top_left.x < r1->bottom_right.x);
  assert(r1->top_left.y > r1->bottom_right.y);
}

// greatest_rectangle(destination, f) mutates the value of destination so it
//  stores the the rectangle for which a call to f returns the largest value,
//  in case of a tie it returns the rectangle that was encountered earlier.
// requires: destination and f != null
// side effects: modifies destination
void greatest_rectangle(struct rectangle *destination,
                        int (*f)(const struct rectangle*)) {
  //asserts
  assert(destination);
  assert(f);
  
  //variables
  struct rectangle r1 = {};
  int retval = 0;
  int scan = 0;
  retval = scanf("%d", &scan);
  
  while(scan > 0) {
    if (retval == -1) {
      break;
    }
    int topx = 0;
    int topy = 0;
    int bottomx = 0;
    int bottomy = 0;
    scanf("%d", &topx);
    scanf("%d", &topy);
    scanf("%d", &bottomx);
    scanf("%d", &bottomy);
    update_rectangle(topx, topy, bottomx, bottomy, &r1);
    swap_greater(destination, &r1, f);
    --scan;
    assert(destination->top_left.x < destination->bottom_right.x);
    assert(destination->top_left.y > destination->bottom_right.y);
    assert(r1.top_left.x < r1.bottom_right.x);
    assert(r1.top_left.y > r1.bottom_right.y);
  }
}

int main(void) {
  // This main function is designed to work with any input file that contains
  // three sets of rectangles, with a particular set of function pointers.
  // To test your code carefully, create different main functions
  // to go along with different function pointers and sets of rectangles.
  // We will use different main functions and input files for private tests.
  struct rectangle r = {{0,0},{0,0}};
  
  // read some rects, and find the one with largest area:
	greatest_rectangle(&r, &area_rectangle);
	printf("%d %d %d %d\n", r.top_left.x, r.top_left.y, r.bottom_right.x, r.bottom_right.y);
	
  // read some rects, and find the one with largest width:
	greatest_rectangle(&r, &width_rectangle);
	printf("%d %d %d %d\n", r.top_left.x, r.top_left.y, r.bottom_right.x, r.bottom_right.y);

  // read some rects, and find the one with largest height:
  greatest_rectangle(&r, &height_rectangle);
	printf("%d %d %d %d\n", r.top_left.x, r.top_left.y, r.bottom_right.x, r.bottom_right.y);
}
