#ifndef LIST_H
#define LIST_H

struct List;

typedef struct _List
{
  struct _List *next;
  struct _List *prev;
  void *value;
} List;

int list_is_empty(List *list);
void * list_pop_back(List **list);
void list_push_back(List **list, void *value);

#endif
