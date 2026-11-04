#include "double_linked_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// ---- STRUCTS ----
//

typedef void (*desctructor_fn)(void *data);

struct dll_type {
  char *name;
  desctructor_fn destroy;
};

struct dll_node {
  struct dll_node *next;
  struct dll_node *prev;

  void *data;
  struct dll_type *type;
};

struct dll_list {
  struct dll_node *head;
  struct dll_node *tail;
  size_t length;
};

//
// ---- LIFETIME ----
//

struct dll_list *dll_list_create(void) {
  struct dll_list *list = malloc(sizeof *list);

  if (list == NULL) {
    fprintf(stderr, "ERROR: dll_list failed to init, malloc error");
    return NULL;
  }

  list->head = NULL;
  list->tail = NULL;
  list->length = 0;

  return list;
}

void dll_list_destroy(struct dll_list *list) {
  struct dll_node *node = list->head;
  struct dll_node *next = NULL;

  while (node != NULL) {
    if (node->type != NULL && node->type->destroy != NULL) {
      node->type->destroy(node->data);
    }

    next = node->next;
    free(node);
    node = next;
  }

  free(list);
}

//
// ---- NODE ADD ----
//

struct dll_node *dll_list_add(struct dll_list *list, void *data, struct dll_type *type) {
  struct dll_node *node = malloc(sizeof *node);

  if (node == NULL) {
    fprintf(stderr, "ERROR: dll_list failed to create node, malloc error");
    return NULL;
  }

  node->data = data;
  node->type = type;
  node->next = NULL;
  node->prev = NULL;

  if (list->head == NULL) {
    list->head = node;
  }
  if (list->tail != NULL) {
    list->tail->next = node;
    node->prev = list->tail;
  }
  list->tail = node;

  list->length++;

  return node;
}
