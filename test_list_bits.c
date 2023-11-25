#include <stdio.h>
#include <assert.h>

#include "sudoku.h"

int main() {
    // Test case 1
    int list1[9] = { 0 };
    int bits1 = 0b000000111;  // Binary representation of bits
    int result1 = listbits(bits1, list1);
    assert(result1 == 3);  // Number of set bits (1s) in 0b000000111 is 3

    // Test case 2
    int list2[9] = { 0 };
    int bits2 = 0b111111010;  // Binary representation of bits
    int result2 = listbits(bits2, list2);
    assert(result2 == 7);  // Number of set bits (1s) in 0b111111010 is 7

    // Test case 3
    int list3[9] = { 0 };
    int bits3 = 0b000000000;  // Binary representation of bits
    int result3 = listbits(bits3, list3);
    assert(result3 == 0);  // Number of set bits (1s) in 0b000000000 is 0

    // Test case 4
    int list4[9] = { 0 };
    int bits4 = 0b111111111;  // Binary representation of bits
    int result4 = listbits(bits4, list4);
    assert(result4 == 9);  // Number of set bits (1s) in 0b111111111 is 9

    return 0;
}
