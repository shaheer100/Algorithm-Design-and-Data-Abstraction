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

#include "next_ten_greater.h"
#include <assert.h>

// Assume this is the maximum array length (if you want/need it)
const int MAX_LEN = 10000;

int next_ten_greater(const int arr[], int len, int value, int result[]) {
  assert(len > 0);
  assert(arr);
  assert(result);
  int my_array[10000] = {};

  //copying the array
  for (int k = 0; k < len; ++k) {
    my_array[k] = arr[k];
  }

  //sort the array
  for (int i = 0; i < len - 1; ++i) {
    for (int j = i + 1; j < len; ++j) {
      if (my_array[j] < my_array[i]) {
        int temp = my_array[j];
        my_array[j] = my_array[i];
        my_array[i] = temp;
      }
    }
  }

  //placing elements into result
  int m = 0;
  for (int l = 0; l < len; ++l) {
    if (!(m < 10)) {
      break; //if result is greater than 10 break!
    }
    if (value < my_array[l]) {
      result[m] = my_array[l];
      ++m;
    }
  }
  return m; //return number of elements placed in result
}
