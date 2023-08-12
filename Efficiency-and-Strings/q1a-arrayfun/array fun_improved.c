/////////////////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v4)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement posted on edX:
// (Course > Assignments > Assignment Information & Policies > Academic Integrity Policy)
/////////////////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with:

// Module 6.3, Example 6.3.4 - BINARY SEARCH ALGORITHM (find(item, a, len)).
//
// Name: shaheer sheeraz
// login ID: ssheeraz
//////////////////////////////////////////////////////////////////////////////////////////

#include "arrayfun_improved.h"
#include <assert.h>

// see arrayfun_improved.h for documentation
int divides_followers(const int a[], int n) {
  assert(a);
  assert(n > 1);

  int sum = 0;
  int count = 0;

  //starting from the last element in the array, sum up and check for each iteration
  for (const int *p = a + n - 1; p >= a ; --p) {
    sum += *p;
    if (*p != 0 && sum % *p == 0) {
      ++count;
    }
  }

  return count;
}	

// find_sorted(item, a, len) finds the index of item in a,
//   or returns -1 if it does not exist
// requires: a is sorted in ascending order [not asserted]
//           len > 0
// time: O(log n)
static int find_sorted(int item, const int a[], int len) {
  assert(a);
  assert(len > 0); 
  int low = 0;
  int high = len - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (a[mid] == item) {
      return mid;
    } else if (a[mid] < item) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

// see arrayfun_improved.h for documentation
bool consec_sum(const int a[], int n, const int b[], int m) {
  assert(a);
  assert(b);
  assert(n > 1);
  assert(m > 1);

  //sums the first 2 elements of the array up and searchs for them using binary search
  //which is O(logm)
  //O(n) * O(logm) = O(n*logm)
  for (const int *p = a; p < a + n; ++p) {
    int sum = 0;
    sum = *p + *(p + 1);
    if (find_sorted(sum, b, m) == -1) {
      continue;
    } else {
      return true;
    }
  }
  return false;
}

// see arrayfun_improved.h for documentation
void even_first(int a[], int n) {
  assert(a);
  assert(n > 1);

  int *pos = a + n - 1; //pointer to the last element

  //if element is odd swap with last, if element swapped in is odd, swap with second
  //last, move on to next element if even
  for (int *p = a; p < a + n;) {
    if (*pos == *p) {
      break;
    }
    
    if (*p % 2 == 1) {
      int temp = *p;
      *p = *pos;
      *pos = temp;
      --pos;
      continue;
    } else {
      ++p;
    }
  }
}
