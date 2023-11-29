#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int list_is_empty(List *list)
{
  return list == NULL ? 1 : 0;
}

// don't POP when the *list pointer is NULL
void * list_pop_back(List **list)
{
  List *back = *list;
  if (back->prev)
  {
    *list = back->prev;
    (*list)->next = NULL;
  }
  else
  {
    *list = NULL;
  }
  void * value = back->value;
  free(back);
  return value;
}

void list_push_back(List **list, void *value)
{
  List *new_back = (List *)malloc(sizeof(List));
  new_back->prev = *list; // even if *list is null
  new_back->next = NULL;
  new_back->value = value;
  if (!list_is_empty(*list))
  {
    (*list)->next = new_back;
  }
  *list = new_back;
}