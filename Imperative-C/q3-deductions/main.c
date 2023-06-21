#include "cs136.h"

// base_hundred(base, remainder_base) calculates the base in cents with 
//  remainder, so the base can have a "00" ending 
//  requires: base >= 0
int base_hundred(int base, int remainder_base) {
  assert(base >= 0);
  return (base - remainder_base);
}

// calculate_federal_taxes(base) calculates the federal taxes of [base] in cents
//  where base is the pay in cents
//  requires: base >= 0
int calculate_federal_taxes(int base) {
  assert(base >= 0);
  int indicator = 0;
  int remainder_base = base % 100;
  const int bracket1 = (4902000 / 100 * 15);
  const int bracket2 = ((9804000-4902000) / 1000 * 205);
  const int bracket3 = ((15197800-9804000) / 100 * 26);
  const int bracket4 = ((21651100-15197800) / 100 * 29);
  base = base_hundred(base, remainder_base);
  if (4902000 >= base){
    indicator = 1;
    base = base / 100 * 15;
  } else if (4902100 <= base && base <= 9804000) {
    indicator = 2;
    base =  bracket1 + ((base - 4902000) / 1000 * 205);
  } else if (9804100 <= base && base <= 15197800) {
    indicator = 3;
    base = bracket1 + bracket2 + ((base - 9804000) / 100 * 26);
  } else if (15197900 <= base && base <= 21651100) {
    indicator = 4;
    base = bracket1 + bracket2 + bracket3 + 
                  ((base - 15197800) / 100 * 29);
  } else {
    indicator = 5;
    base = bracket1 + bracket2 + bracket3 + bracket4 + 
                  ((base - 21651100) / 100 * 33);
  }
  
  if (indicator == 1) {
    remainder_base = remainder_base * 15 / 100;
  } else if (indicator == 2) {
    remainder_base = (remainder_base * 20 / 100) +
                     (remainder_base * 5 / 100);
  } else if (indicator == 3) {
    remainder_base = remainder_base * 26 / 100;
  } else if (indicator == 4) {
    remainder_base = remainder_base * 29 / 100;
  } else {
    remainder_base = remainder_base * 33 / 100;
  }
  
  return remainder_base + base;
}

// calculate_premiums(base) calcualte the CPP and EI premiums of [base] in cents
//  of the base pay in cents
//  requires: base >= 0
int calculate_premiums(int base) {
  assert(base >= 0);
  int cpp = base / 10000 * 570 + (base % 10000 * 570) / 10000;
  int ei = base / 10000 * 158 + (base % 10000 * 158) / 10000;
  return cpp + ei;
}

// print_int_coma(n) prints out a number with commas after 3 integers
//  requires: base >= 0
//  effects: produces output
int print_int_comma (int n, int counter) {
  if (n < 1000) {
    printf ("%d", n);     
  } else {
    ++counter;
    print_int_comma(n/1000, 0);
    printf(",%03d", n%1000);
  }
  return counter;
}

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

// digits(dig) calculates the number of digits in [dig]
int digits(int dig) {
  if (dig < 10) {
    return 1;
  } else {
    return 1 + digits(dig/10);
  }
}

// decimal(dec) prints out the last 2 digits (i.e the decimals) of [dec] 
//  requires: dec >= 0
//   effects: produces output
void decimal(int dec) {
  int last_decimal = dec % 10;
  dec = dec / 10;
  int first_decimal = dec % 10;
  printf("%d%d", first_decimal, last_decimal);
}

// output_pay(base) prints the base pay, the federal taxes, and the premiums.
//  requires: base >= 0
//   effects: produces output
void output_pay(int base) {
  assert(base >= 0);
  int federal_taxes = calculate_federal_taxes(base);
  int premiums = calculate_premiums(base);
  
  int feds_d = digits(federal_taxes);
  int prem_d = digits(premiums);
  
  int max_length = digits(base) + (digits(base) - 3)  / 3 + 1;
  int space_f = feds_d  + (feds_d - 3)  / 3 + 1;
  int space_p = prem_d  + (prem_d - 3)  / 3 + 1;
  
  if(max_length < 4){
    max_length = 4;
  }
  
  if(space_f < 4){
    space_f = 4;
  }
  
  if(space_p < 4){
    space_p = 4;
  }
 
  printf("$ ");
  print_int_comma(base/100, 0);
  printf(".");
  decimal(base);
  printf(" Base Pay\n");
  printf("$ ");
  draw_spaces(max_length - space_f);
  print_int_comma(federal_taxes/100, 0);
  printf("."); 
  decimal(federal_taxes);
  printf(" Federal Taxes\n");
  printf("$ ");
  draw_spaces(max_length - space_p);
  print_int_comma(premiums/100, 0);
  printf(".");
  decimal(premiums);
  printf(" CPP and EI Premiums\n\n");
}

/////////////////////////////////////////////
// DO NOT MODIFY THE CODE BELOW
/////////////////////////////////////////////
// read_int_rec() reads from input and outputs the
//   results from output_pay()
// effects: reads input
//          produces output
void read_int_rec(void) {
  int n = read_int();
  if (n == READ_INT_FAIL) {
    return;
  }
  else {
    output_pay(n);
    read_int_rec();
  }
}

int main(void) {
 read_int_rec();
}
