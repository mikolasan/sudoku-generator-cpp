#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sudoku.h"

int main() {
    // Test case 1
    enum { length1 = 5 };
    const int value1 = 10;
    int arr1[length1];
    makeArray(arr1, length1, value1);

    for (int i = 0; i < length1; ++i) {
        assert(arr1[i] == value1);
    }

    // Test case 2
    enum { length2 = 3 };
    const int value2 = -5;
    int arr2[length2];
    makeArray(arr2, length2, value2);

    for (int i = 0; i < length2; ++i) {
        assert(arr2[i] == value2);
    }

    return 0;
}
