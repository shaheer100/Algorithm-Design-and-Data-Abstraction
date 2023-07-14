#include "cs136.h"

struct point {
	int x;
	int y;
};

struct rectangle {
	struct point top_left;
	struct point bottom_right;
};

// rectangle_equal(r0, r1) returns true if both [r0] and [r1] are equal and
//  false otherwise
// requires: r0.top_left.x < r0.bottom_right.x && 
//           r0.top_left.y > r0.bottom_right.y
//           r1.top_left.x < r1.bottom_right.x && 
//           r1.top_left.y > r1.bottom_right.y
//           r0 and r1 are both not null
bool rectangle_equal(const struct rectangle* r0, const struct rectangle* r1) {
  assert(r0);
  assert(r1);
  assert(r0->top_left.x < r0->bottom_right.x);
  assert(r0->top_left.y > r0->bottom_right.y);
  assert(r1->top_left.x < r1->bottom_right.x);
  assert(r1->top_left.y > r1->bottom_right.y);

  int top_left_x = (r0->top_left.x == r1->top_left.x);
  int top_left_y = (r1->top_left.y == r0->top_left.y);
  int bot_rigt_x = (r0->bottom_right.x == r1->bottom_right.x);
  int bot_rigt_y = (r1->bottom_right.y == r0->bottom_right.y);
  return (top_left_x && top_left_y && bot_rigt_x && bot_rigt_y);
}

// Here are some functions to use as function pointers.
// Do not modify width_rectangle, height_rectangle, or area_rectangle

// width_rectangle(r) Find the width of r.
int width_rectangle(const struct rectangle* r) {
	return abs(r->bottom_right.x - r->top_left.x);
}

// height_rectangle(r) Find the height of r.
int height_rectangle(const struct rectangle* r) {
	return abs(r->top_left.y - r->bottom_right.y);
}

// area_rectangle(r) Calculate the area of r.
int area_rectangle(const struct rectangle* r) {
	return width_rectangle(r) * height_rectangle(r);
}

// swap_greater(r0, r1, f) returns the rectangle, r0 for which the f 
//  returns a greater value, and r1 for the one with the lesser value
// requires: r0, r1, f are all valid pointers and not null
//           r0.top_left.x < r0.bottom_right.x && 
//           r0.top_left.y > r0.bottom_right.y
//           r1.top_left.x < r1.bottom_right.x && 
//           r1.top_left.y > r1.bottom_right.y
// side effects: modifies r0 and r1
void swap_greater(struct rectangle* const r0, 
                 struct rectangle* const r1,
                 int (*f)(const struct rectangle*)) {
  assert(f);
  assert(r0);
  assert(r1);
  assert(r0->top_left.x < r0->bottom_right.x);
  assert(r0->top_left.y > r0->bottom_right.y);
  assert(r1->top_left.x < r1->bottom_right.x);
  assert(r1->top_left.y > r1->bottom_right.y);
  
  if(f(r0) >= f(r1)) {
    return;
  }
  else {
    struct rectangle temp_rect0 = *r0;
    *r0 = *r1;
    *r1 = temp_rect0;
  }
}

int main(void) {
  const struct rectangle t0_orig = {{10,13}, {15,12}};
  const struct rectangle t1_orig = {{5,11}, {7,8}};
  struct rectangle t0 = t0_orig;
  struct rectangle t1 = t1_orig;
  
  // A few tests for rect_equal
  assert(rectangle_equal(&t0_orig, &t0));
  assert(rectangle_equal(&t1_orig, &t1));
  assert(!rectangle_equal(&t1_orig, &t0));
  assert(!rectangle_equal(&t0_orig, &t1));
  
  
  // Now tests for swap_greater:
  
  // t1 has greater area:
  t0 = t0_orig;
  t1 = t1_orig;
  swap_greater(&t0, &t1, &area_rectangle);
  //assert(rectangle_equal(&t0, &t1_orig));
  //assert(rectangle_equal(&t1, &t0_orig));

  // t0 has greater width:
  t0 = t0_orig;
  t1 = t1_orig;
  swap_greater(&t0, &t1, &width_rectangle);
  //assert(rectangle_equal(&t0, &t0_orig));
  //assert(rectangle_equal(&t1, &t1_orig));

  // t1 has greater height:
  t0 = t0_orig;
  t1 = t1_orig;
  swap_greater(&t0, &t1, &height_rectangle);
  //assert(rectangle_equal(&t0, &t1_orig));
  //assert(rectangle_equal(&t1, &t0_orig));
}
// IF THEY ARE EQUAL PREFER THE OLDER ONE
