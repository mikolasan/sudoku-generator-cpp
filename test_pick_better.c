#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sudoku.h"

int main() {
    // Test case 1
    int b_size1 = 3;
    Entry *b1 = (Entry *)malloc(b_size1 * sizeof(Entry));
    for (int i = 0; i < b_size1; ++i) {
        b1[i].pos = i;
        b1[i].num = i + 1;
    }
    int c1 = 2;

    int t_size1 = 2;
    Entry *t1 = (Entry *)malloc(t_size1 * sizeof(Entry));
    for (int i = 0; i < t_size1; ++i) {
        t1[i].pos = i + 10;
        t1[i].num = i + 11;
    }
    
    Entry *b1_orig = b1;
    pickbetter(&b1, &b_size1, &c1, t1, t_size1);

    // Check if b1 and c1 are updated correctly
    assert(b1 == t1);
    assert(b_size1 == t_size1);
    assert(c1 == 1);

    free(b1_orig);
    free(t1);

    printf("Test case 1 passed!\n");

    // Test case 2
    int b_size2 = 3;
    Entry *b2 = (Entry *)malloc(b_size2 * sizeof(Entry));
    for (int i = 0; i < b_size2; ++i) {
        b2[i].pos = i + 20;
        b2[i].num = i + 21;
    }
    int c2 = 1;

    int t_size2 = 3;
    Entry *t2 = (Entry *)malloc(t_size2 * sizeof(Entry));
    for (int i = 0; i < t_size2; ++i) {
        t2[i].pos = i + 30;
        t2[i].num = i + 31;
    }

    Entry *b2_orig = b2;
    pickbetter(&b2, &b_size2, &c2, t2, t_size2);

    // Check if b2 and c2 are updated correctly
    assert(b2 == t2);
    assert(b_size2 == t_size2);
    assert(c2 == 2);

    free(b2_orig);
    free(t2);

    printf("Test case 2 passed!\n");

    // Test case 3
    int b_size3 = 2;
    Entry *b3 = (Entry *)malloc(b_size3 * sizeof(Entry));
    for (int i = 0; i < b_size3; ++i) {
        b3[i].pos = i + 40;
        b3[i].num = i + 41;
    }
    int c3 = 0;

    int t_size3 = 3;
    Entry *t3 = (Entry *)malloc(t_size3 * sizeof(Entry));
    for (int i = 0; i < t_size3; ++i) {
        t3[i].pos = i + 50;
        t3[i].num = i + 51;
    }

    pickbetter(&b3, &b_size3, &c3, t3, t_size3);

    // Check if b3 and c3 remain unchanged
    assert(b3 != t3);
    assert(b_size3 == 2);
    assert(c3 == 0);

    free(b3);
    free(t3);

    printf("Test case 3 passed!\n");

    // Test case 4
    int b_size4 = 3;
    Entry *b4 = (Entry *)malloc(b_size4 * sizeof(Entry));
    for (int i = 0; i < b_size4; ++i) {
        b4[i].pos = i + 60;
        b4[i].num = i + 61;
    }
    int c4 = 10000;

    int t_size4 = 3;
    Entry *t4 = (Entry *)malloc(t_size4 * sizeof(Entry));
    for (int i = 0; i < t_size4; ++i) {
        t4[i].pos = i + 70;
        t4[i].num = i + 71;
    }

    pickbetter(&b4, &b_size4, &c4, t4, t_size4);

    // Check if b4 and c4 are updated correctly
    assert(b4 != t4);
    assert(b_size4 == 3);
    assert(c4 == 10001);

    free(b4);
    free(t4);

    printf("Test case 4 passed!\n");

    // Test case 5
    Entry *b5 = NULL;
    int b_size5 = 0;
    int c5 = 12345;
    int t_size5 = 3;
    Entry *t5 = (Entry *)malloc(t_size5 * sizeof(Entry));
    for (int i = 0; i < t_size5; ++i) {
        t5[i].pos = i + 80;
        t5[i].num = i + 81;
    }

    pickbetter(&b5, &b_size5, &c5, t5, t_size5);

    // Check if b5 and c5 are updated correctly
    assert(b5 == t5);
    assert(b_size5 == t_size5);
    assert(c5 == 1);

    free(t5);

    printf("Test case 5 passed!\n");
    return 0;
}
