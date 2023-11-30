#ifndef SUDOKU_H
#define SUDOKU_H

#include "list.h"

#define BOARD_SIZE 81

enum AXIS {
  VERTICAL,
  HORIZONTAL,
  BLOCK
};

typedef struct
{
  int pos;
  int num;
} Guess;

typedef struct
{
  Guess *guesses;
  int guess_size;
  int c;
  int *board;
} SolveItem;

typedef struct
{
  List *remembered;
  int *workspace;
} SolveNext;

void makeArray(int arr[], int length, int value);
void shuffleArray(int arr[], int length);
void shuffle_guesses(Guess *arr, int length);
int posfor(int x, int y, int axis);
int axismissing(int board[], int x, int axis);
int listbits(int bits, int list[]);
void figurebits(int board[], int allowed[], int needed[]);
void pickbetter(Guess **b, int *b_size, int *c, Guess *t, int t_size);
void deduce(int board[], Guess **guess, int *guess_size);
void solvenext(List *remembered, SolveNext *next);
void makepuzzle(int *input_board, int *output_board);
void boardforentries(Guess *entries, int entries_size, int *board);
void solveboard(const int *const original, SolveNext *answer);

#endif 