#include <stdio.h>
#include <stdlib.h>

#include "sudoku.h"

void makeArray(int arr[], int length, int value)
{
  for (int i = 0; i < length; i++)
  {
    arr[i] = value;
  }
}

void shuffleArray(int arr[], int length)
{
  while (--length)
  {
    int i = rand() % length;
    int temp = arr[i];
    arr[i] = arr[length];
    arr[length] = temp;
  }
}

void shuffle_guesses(Guess *arr, int length)
{
  while (--length)
  {
    int i = rand() % length;
    Guess temp = arr[i];
    arr[i] = arr[length];
    arr[length] = temp;
  }
}

// `y` is a variable from 0 to 8
// `axis` specifies if `y` is moving along vertical
// or horizontal axis, or in a block
// thus it makes an iterator and converts (x,y) to 
// the position in 1D array
int posfor(int x, int y, int axis)
{
  if (axis == VERTICAL)
  {
    return x * SIDE_SIZE + y;
  }
  else if (axis == HORIZONTAL)
  {
    return y * SIDE_SIZE + x;
  }
  // block
  return 27 * (x / SQUARE_SIZE) + SQUARE_SIZE * (x % SQUARE_SIZE) + SIDE_SIZE * (y / SQUARE_SIZE) + (y % SQUARE_SIZE);
}

// missing values from 0-8 on the specified axis
int axismissing(int board[], int x, int axis)
{
  int bits = 0;
  for (int y = 0; y < SIDE_SIZE; y++)
  {
    int pos = posfor(x, y, axis);
    int e = board[pos];
    if (e != -1)
    {
      bits |= 1 << e;
    }
  }
  return 511 ^ bits;
}

// returns the size of `list`
int listbits(int bits, int list[])
{
  int index = 0;
  for (int y = 0; y < SIDE_SIZE; y++)
  {
    if ((bits & (1 << y)) != 0)
    {
      list[index++] = y;
    }
  }
  return index;
}

void figurebits(const int *const board, int allowed[], int needed[])
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    allowed[i] = board[i] == -1 ? 511 : 0;
  }

  for (int axis = 0; axis < N_AXIS; axis++)
  {
    for (int x = 0; x < SIDE_SIZE; x++)
    {
      int bits = axismissing(board, x, axis);
      needed[axis * SIDE_SIZE + x] = bits;
      for (int y = 0; y < SIDE_SIZE; y++)
      {
        int pos = posfor(x, y, axis);
        allowed[pos] &= bits;
      }
    }
  }
}

void available(const int *const board, int available[])
{
  for (int axis = 0; axis < N_AXIS; axis++)
  {
    for (int x = 0; x < SIDE_SIZE; x++)
    {
      int bits = axismissing(board, x, axis);
      available[axis * SIDE_SIZE + x] = bits;
      int numbers[SIDE_SIZE];
      listbits(bits, numbers);
    }
  }
}

void pickbetter(Guess **b, int *b_size, int *c, Guess *t, int t_size)
{
  if (*b == NULL || t_size < *b_size)
  {
    if (*b) free(*b);
    *b = t;
    *b_size = t_size;
    *c = 1;
    return;
  }
  if (t_size > *b_size)
  {
    free(t);
    return;
  }
  if (rand() % *c == 0)
  {
    free(*b);
    *b = t;
    *b_size = t_size;
    (*c)++;
    return;
  }
  else
  {
    free(t);
    (*c)++;
    return;
  }
}

int deduce(int board[], Guess **guesses, int *guess_size)
{
  int allowed[BOARD_SIZE] = { 0 };
  int needed[27] = { 0 };

  while (1)
  {
    int stuck = 1;
    if (*guesses)
    {
      free(*guesses);
      *guess_size = 0;
    }
    *guesses = NULL;
    int count = 0;
    // fill in any spots determined by direct conflicts
    figurebits(board, allowed, needed);
    for (int pos = 0; pos < BOARD_SIZE; pos++)
    {
      if (board[pos] == -1)
      {
        int numbers[SIDE_SIZE];
        int list_size = listbits(allowed[pos], numbers);
        if (list_size == 0)
        {
          return 1;
        }
        else if (list_size == 1)
        {
          board[pos] = numbers[0];
          stuck = 0;
        }
        else if (stuck)
        {
          Guess *t = (Guess *)malloc(list_size * sizeof(Guess));
          for (int i = 0; i < list_size; i++) {
            t[i].pos = pos;
            t[i].num = numbers[i];
          }
          pickbetter(guesses, guess_size, &count, t, list_size);
        }
      }
    }

    if (!stuck)
    {
      figurebits(board, allowed, needed);
    }

    // fill in any spots determined by elimination of other locations
    for (int axis = 0; axis < N_AXIS; axis++)
    {
      for (int x = 0; x < SIDE_SIZE; x++)
      {
        int numbers[SIDE_SIZE];
        int list_size = listbits(needed[axis * SIDE_SIZE + x], numbers);
        for (int i = 0; i < list_size; i++)
        {
          int n = numbers[i];
          int bit = 1 << n;
          int spots[SIDE_SIZE];
          int spotCount = 0;

          for (int y = 0; y < SIDE_SIZE; y++)
          {
            int pos = posfor(x, y, axis);
            if (allowed[pos] & bit)
            {
              spots[spotCount++] = pos;
            }
          }

          if (spotCount == 0)
          {
            return 1;
          }
          else if (spotCount == 1)
          {
            board[spots[0]] = n;
            stuck = 0;
          }
          else if (stuck)
          {
            Guess *t = (Guess *)malloc(spotCount * sizeof(Guess));
            for (int i = 0; i < spotCount; i++) {
              t[i].pos = spots[i];
              t[i].num = n;
            }
            pickbetter(guesses, guess_size, &count, t, spotCount);
          }
        }
      }
    }

    if (stuck)
    {
      if (*guesses)
      {
        shuffle_guesses(*guesses, *guess_size);
        return 1;
      }
      return 0;
    }
  }
  return 0;
}

void solveboard(const int *const original, SolveNext *answer)
{
  int board[BOARD_SIZE];
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    board[i] = original[i];
  }

  Guess *guesses = NULL;
  int guess_size = 0;
  int guess_result = deduce(board, &guesses, &guess_size);
  if (guess_result == 0)
  {
    answer->workspace = (int *)malloc(BOARD_SIZE * sizeof(int));
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
      answer->workspace[i] = board[i];
    }
    answer->remembered = NULL;
    return;
  }

  List *track = NULL;
  SolveItem *item = (SolveItem *)malloc(sizeof(SolveItem));
  item->guesses = guesses;
  item->guess_size = guess_size;
  item->c = 0;
  item->board = (int *)malloc(BOARD_SIZE * sizeof(int));
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    item->board[i] = board[i];
  }
  list_push_back(&track, (void *)item);
  
  solvenext(track, answer);
}

void solvenext(const List *state, SolveNext *next)
{
  List *remembered = state;
  int *workspace = (int *)malloc(BOARD_SIZE * sizeof(int));
  next->workspace = (int *)malloc(BOARD_SIZE * sizeof(int));

  while (!list_is_empty(remembered))
  {
    SolveItem *item = (SolveItem *)list_pop_back(&remembered);
    if (item->c >= item->guess_size)
    {
      free(item);
      continue;
    }

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
      workspace[i] = item->board[i];
    }
    int c = item->c;

    SolveItem *next_count_item = (SolveItem *)malloc(sizeof(SolveItem));
    next_count_item->guesses = item->guesses;
    next_count_item->guess_size = item->guess_size;
    next_count_item->c = item->c + 1;
    next_count_item->board = (int *)malloc(BOARD_SIZE * sizeof(int));
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
      next_count_item->board[i] = item->board[i];
    }
    list_push_back(&remembered, next_count_item);

    int pos = item->guesses[c].pos;
    int n = item->guesses[c].num;
    workspace[pos] = n;

    Guess *guesses = NULL;
    int guess_size = 0;
    int guess_result = deduce(workspace, &guesses, &guess_size);
    if (guess_result == 0)
    {
      next->remembered = remembered;
      for (int i = 0; i < BOARD_SIZE; ++i)
      {
        next->workspace[i] = workspace[i];
      }
      free(workspace);
      return;
    }

    SolveItem *next_item = (SolveItem *)malloc(sizeof(SolveItem));
    next_item->guesses = guesses;
    next_item->guess_size = guess_size;
    next_item->c = 0;
    next_item->board = (int *)malloc(BOARD_SIZE * sizeof(int));
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
      next_item->board[i] = workspace[i];
    }
    list_push_back(&remembered, (void *)next_item);
  }

  while (!list_is_empty(next->remembered))
  {
    SolveItem *item = (SolveItem *)list_pop_back(&next->remembered);
    free(item);
  }
  free(next->workspace);
  next->workspace = NULL;
  free(workspace);
}

void makepuzzle(int *input_board, int *output_board)
{
  int deduced[BOARD_SIZE];
  makeArray(deduced, BOARD_SIZE, -1);

  int order[BOARD_SIZE];
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    order[i] = i;
  }
  shuffleArray(order, BOARD_SIZE);

  Guess puzzle[BOARD_SIZE];
  int puzzle_size = 0;
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    int pos = order[i];
    if (deduced[pos] == -1)
    {
      puzzle[puzzle_size].pos = pos;
      puzzle[puzzle_size].num = input_board[pos];
      puzzle_size++;
      
      deduced[pos] = input_board[pos];
      
      Guess *guesses = NULL;
      int guess_size = 0;
      deduce(deduced, &guesses, &guess_size);
    }
  }

  shuffle_guesses(puzzle, puzzle_size);

  int deleted[BOARD_SIZE];
  for (int i = puzzle_size - 1; i >= 0; i--)
  {
    Guess e = puzzle[i];
    deleted[i] = 1;
    int *tmp_board = (int *)malloc(BOARD_SIZE * sizeof(int));
    boardforentries(puzzle, puzzle_size, tmp_board);
    int rating = checkpuzzle(tmp_board, input_board);
    if (rating == -1)
    {
      deleted[i] = 0;
    }
  }

  Guess new_puzzle[BOARD_SIZE];
  int new_puzzle_size = 0;
  for (int i = 0; i < puzzle_size; ++i)
  {
    if (!deleted[i])
    {
      new_puzzle[new_puzzle_size++] = puzzle[i];
    }
  }
  boardforentries(new_puzzle, new_puzzle_size, output_board);
}

void boardforentries(Guess *entries, int entries_size, int *board)
{
    makeArray(board, BOARD_SIZE, -1);

    for (int i = 0; i < entries_size; ++i) {
        Guess item = entries[i];
        board[item.pos] = item.num;
    }
}

// return rating
int checkpuzzle(int puzzle[], int *board)
{
  SolveNext solution;
  solveboard(puzzle, &solution);
  List *state = solution.remembered;
  int *answer = solution.workspace;

  if (answer == NULL)
  {
    return -1;
  }

  if (board != NULL && boardmatches(board, answer))
  {
    return -1;
  }

  int difficulty = list_length(state);
  SolveNext second;
  second.workspace = NULL;
  second.remembered = NULL;
  solvenext(state, &second);

  if (second.remembered != NULL)
  {
    return -1;
  }

  return difficulty;
}

int boardmatches(int board1[], int board2[])
{
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    if (board1[i] != board2[i]) return 0;
  }
  return 1;
}

void find_next_move(int *board, List **moves)
{
  int allowed[BOARD_SIZE] = { 0 };
  int needed[27] = { 0 };
  
  figurebits(board, allowed, needed);
 
  // fill in any spots determined by direct conflicts
  for (int pos = 0; pos < BOARD_SIZE; pos++)
  {
    if (board[pos] == -1)
    {
      int numbers[SIDE_SIZE];
      int list_size = listbits(allowed[pos], numbers);
      if (list_size == 1)
      {
        NextMove *move = (NextMove *)malloc(sizeof(NextMove));
        move->num = numbers[0];
        move->pos = pos;
        list_push_back(moves, (void *)move);
      }
    }
  }

  // fill in any spots determined by elimination of other locations
  for (int axis = 0; axis < N_AXIS; axis++)
  {
    for (int x = 0; x < SIDE_SIZE; x++)
    {
      int numbers[SIDE_SIZE];
      int list_size = listbits(needed[axis * SIDE_SIZE + x], numbers);
      for (int i = 0; i < list_size; i++)
      {
        int n = numbers[i];
        int bit = 1 << n;
        int spots[SIDE_SIZE];
        int spotCount = 0;

        for (int y = 0; y < SIDE_SIZE; y++)
        {
          int pos = posfor(x, y, axis);
          if (allowed[pos] & bit)
          {
            spots[spotCount++] = pos;
          }
        }

        if (spotCount == 1)
        {
          NextMove *move = (NextMove *)malloc(sizeof(NextMove));
          move->num = n;
          move->pos = spots[0];
          list_push_back(moves, (void *)move);
        }
      }
    }
  }
}

int puzzle_length(int *board)
{
  int length = 0;
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    if (board[i] == -1)
    {
      length++;
    }
  }
  return length;
}

int count_next_open_moves(int *board)
{
  List *moves = NULL;
  find_next_move(board, &moves);
  int length = list_length(moves);
  list_clear(moves);
  return length;
}

int count_singles(int *board)
{
  int available[27] = {0};
    for (int axis = 0; axis < N_AXIS; axis++)
    {
        for (int x = 0; x < SIDE_SIZE; x++)
        {
            int bits = axismissing(board, x, axis);
            available[axis * SIDE_SIZE + x] = bits;
        }
    }

    int n_singles = 0;
    for (int k = 0; k < BOARD_SIZE; ++k)
    {
        if (board[k] > -1) continue;

        int x = k % SIDE_SIZE;
        int y = k / SIDE_SIZE;
        int block_x = x / SQUARE_SIZE;
        int block_y = y / SQUARE_SIZE;
        int row_id = y;
        int column_id = SIDE_SIZE + x;
        int block_id = 18 + block_y * SQUARE_SIZE + block_x;
        int cross = available[row_id] & available[column_id] & available[block_id];
        int numbers[SIDE_SIZE] = {0};
        int size = listbits(cross, numbers);
        if (size == 1)
        {
            n_singles++;
        }
    }
    return n_singles;
}