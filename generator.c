#include <stdio.h>
#include <stdlib.h>

#include "sudoku.h"



int allowed[BOARD_SIZE];
int needed[BOARD_SIZE * 3];


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

void shuffleEntries(Entry *arr, int length)
{
  while (--length)
  {
    int i = rand() % length;
    Entry temp = arr[i];
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
    return x * 9 + y;
  }
  else if (axis == HORIZONTAL)
  {
    return y * 9 + x;
  }
  // block
  return 27 * (x / 3) + 3 * (x % 3) + 9 * (y / 3) + (y % 3);
}

// missing values from 0-8 on the specified axis
int axismissing(int board[], int x, int axis)
{
  int bits = 0;
  for (int y = 0; y < 9; y++)
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
  for (int y = 0; y < 9; y++)
  {
    if ((bits & (1 << y)) != 0)
    {
      list[index++] = y;
    }
  }
  return index;
}

void figurebits(int board[], int allowed[], int needed[])
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    allowed[i] = board[i] == -1 ? 511 : 0;
  }

  for (int axis = 0; axis < 3; axis++)
  {
    for (int x = 0; x < 9; x++)
    {
      int bits = axismissing(board, x, axis);
      needed[axis * 9 + x] = bits;
      for (int y = 0; y < 9; y++)
      {
        int pos = posfor(x, y, axis);
        allowed[pos] &= bits;
      }
    }
  }
}

void pickbetter(Entry **b, int *b_size, int *c, Entry *t, int t_size)
{
  if (*b == NULL || t_size < b_size)
  {
    *b = t;
    *b_size = t_size;
    *c = 1;
    return;
  }
  if (t_size > b_size)
  {
    return;
  }
  if (rand() % *c == 0)
  {
    *b = t;
    *b_size = t_size;
    (*c)++;
    return;
  }
  else
  {
    (*c)++;
    return;
  }
}

void deduce(int board[], Entry *guess)
{
  int allowed[81] = { 0 };
  int needed[27] = { 0 };

  while (1)
  {
    int stuck = 1;
    guess = NULL;
    int guess_size = 0;
    int count = 0;
    // fill in any spots determined by direct conflicts
    figurebits(board, allowed, needed);
    for (int pos = 0; pos < BOARD_SIZE; pos++)
    {
      if (board[pos] == -1)
      {
        int numbers[9];
        int list_size = listbits(allowed[pos], numbers);
        if (list_size == 0)
        {
          // return [];
          return;
        }
        else if (list_size == 1)
        {
          board[pos] = numbers[0];
          stuck = 0;
        }
        else if (stuck)
        {
          Entry *t = (Entry *)malloc(list_size * sizeof(Entry));
          for (int i = 0; i < list_size; i++) {
            t[i].pos = pos;
            t[i].num = numbers[i];
          }
          pickbetter(&guess, &guess_size, &count, t, list_size);
        }
      }
    }

    if (!stuck)
    {
      figurebits(board, allowed, needed);
    }

    // fill in any spots determined by elimination of other locations
    for (int axis = 0; axis < 3; axis++)
    {
      for (int x = 0; x < 9; x++)
      {
        int numbers[9];
        int list_size = listbits(needed[axis * 9 + x], numbers);
        for (int i = 0; i < list_size; i++)
        {
          int n = numbers[i];
          int bit = 1 << n;
          int spots[9];
          int spotCount = 0;

          for (int y = 0; y < 9; y++)
          {
            int pos = posfor(x, y, axis);
            if (allowed[pos] & bit)
            {
              spots[spotCount++] = pos;
            }
          }

          if (spotCount == 0)
          {
            // return [];
            return;
          }
          else if (spotCount == 1)
          {
            board[spots[0]] = n;
            stuck = 0;
          }
          else if (stuck)
          {
            Entry *t = (Entry *)malloc(list_size * sizeof(Entry));
            for (int i = 0; i < list_size; i++) {
              t[i].pos = spots[i];
              t[i].num = n;
            }
            pickbetter(&guess, &guess_size, &count, t, list_size);
          }
        }
      }
    }

    if (stuck)
    {
      if (guess)
      {
        shuffleEntries(guess, guess_size);
      }
      return;
    }
  }
}



// void solveboard(int original[], Entry answer[], int *answerCount)
// {
//   int board[BOARD_SIZE];
//   makeArray(board, BOARD_SIZE, -1);
//   int guesses[81][9];
//   makeArray(guesses, 81, 0);

//   *answerCount = 0;
//   Entry track[81];
//   track[0].num = track[0].pos = track[0].num = 0;
//   track[0].pos = 0;

//   while (*answerCount == 0 && track[0].count < track[0].guesses.length)
//   {
//     track[track[0].count] = track[0];
//     track[0].count++;

//     int workspace[BOARD_SIZE];
//     makeArray(workspace, BOARD_SIZE, 0);
//     Entry tuple2 = track[track[0].count].guesses[track[0].count];
//     workspace[tuple2.pos] = tuple2.num;

//     deduce(workspace);

//     if (workspace[0] == -1)
//     {
//       *answerCount = -1;
//     }
//     else
//     {
//       track[0].count = 0;
//       track[0].board = workspace;
//     }
//   }

//   if (*answerCount != -1)
//   {
//     for (int i = 0; i < BOARD_SIZE; i++)
//     {
//       answer[i] = track[0].board[i];
//     }
//   }
// }

// void solvenext(Entry remembered[], Entry answer[], int *answerCount)
// {
//   while (*answerCount == 0 && remembered[0].count < remembered[0].guesses.length)
//   {
//     Entry tuple1 = remembered[0];

//     if (tuple1.count >= tuple1.guesses.length)
//     {
//       continue;
//     }

//     remembered[remembered[0].count] = tuple1;
//     remembered[0].count++;
//     int workspace[BOARD_SIZE];
//     makeArray(workspace, BOARD_SIZE, 0);
//     Entry tuple2 = tuple1.guesses[tuple1.count];

//     workspace[tuple2.pos] = tuple2.num;

//     int guesses[81][9];
//     makeArray(guesses, 81, 0);
//     deduce(workspace);

//     if (workspace[0] == -1)
//     {
//       *answerCount = 1;
//       for (int i = 0; i < BOARD_SIZE; i++)
//       {
//         answer[i] = workspace[i];
//       }
//     }
//     else
//     {
//       remembered[0].count = 0;
//       remembered[0].board = workspace;
//     }
//   }

//   if (*answerCount == 0)
//   {
//     makeArray(answer, BOARD_SIZE, -1);
//   }
// }

// void makepuzzle(int board[], Entry puzzle[])
// {
//   Entry deduced[BOARD_SIZE];
//   makeArray(deduced, BOARD_SIZE, -1);
//   int order[BOARD_SIZE];
//   makeArray(order, BOARD_SIZE, 0);

//   for (int i = 0; i < BOARD_SIZE; i++)
//   {
//     order[i] = i;
//   }

//   shuffleArray(order, BOARD_SIZE);

//   for (int i = 0; i < BOARD_SIZE; i++)
//   {
//     int pos = order[i];

//     if (deduced[pos].num == -1)
//     {
//       puzzle[i].pos = pos;
//       puzzle[i].num = board[pos];
//       deduced[pos] = board[pos];
//       deduce(deduced);
//     }
//   }

//   shuffleArray(puzzle, BOARD_SIZE);

//   for (int i = BOARD_SIZE - 1; i >= 0; i--)
//   {
//     Entry e = puzzle[i];
//     puzzle[i].pos = -1;
//     int rating = checkpuzzle(boardforentries(puzzle), board);
//     if (rating == -1)
//     {
//       puzzle[i] = e;
//     }
//   }
// }

// int checkpuzzle(Entry puzzle[], int board[])
// {
//   if (board == NULL)
//   {
//     board = (int *)malloc(sizeof(int) * BOARD_SIZE);
//     makeArray(board, BOARD_SIZE, -1);
//   }

//   Entry tuple1[BOARD_SIZE];
//   solveboard(puzzle, tuple1);
//   if (tuple1[0].num == -1)
//   {
//     return -1;
//   }

//   if (board != NULL && !boardmatches(board, tuple1))
//   {
//     return -1;
//   }

//   int difficulty = tuple1[0].count;
//   Entry tuple2[BOARD_SIZE];
//   solvenext(tuple1, tuple2);

//   if (tuple2[0].num != -1)
//   {
//     return -1;
//   }

//   return difficulty;
// }
