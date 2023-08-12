/////////////////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v4)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement posted on edX:
// (Course > Assignments > Assignment Information & Policies > Academic Integrity Policy)
/////////////////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with:

// no one.
//
// Name: shaheer sheeraz
// login ID: ssheeraz
//////////////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "cs136-trace.h"

// is_valid_password(s) determins if s is a valid password, according to the usual rules;
//   where a password has at least 8 characters, no whitespace or non-printable chars,
//   and at least one of each: upper case, lower case, special character, and digit.
// requires: s is a valid pointer not to NULL
// Time: O(n), where n is the length of the string s
// Justification: 
// strlen(n) = O(n) since it will go through each element in the string array. Iterating
//   through the array while checking for valid passwords will also result in O(n):
// Loop: Sum[i=0..i=n-1]: O(1)
//            = O(n)
bool is_valid_password(const char *s){
  assert(s);

  int len = strlen(s);
  int min_len = 8;

  char first_printable = '!';
  char last_printable = '~';
  char first_digit = '0';
  char last_digit = '9';
  char first_lower = 'a';
  char last_lower = 'z';
  char first_upper = 'A';
  char last_upper = 'Z';

  bool char_flag = 0;
  bool dig_case = 0;
  bool lower_case = 0;
  bool upper_case = 0;
  bool special_case = 0;

  for (const char *p = s; p < s + len; ++p) {
    if (first_printable > *p || last_printable < *p) { //no whitespace/non-printable 
      return false;
    }
    
    if (len >= min_len) { //at least 8 characters
      char_flag = 1;
    }

    if (first_digit <= *p && *p <= last_digit) { //at least one digit
      dig_case = 1;
    }

    if (first_lower <= *p && *p <= last_lower) { //at least one lower case letter
      lower_case = 1;
    }

    if (first_upper <= *p && *p <=last_upper) { //at least one upper case letter
      upper_case = 1;
    }

    if ((first_printable <= *p && *p < first_digit) || 
        (last_digit < *p && *p < first_upper) ||
        (last_upper < *p && *p < first_lower) ||
        (last_lower < *p && *p <= last_printable)) { //at least one special character
      special_case = 1;
    }
  }

  return char_flag && upper_case && lower_case && dig_case && special_case;
}

int main(void){
  assert(is_valid_password("Tru$tNo1"));
  assert(!is_valid_password("trustno1"));
  // add tests!
  trace_msg("ALL ASSERTIONS PASSED!")
}
