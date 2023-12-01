#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "sudoku.h"

void printBoard(int *board)
{
    for (int i = 0; i < BOARD_SIZE; ++i) {
        printf("%d ", board[i]);
        if ((i + 1) % 9 == 0) {
            printf("\n");
        }
    }
}

float rate_puzzle(int *puzzle, int samples)
{
    int total = 0;
    for (int i = 0; i < samples; ++i)
    {
        SolveNext answer;
        solveboard(puzzle, &answer);
        if (answer.workspace == NULL)
        {
            return -1.;
        }
        printf("%d\n", list_length(answer.remembered));
        total += list_length(answer.remembered);
    }
    return (float)total / samples;
}

int main()
{
    srand(time(NULL)); // use current time as seed for random generator

    // Create an input board with some values (replace with your actual input)
    int input_board[BOARD_SIZE] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1};

    // Print the input and output boards for visual inspection
    printf("Input Board:\n");
    printBoard(input_board);

    SolveNext answer;
    solveboard(input_board, &answer);
    
    printf("\nSolution:\n");
    printBoard(answer.workspace);

    int output_board[BOARD_SIZE];
    makepuzzle(answer.workspace, output_board);

    printf("\nOutput Board (Puzzle):\n");
    printBoard(output_board);

    float rating = rate_puzzle(output_board, 4);
    printf("Puzzle rating: %.2f", rating);

    return 0;
}
