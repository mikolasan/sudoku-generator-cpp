#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sudoku.h"

void printBoard(int *board)
{
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    printf("%d ", board[i]);
    if ((i + 1) % 9 == 0)
    {
      printf("\n");
    }
  }
}

void freeSolveNext(SolveNext *next) {
    free(next->workspace);
    free(next->remembered);
}

int main()
{
  // Create a board with a solvable puzzle (replace with your actual input)
  int empty_board[BOARD_SIZE] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1};

  // Print the original and solved boards for visual inspection
  printf("Original Board:\n");
  printBoard(empty_board);

  SolveNext answer;
  solveboard(empty_board, &answer);

  assert(answer.remembered != NULL);
  assert(answer.workspace != NULL);

  printf("\nSolved Board:\n");
  printBoard(answer.workspace);

  // Free allocated memory
  // freeSolveNext(&answer);

  return 0;
}
