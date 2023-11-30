#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    srand(time(NULL)); // use current time as seed for random generator

    // Test case
    int board1[BOARD_SIZE] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1};
    
    printf("Original Board:\n");
    printBoard(board1);

    Guess *guesses = NULL;
    int guess_size = 0;
    deduce(board1, &guesses, &guess_size);

    printf("\nDeduced Board:\n");
    printBoard(board1);
    
    assert(guesses != NULL);
    assert(guess_size != 0);

    List *remembered = NULL;
    SolveItem *item = (SolveItem *)malloc(sizeof(SolveItem));
    item->guesses = guesses;
    item->guess_size = guess_size;
    item->c = 0;
    item->board = (int *)malloc(BOARD_SIZE * sizeof(int));
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        item->board[i] = board1[i];
    }
    list_push_back(&remembered, (void *)item);
    SolveNext next;
    next.workspace = NULL;
    next.remembered = NULL;
    solvenext(remembered, &next);

    assert(next.remembered != NULL);
    assert(next.workspace != NULL);

    printf("\nSolved Board:\n");
    printBoard(next.workspace);

    // guesses = NULL;
    // guess_size = 0;
    // deduce(next.workspace, &guesses, &guess_size);
    // printf("\nDeduced Board:\n");
    // printBoard(next.workspace);

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        assert(next.workspace[i] > -1);
    }

    return 0;
}
