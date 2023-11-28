#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sudoku.h"

void printBoard(int *board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        printf("%d ", board[i]);
        if ((i + 1) % 9 == 0) {
            printf("\n");
        }
    }
}

int main() {
    // Create an input board with some values (replace with your actual input)
    int input_board[BOARD_SIZE] = {
        5, 3, -1, -1, 7, -1, -1, -1, -1,
        6, -1, -1, 1, 9, 5, -1, -1, -1,
        -1, 9, 8, -1, -1, -1, -1, 6, -1,
        8, -1, -1, -1, 6, -1, -1, -1, 3,
        4, -1, -1, 8, -1, 3, -1, -1, 1,
        7, -1, -1, -1, 2, -1, -1, -1, 6,
        -1, 6, -1, -1, -1, -1, 2, 8, -1,
        -1, -1, -1, 4, 1, 9, -1, -1, 5,
        -1, -1, -1, -1, 8, -1, -1, 7, 9
    };

    // Print the input and output boards for visual inspection
    printf("Input Board:\n");
    printBoard(input_board);

    int output_board[BOARD_SIZE];
    makepuzzle(input_board, output_board);

    printf("\nOutput Board (Puzzle):\n");
    printBoard(output_board);

    return 0;
}
