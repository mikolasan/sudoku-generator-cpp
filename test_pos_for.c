#include <stdio.h>
#include <assert.h>

#include "sudoku.h"

int main() {
    // Test case 1
    int x1 = 2, y1 = 3, axis1 = VERTICAL;
    int result1 = posfor(x1, y1, axis1);
    int expected1 = x1 * 9 + y1;
    assert(result1 == expected1);

    // Test case 2
    int x2 = 4, y2 = 1, axis2 = HORIZONTAL;
    int result2 = posfor(x2, y2, axis2);
    int expected2 = y2 * 9 + x2;
    assert(result2 == expected2);

    // Test case 3
    int x3 = 1, y3 = 2, axis3 = BLOCK;
    int result3 = posfor(x3, y3, axis3);
    int expected3 = 27 * (x3 / 3) + 3 * (x3 % 3) + 9 * (y3 / 3) + (y3 % 3);
    assert(result3 == expected3);

    return 0;
}
