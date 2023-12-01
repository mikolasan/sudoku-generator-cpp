#include <stdio.h>
#include <assert.h>

#include "sudoku.h"

void main()
{
  int board[] = {
    -1, -1, 1, -1, -1, 8, -1, 5, 2,
    -1, -1, -1, -1, -1, -1, -1, -1, 8,
    2, 7, 8, -1, -1, 5, 3, 0, 1,
    -1, 4, -1, -1, -1, 0, 8, -1, -1,
    5, 8, -1, -1, -1, -1, -1, 7, -1,
    1, -1, 3, -1, -1, 7, -1, 4, 5,
    -1, -1, 5, -1, -1, 6, 0, 2, -1,
    -1, -1, -1, -1, 0, 4, -1, -1, 3,
    -1, 1, -1, -1, 2, -1, 5, 8, 4};

  assert(puzzle_length(board) == 46);
  // int length = puzzle_length(board);

  List *moves = NULL;
  find_next_move(board, &moves);

  // Test case 1: Check if the moves list is not empty
  assert(list_is_empty(moves) == 0);
  assert(list_length(moves) == 20);

  // Test case 2: Check the content of the moves list
  int expectedPositions[] = {66, 54, 34, 44, 10, 62, 44, 34, 31, 11, 10, 66, 54, 46, 10, 77, 62, 55, 35, 16};
  int expectedNumbers[] = {5, 4, 3, 0, 5, 7, 0, 3, 5, 4, 5, 5, 4, 0, 5, 3, 7, 3, 6, 6};
  int i = 0;
  while (!list_is_empty(moves)) {
    NextMove *move = (NextMove *)list_pop_back(&moves);
    assert(move->pos == expectedPositions[i]);
    assert(move->num == expectedNumbers[i]);
    i++;
  }

  // Test case 3: Check if the moves list is empty after popping all elements
  assert(list_is_empty(moves) == 1);


  assert(count_next_open_moves(board) == 20);
  
  printf("All tests passed!\n");

  return 0;
}
