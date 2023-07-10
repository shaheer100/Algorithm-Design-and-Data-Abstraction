#include "cs136.h"

struct point {
	int x;
	int y;
};

struct rectangle {
	struct point top_left;
	struct point bottom_right;
};

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

// update_rectangle(x_left, y_top, x_right, y_bottom, bounds) updates the bounds
//  i.e the rectangle
// requires: top_left.x <= bottom_right.x
//           top_left.y >= bottom_right.y
//           bounds is not null.
// side effects: modfies bound
void update_rectangle(int x_left, int y_top, int x_right, int y_bottom,
                      struct rectangle *bounds) {
  assert(bounds);
  assert(bounds->top_left.x <= bounds->bottom_right.x);
  assert(bounds->top_left.y >= bounds->bottom_right.y);
  
  bounds->top_left.x = x_left;
  bounds->top_left.y = y_top;
  bounds->bottom_right.x = x_right;
  bounds->bottom_right.y = y_bottom;
}

// reset_robot(x, y, robot) resets the robot according to [x] and [y]
// requires: robot is not null
// side effects: modfies robot
void reset_robot(int x, int y, struct point *robot) {
  assert(robot);
  robot->x = x;
  robot->y = y;
}

// update_robot(x, y, robot) updates the current point of the robot
// requires: robot is not null
// side effects: modfies robot
void update_robot(int x, int y, struct point *robot) {
  assert(robot);
  robot->x += x;
  robot->y += y;
}

// drive_robot() reads a series of commands that allows you to control a robot
//  around a rectangular enclosure, R resets environment [bounds] and the 
//  [robot], ? prints the robots current position, and the [robot] moves with
//  directions to N, W, E, S.
// side effects: reads input
//               prints output
void drive_robot(void) {
  char command = '0';
  int x_left = 0;
  int y_top = 0;
  int x_right = 0;
  int y_bottom = 0;
  int x = 0;
  int y = 0;
  struct rectangle bounds = {};
  struct point robot = {};
  int move = 0;
  int stuck = 1;
  int *boolean = &stuck;
  
  while (1) {
    int retval = 0;
    retval = scanf(" %c", &command);
    
    if (retval == -1){
      break;
    }
    
    if (command == 'R') {
      scanf("%d", &x_left);
      scanf("%d", &y_top);
      scanf("%d", &x_right);
      scanf("%d", &y_bottom);
      scanf("%d", &x);
      scanf("%d", &y);
      update_rectangle(x_left, y_top, x_right, y_bottom, &bounds);
      reset_robot(x, y, &robot);
      *boolean = 1;
      continue;
    }
    else if (command == '?') {
      printf("%d", robot.x);
      printf(" ");
      printf("%d\n", robot.y);
      continue;
    }
    else if (command == 'N' && stuck == 1) {
      scanf("%d", &move);
      update_robot(0, move, &robot);
      *boolean = !constrain(&(robot.x), &(robot.y), &bounds);
      continue;
    }
    else if (command == 'S' && stuck == 1) {
      scanf("%d", &move);
      update_robot(0, -move, &robot);
      *boolean = !constrain(&(robot.x), &(robot.y), &bounds); 
      continue;
    }
    else if (command == 'E' && stuck == 1) {
      scanf("%d", &move);
      update_robot(move, 0, &robot);
      *boolean = !constrain(&(robot.x), &(robot.y), &bounds); 
      continue;
    }
    else if (command == 'W' && stuck == 1) {
      scanf("%d", &move);
      update_robot(-move, 0, &robot);
      *boolean = !constrain(&(robot.x), &(robot.y), &bounds); 
      continue;
    }
  }
  return;
}

int main(void) {
  // assert tests:
  int xt = 0, yt = 0;
  struct rectangle test_rect = {{-4, 3}, {4, -3}};
  
  xt = 2;
  yt = 1;
  assert(!constrain(&xt, &yt, &test_rect));  // already inside
  assert(xt == 2 && yt == 1);  // location unchanged
  
  xt = 10;
  yt = 1;
  assert(constrain(&xt, &yt, &test_rect));  // starts outside, so mutate
  assert(xt == 4 && yt == 1);  // now at nearest point

  xt = -20;
  yt = 20;
  assert(constrain(&xt, &yt, &test_rect));  // starts outside, so mutate
  assert(xt == -4 && yt == 3);  // now at nearest point

  // Add assert based tests here.
  // Do not otherwise change the main function.
  // Put all I/O in your function(s).

  drive_robot();   // start the process for I/O tests.
}
