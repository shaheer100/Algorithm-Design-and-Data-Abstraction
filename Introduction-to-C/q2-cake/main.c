#include "cs136.h"

// away_div(num, denom) calculates the result of the integer division
//  between [num] and [denom], but instead of rounding towards 0,
// requires: denom is not zero, denom != 0
int away_div(int num, int denom) {
  assert(denom != 0);
  if (num == 0) {
    return 0;
  } else if (num % denom == 0) {
    return num / denom;
  } else if ((num > 0 && denom < 0) || (num < 0 && denom > 0)) {
    return num / denom - 1;
  } else {
    return num / denom + 1;
  }
}

// num_cakes(gf, chocholate, vanilla, lemon, pieces_per_cake) 
//   calculates the minimum number of cakes needed for a party, 
//   provided people specify how much pieces they want of each cake.
// requires: gf, chocolate, vanilla, lemon, >= 0
//           pieces_per_cake > 0
int num_cakes(int gf, int chocolate, int vanilla, int lemon, 
              int pieces_per_cake) {
  assert(gf >= 0);
  assert(chocolate >= 0);
  assert(vanilla >= 0);
  assert(lemon >= 0);
  assert(pieces_per_cake > 0);
  return away_div(gf, pieces_per_cake) + 
         away_div(chocolate, pieces_per_cake) +
         away_div(vanilla, pieces_per_cake) +
         away_div(lemon, pieces_per_cake);
}

// num_cakes_v2(gf, chocolate, vanilla, lemon, pieces_per_cake) 
//   still calculates minimum number of cakes needed for a party,
//   however you can now order half-and-half cakes.
// requires: gf, chocolate, vanilla, lemon, >= 0
//           pieces_per_cake > 0 and pieces_per_cake % 2 == 0
//           gluten cannot be added with other cakes.
int num_cakes_v2(int gf, int chocolate, int vanilla, int lemon, 
                 int pieces_per_cake)  {
  assert(gf >= 0);
  assert(chocolate >= 0);
  assert(vanilla >= 0);
  assert(lemon >= 0);
  assert(pieces_per_cake > 0);
  assert(pieces_per_cake % 2 == 0);
  
  int half_cakes = pieces_per_cake / 2;
  
  int gf_pieces = away_div(gf, pieces_per_cake);
  
  int chocolate_halves = away_div(chocolate, half_cakes); 
  int vanilla_halves = away_div(vanilla, half_cakes);
  int lemon_halves = away_div(lemon, half_cakes);
  
  return gf_pieces + away_div(chocolate_halves + vanilla_halves + 
                              lemon_halves, 2);
}

int main(void) {
  assert(away_div(39, 10) == 4);
  assert(num_cakes(0, 1, 6, 4, 4) == 4);
  assert(num_cakes_v2(1, 2, 6, 2, 4) == 4);
  
  // add more asserts below to test your code
  
  assert(away_div(1, 4) == 1);
  assert(away_div(180, 59) == 4);
  assert(away_div(180, 61) == 3);
  assert(away_div(10, 3) == 4);
  assert(away_div(0, 10) == 0);
  assert(away_div(20, 3) == 7);
  assert(away_div(-20, -3) == 7);
  assert(away_div(-20, 3) == -7);
  assert(away_div(-20, 2) == -10);
  assert(num_cakes(10, 10, 12, 13, 4) == 13);
  assert(num_cakes(3, 5, 7, 9, 2) == 14);
  assert(num_cakes_v2(12, 12, 16, 2, 4) == 11); // 3 + 3 + 4 + 1
  assert(num_cakes_v2(17, 12, 16, 7, 8) == 8); // 3 + 1 + 2 + 2
  assert(num_cakes_v2(1, 3, 6, 1, 4) == 4); // 1 + 1 + 2
  
  assert(num_cakes_v2(1, 1, 3, 4, 8) == 3); // 1 + 1 + 1
  assert(num_cakes_v2(1, 9, 9, 9, 8) == 6); // 3 + 3
  assert(num_cakes_v2(1, 2, 0, 5, 2) == 5); // 2 + 3
  assert(num_cakes_v2(0, 3, 1, 0, 4) == 2); // 1 + 1
  assert(num_cakes_v2(2, 3, 4, 5, 2) == 7);
  assert(num_cakes_v2(0, 1, 6, 4, 4) == 3);
}
