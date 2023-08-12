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
// Name: shaheer sheeraz.
// login ID: ssheeraz
//////////////////////////////////////////////////////////////////////////////////////////

#include "next_ten_greater.h"
#include <assert.h>

// for documentation see [next_ten_greater.h]

// Assume this is the maximum array length (if you want/need it)
const int MAX_LEN = 10000;

// time: O(n)
//   justification: (n) for nested loops AND 
//                  assume len, length = n (length of array) since
//                  length <= len
//       First Loop: Sum[i=0..i=n-1] O(1) = O(n)
//  (n)  Inner Loop: Sum[k=0..k=n-1]: O(1) = O(n)
//  (n)  Outer Loop: Sum[j=0..j=9]: O(n) = O(n), this is O(10) * O(n) = O(n)
//       Last Loop:  Sum[m=0..m=n-1] O(1) = O(n)
// summing everything we have: O(n) + O(n) + O(n) = O(n) efficiency 
int next_ten_greater(const int arr[], int len, int value, int result[]) {
  assert(len > 0);
  assert(arr);
  assert(result);
  
  int my_array[10000] = {};
  int length = 0;

  for (int i = 0; i < len; ++i) { //going through array O(len)
    if (value < arr[i]) {
      my_array[length] = arr[i];
      ++length;
    }
  }

  for (int j = 0; j < 10; ++j) { //max of 10 iterations (sort smallest 10)
    int pos = j;
    for (int k = j + 1; k < length; ++k) {
      if (my_array[pos] > my_array[k]) {
        pos = k;
      }
    }
    int temp = my_array[pos];
    my_array[pos] = my_array[j];
    my_array[j] = temp;
  }

  int count = 0;
  for (int m = 0; m < length; ++m) { //going through array of length len O(n)
    if (!(count < 10)) {
      break;
    }
    result[count] = my_array[m];
    ++count;
  }

  return count;
}
