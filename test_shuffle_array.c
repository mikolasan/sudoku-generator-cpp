#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sudoku.h"

void printArray(int arr[], int length) {
    printf("[");
    for (int i = 0; i < length; ++i) {
        printf("%d", arr[i]);
        if (i < length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int arraysEqual(int arr1[], int arr2[], int length) {
    for (int i = 0; i < length; ++i) {
        if (arr1[i] != arr2[i]) {
            return 0;  // Not equal
        }
    }
    return 1;  // Arrays are equal
}

int main() {
    // Test case 1
    enum { length1 = 5 };
    int arr1[] = {1, 2, 3, 4, 5};
    int original1[length1];
    for (int i = 0; i < length1; ++i) {
        original1[i] = arr1[i];
    }

    shuffleArray(arr1, length1);
    printArray(arr1, length1);

    // Check that the array is shuffled
    assert(arraysEqual(arr1, original1, length1) == 0);

    // Test case 2
    enum { length2 = 3 };
    int arr2[] = {10, 20, 30};
    int original2[length2];
    for (int i = 0; i < length2; ++i) {
        original2[i] = arr2[i];
    }

    shuffleArray(arr2, length2);
    printArray(arr2, length2);

    // Check that the array is shuffled
    assert(arraysEqual(arr2, original2, length2) == 0);

    return 0;
}
