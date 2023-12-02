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
    int x3 = 4, axis3 = SQUARE;
    int result3 = axismissing(board3, x3, axis3);
    int expected3 = 511 ^ 0b011111111;  // missing: 9
    assert(result3 == expected3);

    int board4[] = 
    {
        6, -1, -1, -1, 8, -1, -1, 0, -1,
        1, 5, 3, -1, 4, -1, -1, -1, 8,
        8, -1, -1, -1, -1, -1, -1, -1, 6,
        -1, -1, -1, -1, -1, 1, 4, 6, 2,
        -1, -1, -1, -1, -1, 4, 7, 3, 5,
        -1, 7, -1, 2, -1, 5, -1, -1, -1,
        5, -1, 8, -1, 2, -1, 6, -1, -1,
        -1, 3, 2, 1, 7, -1, -1, 5, 0,
        -1, 1, -1, 0, 5, -1, 3, -1, -1
    };
    // Solution:
    // int board4[] = 
    // {
    //     6, 4, 7, 5, 8, 2, 1, 0, 3,
    //     1, -1, 3, 6, 4, 0, 2, 7, 8,
    //     8, 2, 0, 3, 1, 7, 5, 4, 6,
    //     0, 8, 5, 7, 3, 1, 4, 6, 2,
    //     2, 6, 1, 8, 0, 4, 7, 3, 5,
    //     3, 7, 4, 2, 6, 5, 0, 8, 1,
    //     5, 0, 8, 4, 2, 3, 6, 1, 7,
    //     4, 3, 2, 1, 7, 6, 8, 5, 0,
    //     7, 1, 6, 0, 5, 8, 3, 2, 4};
    int available[27] = {0};
    for (int axis = 0; axis < 3; axis++)
    {
        for (int x = 0; x < SIDE_SIZE; x++)
        {
            int bits = axismissing(board4, x, axis);
            available[axis * SIDE_SIZE + x] = bits;
            // int numbers[SIDE_SIZE] = {0};
            // listbits(bits, numbers);
            // printf("%d: ", x + 1);
            // for (int i = 0; i < SIDE_SIZE; ++i)
            // {
            //     printf("%d ", numbers[i]);
            // }
            // printf("\n");
        }
    }

    printf("----------\n");
    int n_singles = 0;
    for (int k = 0; k < BOARD_SIZE; ++k)
    {
        if (board4[k] > -1) continue;

        int x = k % SIDE_SIZE;
        int y = k / SIDE_SIZE;
        int block_x = x / 3;
        int block_y = y / 3;
        int row_id = y;
        int column_id = SIDE_SIZE + x;
        int block_id = 18 + block_y * 3 + block_x;
        int cross = available[row_id] & available[column_id] & available[block_id];
        int numbers[SIDE_SIZE] = {0};
        int size = listbits(cross, numbers);
        if (size == 1)
        {
            n_singles++;
        }
        printf("%d [%d,%d,%d](%d): ", k + 1, row_id, column_id, block_id, size);
        for (int i = 0; i < SIDE_SIZE; ++i)
        {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }
    printf("singles: %d\n", n_singles);

    assert(n_singles == count_singles(board4));

    return 0;
}
