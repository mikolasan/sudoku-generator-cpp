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

typedef struct
{
  int strategy;
  int pos;
  int num;

} NextMove;


void makeArray(int arr[], int length, int value);
void shuffleArray(int arr[], int length);
void shuffle_guesses(Guess *arr, int length);
int posfor(int x, int y, int axis);
int axismissing(int board[], int x, int axis);
int listbits(int bits, int list[]);
void figurebits(const int *const board, int allowed[], int needed[]);
void pickbetter(Guess **b, int *b_size, int *c, Guess *t, int t_size);
int deduce(int board[], Guess **guess, int *guess_size);
void solvenext(const List *remembered, SolveNext *next);
void makepuzzle(int *input_board, int *output_board);
void boardforentries(Guess *entries, int entries_size, int *board);
void solveboard(const int *const original, SolveNext *answer);
int checkpuzzle(int puzzle[], int *board);
int boardmatches(int board1[], int board2[]);

void find_next_move(int *board, List **moves);
int puzzle_length(int *board);
int count_next_open_moves(int *board);

#endif 