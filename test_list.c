#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

// Test the list functions
int main()
{
    List *myList = NULL;

    // Test list_is_empty
    assert(list_is_empty(myList) == 1);
    assert(list_length(myList) == 0);

    // Test list_push_back
    int value1 = 42;
    list_push_back(&myList, &value1);
    assert(list_is_empty(myList) == 0);
    assert(list_length(myList) == 1);
    int *curr_value = (int *)myList->value;
    assert((int)(*curr_value) == value1);

    // Test list_pop_back
    int *popValue1 = (int *)list_pop_back(&myList);
    assert(*popValue1 == value1);
    assert(list_is_empty(myList) == 1);
    assert(list_length(myList) == 0);

    // Test list_push_back with multiple values
    int value2 = 99;
    int value3 = 123;
    list_push_back(&myList, &value2);
    assert(list_length(myList) == 1);
    list_push_back(&myList, &value3);
    assert(list_length(myList) == 2);
    assert(list_is_empty(myList) == 0); // The list should not be empty

    // Test list_pop_back with multiple values
    int *popValue3 = (int *)list_pop_back(&myList);
    assert((int)(*popValue3) == value3);
    int *popValue2 = (int *)list_pop_back(&myList);
    assert((int)(*popValue2) == value2);
    assert(list_is_empty(myList) == 1);
    assert(list_length(myList) == 0);

    printf("All tests passed!\n");

    return 0;
}
