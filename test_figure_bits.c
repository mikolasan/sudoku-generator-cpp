#include <stdio.h>
#include <assert.h>

#include "sudoku.h"

void printBinary(int num) {
    for (int i = SIDE_SIZE - 1; i >= 0; --i) {
        printf("%d", (num >> i) & 1);
    }
}

int main() {
    // Test case 1
    int board1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int allowed1[BOARD_SIZE], needed1[27];
    figurebits(board1, allowed1, needed1);

    // Check allowed and needed arrays
    // allowed = 000000000 000000000 000000000 000000000 000000000 000000000 000000000 000000000 000000000 111110001 111110001 111110001 110001111 110001111 110001111 001111110 001111110 001111110 111110001 111110001 111110001 110001111 110001111 110001111 001111110 001111110 001111110 111111101 111111011 111110111 111101111 111011111 110111111 101111111 011111111 111111110 111111101 111111011 111110111 111101111 111011111 110111111 101111111 011111111 111111110 111111101 111111011 111110111 111101111 111011111 110111111 101111111 011111111 111111110 111111101 111111011 111110111 111101111 111011111 110111111 101111111 011111111 111111110 111111101 111111011 111110111 111101111 111011111 110111111 101111111 011111111 111111110 111111101 111111011 111110111 111101111 111011111 110111111 101111111 011111111 111111110 
    // needed = 000000000 111111111 111111111 111111111 111111111 111111111 111111111 111111111 111111111 111111101 111111011 111110111 111101111 111011111 110111111 101111111 011111111 111111110 111110001 110001111 001111110 111111111 111111111 111111111 111111111 111111111 111111111 
    // for (int i = 0; i < BOARD_SIZE; ++i) {
    //     printBinary(allowed1[i]);
    //     printf(" ");
    // }
    // printf("\n");

    // for (int i = 0; i < 27; ++i) {
    //     printBinary(needed1[i]);
    //     printf(" ");
    // }
    // printf("\n");
    for (int i = 0; i < SIDE_SIZE; ++i) {
      assert(allowed1[0] == 0);
    }
    assert(needed1[0] == 0);

    // Test case 2
    int board2[] = {1, -1, 3, 4, -1, 6, 7, 8, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int allowed2[BOARD_SIZE], needed2[27];
    figurebits(board2, allowed2, needed2);

    // Check allowed and needed arrays
    // allowed = 000000000 000100101 000000000 000000000 000100101 000000000 000000000 000000000 000000000 111110101 111110101 111110101 110101111 110101111 110101111 001111111 001111111 001111111 111110101 111110101 111110101 110101111 110101111 110101111 001111111 001111111 001111111 111111101 111111111 111110111 111101111 111111111 110111111 101111111 011111111 111111111 111111101 111111111 111110111 111101111 111111111 110111111 101111111 011111111 111111111 111111101 111111111 111110111 111101111 111111111 110111111 101111111 011111111 111111111 111111101 111111111 111110111 111101111 111111111 110111111 101111111 011111111 111111111 111111101 111111111 111110111 111101111 111111111 110111111 101111111 011111111 111111111 111111101 111111111 111110111 111101111 111111111 110111111 101111111 011111111 111111111 
    // needed = 000100101 111111111 111111111 111111111 111111111 111111111 111111111 111111111 111111111 111111101 111111111 111110111 111101111 111111111 110111111 101111111 011111111 111111111 111110101 110101111 001111111 111111111 111111111 111111111 111111111 111111111 111111111
    // for (int i = 0; i < BOARD_SIZE; ++i) {
    //     printBinary(allowed2[i]);
    //     printf(" ");
    // }
    // printf("\n");

    // for (int i = 0; i < 27; ++i) {
    //     printBinary(needed2[i]);
    //     printf(" ");
    // }
    // printf("\n");
    assert(allowed2[1] == 0b000100101);
    assert(allowed2[4] == 0b000100101);
    assert(allowed2[8] == 0b000100101);
    assert(needed2[0] == 0b000100101);

    return 0;
}
