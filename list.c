#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "list.h"

void list_init(List *list, void (*destroy)(void *data),
	       char* (*tostr)(void *data)){
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  list->destroy = destroy;
  list->tostr = tostr;
}

void list_destroy(List *list){
  void *data;
  while (list_size(list) > 0){
    if (list_rem_next(list,NULL,(const void **) &data) == 0 &&
	list->destroy != NULL)
      list->destroy(data);
  }
  memset(list,0,sizeof(list));
}

int list_ins_next(List *list, ListElmt *element, const void *data){
  ListElmt *new_element;
  if ((new_element = (ListElmt *) malloc(sizeof(ListElmt))) == NULL)
    return -1;
  new_element->data = (void *) data;
  /* specifying NULL for element indicates insertion at head of list */
  if (element == NULL){
    /* if list size is zero then tail is also new_element */
    if (list_size(list) == 0)
      list->tail = new_element;
    /* head is shoved over one */
    new_element->next = list->head;
    /* new element is the head */
    list->head = new_element;
  }
  /* for insertion to any other part of list */
  else{
    /* if inserting into tail new_element becomes tail */
    if (element->next == NULL)
      list->tail = new_element;
    new_element->next = element->next;
    element->next = new_element;
  }
  
  list->size++;
  return 0;
}

int list_rem_next(List *list, ListElmt *element, const void **data){
  ListElmt     *old_element;
  
  if (list_size(list) == 0)
    return -1;

  /* NULL indicates head element */
  if (element == NULL){
    *data =list->head->data;
    old_element = list->head;
    list->head = list->head->next;
    
    /* if it's the tail then set
       its neighbor to NULL
    */
    if (list_size(list) == 1)
      list->tail = NULL;
  }
  else{
    if (element->next == NULL)
      return -1;
    *data = element->next->data;
    old_element = element->next;
    /* fill the hole */
    element->next = element->next->next;
    /* check if now tail */
    if (element->next == NULL)
      list->tail = element;
  }

  free(old_element);
  list->size--;
  return 0;
}


/* O(n) methods */
void list_print(List *list){
  ListElmt *node = list_head(list);
  printf("[ "); 
  while (node != NULL){
    printf("%s ", list->tostr(node->data));
    node = node->next;
  }
  printf(" ]\n"); 
  return;
}

/* add to specified index */
int list_add(List *list, int index, void *data){
  int i = 0;
  ListElmt *node = list->head;
  
  if (index > list->size || index < 0)
    return -1;
  
  if (index == 0)
    list_ins_next(list, NULL, data);  
  else if (index == list->size)
    list_ins_next(list, list->tail, data);  
  else{
    while (i < index){
      node = node->next;
      ++i;
    }
    list_ins_next(list, node, data);  
  }
  return 0;
}
/* this is O(1) but is included for convencience */
void list_append(List *list, void *data){
  ListElmt *node = list->tail;
  list_ins_next(list,list->tail,data);
  printf("new list size after append: %d\n", list->size);
  return;
}


