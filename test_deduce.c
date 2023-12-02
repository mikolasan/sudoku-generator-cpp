#include <stdio.h>
#include <assert.h>

#include "sudoku.h"

void printBoard(int board[]) {
    for (int i = 0; i < SIDE_SIZE; ++i) {
        for (int j = 0; j < SIDE_SIZE; ++j) {
            printf("%2d ", board[i * SIDE_SIZE + j]);
        }
        printf("\n");
    }
}

int main() {
    // Test case 1: Solvable Sudoku puzzle
    int board1[] = {5, 3, -1, -1, 7, -1, -1, -1, -1,
                    6, -1, -1, 1, 0, 5, -1, -1, -1,
                    -1, 0, 8, -1, -1, -1, -1, 6, -1,
                    8, -1, -1, -1, 6, -1, -1, -1, 3,
                    4, -1, -1, 8, -1, 3, -1, -1, 1,
                    7, -1, -1, -1, 2, -1, -1, -1, 6,
                    -1, 6, -1, -1, -1, -1, 2, 8, -1,
                    -1, -1, -1, 4, 1, 0, -1, -1, 5,
                    -1, -1, -1, -1, 8, -1, -1, 7, 0};

    // int board1[] = {
    //     5,  3, -1,  6,  7,  8, -1,  1, -1,
    //     6,  7, -1,  1,  0,  5,  3, -1,  8,
    //     1,  0,  8,  3,  4,  2,  5,  6,  7,
    //     8, -1, -1, -1,  6, -1, -1, -1,  3,
    //     4, -1,  6,  8, -1,  3,  7, -1,  1,
    //     7, -1,  3, -1,  2, -1,  8, -1,  6,
    //     0,  6,  1, -1,  3, -1,  2,  8,  4,
    //     2,  8,  7,  4,  1,  0,  6,  3,  5,
    //     -1, -1, -1, -1,  8,  6,  1,  7,  0
    // };
    printf("Original Board:\n");
    printBoard(board1);

    Guess *guesses = NULL;
    int guess_size = 0;
    deduce(board1, &guesses, &guess_size);

    printf("\nNext step Board:\n");
    printBoard(board1);

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        assert(board1[i] > -1);
    }
    assert(guesses == NULL);
    assert(guess_size == 0);

    return 0;
}
