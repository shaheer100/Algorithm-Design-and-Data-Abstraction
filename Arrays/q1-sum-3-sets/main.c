#include "cs136-trace.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
    int array[1000] = {}; //maximum elements in one array
    int n = 0;
    assert(scanf("%d", &n) == 1); //ensure it reads n in properly
    assert(n > 0); //n is positive

    int input = 0;
    int count = 0;
    while (scanf("%d", &input) != -1) {
        if (count == n){
            count = 0;
        }
        for (int i = 0; i < n; i++) {
            if (count == i) {
                array[i] += input;
            }
        }
        
        ++count; 
    }
    //prints the sums
    for (int j = 0; j < n; j++) {
        printf("%d\n", array[j]);
    }
}
