#ifndef SUDOKU_H
#define SUDOKU_H

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
} Entry;

void makeArray(int arr[], int length, int value);
void shuffleArray(int arr[], int length);
int posfor(int x, int y, int axis);
int axismissing(int board[], int x, int axis);
int listbits(int bits, int list[]);
void figurebits(int board[], int allowed[], int needed[]);
void deduce(int board[]);

#endif 