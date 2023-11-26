#include <stdio.h>
#include <assert.h>

#include "sudoku.h"

void printBoard(int board[]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            printf("%2d ", board[i * 9 + j]);
        }
        printf("\n");
    }
}

int main() {
    // Test case 1: Solvable Sudoku puzzle
    // int board1[] = {5, 3, -1, -1, 7, -1, -1, -1, -1,
    //                 6, -1, -1, 1, 9, 5, -1, -1, -1,
    //                 -1, 9, 8, -1, -1, -1, -1, 6, -1,
    //                 8, -1, -1, -1, 6, -1, -1, -1, 3,
    //                 4, -1, -1, 8, -1, 3, -1, -1, 1,
    //                 7, -1, -1, -1, 2, -1, -1, -1, 6,
    //                 -1, 6, -1, -1, -1, -1, 2, 8, -1,
    //                 -1, -1, -1, 4, 1, 9, -1, -1, 5,
    //                 -1, -1, -1, -1, 8, -1, -1, 7, 9};

    int board1[] = {
        5,  3, -1,  6,  7,  8, -1,  1, -1,
        6,  7, -1,  1,  9,  5,  3, -1,  8,
        1,  9,  8,  3,  4,  2,  5,  6,  7,
        8, -1, -1, -1,  6, -1, -1, -1,  3,
        4, -1,  6,  8, -1,  3,  7, -1,  1,
        7, -1,  3, -1,  2, -1,  8, -1,  6,
        0,  6,  1, -1,  3, -1,  2,  8,  4,
        2,  8,  7,  4,  1,  9,  6,  3,  5,
        -1, -1, -1, -1,  8,  6,  1,  7,  9
    };
    printf("Original Board:\n");
    printBoard(board1);

    Guess *guesses = NULL;
    int guess_size = 0;
    deduce(board1, &guesses, &guess_size);

    printf("\nSolved Board:\n");
    printBoard(board1);

    // Check if the Sudoku puzzle is solved
    for (int i = 0; i < 81; ++i) {
        assert(board1[i] != -1);
    }

    printf("Test case 1 passed!\n");

    // Add more test cases as needed

    return 0;
}
