#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

void freeSolveNext(SolveNext *next)
{
    free(next->workspace);
    free(next->remembered);
}

int main()
{
  srand(time(NULL)); // use current time as seed for random generator

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

  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    assert(answer.workspace[i] > -1);
  }

  // // bad board
  // int board1[BOARD_SIZE] = {
  //   6, 1, 0, 7, 4, -1, 3, 2, 5,
  //   3, 8, 4, 0, 1, 5, 6, -1, -1,
  //   7, 5, 2, 3, 8, 6, 4, 0, 1,
  //   8, 7, 1, 2, 5, 3, 0, 4, 6,
  //   2, 4, 6, 8, 7, 0, 1, 5, 3,
  //   0, 3, 5, 1, 6, 4, -1, -1, -1,
  //   5, 0, 8, 4, 3, 1, -1, 6, -1,
  //   1, 6, 7, 5, 0, -1, -1, 3, 4,
  //   4, 2, 3, 6, 8, 7, 5, 1, 0,
  // };

  // printf("Original Board:\n");
  // printBoard(board1);

  // SolveNext answer1;
  // solveboard(board1, &answer1);

  // assert(answer1.remembered == NULL);
  // // assert(answer1.workspace == NULL);

  return 0;
}
