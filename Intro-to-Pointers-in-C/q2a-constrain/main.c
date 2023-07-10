// constrain(x, y, r) It "constrains" the point (x,y) to be inside or on the 
//  border of the rectangle r.
// requires: top_left.x <= bottom_right.x
//           top_left.y >= bottom_right.y
//           x,y,r are all not null.
// side effects: modifies *x and *y.
bool constrain(int* x, int* y, const struct rectangle* r) {
  assert(x);
  assert(y);
  assert(r);
  assert(r->top_left.x <= r->bottom_right.x);
  assert(r->top_left.y >= r->bottom_right.y);
  bool retval = false;
  
  if (*x < r->top_left.x){
    *x = r->top_left.x;
    retval = true;
  } 
  else if (r->bottom_right.x < *x){
    *x = r->bottom_right.x;
    retval = true;
  }
  
  if (r->top_left.y < *y){
    *y = r->top_left.y;
    retval = true;
  }
  else if (*y < r->bottom_right.y){
    *y = r->bottom_right.y;
    retval = true;
  }
  return retval;
}
