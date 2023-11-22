#include <stdio.h>
#include <assert.h>

#include "sudoku.h"

void printBinary(int num) {
    for (int i = 8 * sizeof(int) - 1; i >= 0; --i) {
        printf("%d", (num >> i) & 1);
    }
}

int main() {
    // Test case 1
    int board1[] = {1, 2, 3, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int y1 = 0, axis1 = VERTICAL;
    int result1 = axismissing(board1, y1, axis1);
    int expected1 = 511 ^ 0b000001110;  // digits: 1, 2, 3 (count starts from 0)
    assert(result1 == expected1);

    // Test case 2
    int board2[] = {-1, -1, 3, 4, -1, 6, 7, 8, 9,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int x2 = 3, axis2 = HORIZONTAL;
    int result2 = axismissing(board2, x2, axis2);
    int expected2 = 511 ^ 0b000010000;  // digits: 4
    assert(result2 == expected2);

    // Test case 3
    int board3[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, 6, 7, -1, -1, -1, -1,
                    -1, -1, -1, 3, 4, 5, -1, -1, -1,
                    -1, -1, -1, 0, 1, 2, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1};;
    int x3 = 4, axis3 = BLOCK;
    int result3 = axismissing(board3, x3, axis3);
    int expected3 = 511 ^ 0b011111111;  // missing: 9
    assert(result3 == expected3);

    return 0;
}
