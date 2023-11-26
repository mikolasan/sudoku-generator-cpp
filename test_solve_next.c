#include <stdio.h>
#include <stdlib.h>
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

void freeSolveNext(SolveNext *next) {
    free(next->workspace);
    free(next->remembered);
}

int main()
{
    // Test case
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

    assert(guesses != NULL);
    assert(guess_size != 0);

    int max_size = 10;  // Adjust the size as needed
    int size = 1;
    SolveItem **remembered = (SolveItem **)malloc(max_size * sizeof(SolveItem *));
    remembered[0] = (SolveItem *)malloc(sizeof(SolveItem));
    remembered[0]->guesses = guesses;
    remembered[0]->guess_size = guess_size;
    remembered[0]->c = 0;
    remembered[0]->board = (int *)malloc(BOARD_SIZE * sizeof(int));
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        remembered[0]->board[i] = board1[i];
    }

    SolveNext next;
    next.workspace = NULL;
    next.remembered = NULL;

    // Call the solvenext function
    
    solvenext(remembered, &size, &next);

    printf("\nSolved Board:\n");
    printBoard(next.workspace);
    
    // Check the result
    if (next.remembered != NULL)
    {
        // Process the result as needed
        // ...

        // Free allocated memory
        freeSolveNext(&next);
    }
    else
    {
        printf("No solution found.\n");
    }

    // // Free allocated memory
    // for (int i = 0; i < 100; ++i)
    // {
    //     free(remembered[i]->board);
    //     free(remembered[i]->guesses);
    //     free(remembered[i]);
    // }
    free(remembered);

    return 0;
}
