#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include <string.h>

List *init_history(){
  List *list = (List*)malloc(sizeof(List)); // allocate memory for size of list
  list->root = NULL;
  return list;
}


char *copyStr(const char *str) {
  size_t len = strlen(str);
  char *copy = (char *)malloc((len + 1) * sizeof(char));
  if (copy == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < len; i++) {
    copy[i] = str[i];
  }
  copy[len] = '\0';
  return copy;
}

void add_history(List *list, char *str){
  Item *item = (Item*)malloc(sizeof(Item));
  item->str = copyStr(str); 
  item->next = NULL;           

  if (list->root == NULL) {
    item->id = 1;
    list->root = item;
  } else {
    Item *temp = list->root;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    item->id = temp->id + 1;
    temp->next = item;
  }
}
char *get_history(List *list, int id){
  Item *temp = list->root;
  while (temp != NULL) {
    if (temp->id == id) {
      return temp->str;
    }
    temp = temp->next;
  }
  return NULL;
}

void print_history(List *list){
  Item *temp = list->root;
  while (temp != NULL) {
    printf("%d, %s\n", temp->id, temp->str);
    temp = temp->next;
  }
}

void free_history(List *list){
  Item *temp;
  while (list->root != NULL) {
    temp = list->root->next;
    free(list->root->str);  // Free the stored string
    free(list->root);       // Free the current item
    list->root = temp;
  }
}
