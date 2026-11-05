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

struct dll_node *dll_node_create(void *data, struct dll_type *type) {
  struct dll_node *node = malloc(sizeof *node);

  if (node == NULL) {
    fprintf(stderr, "ERROR: dll_list failed to create node, malloc error\n");
    return NULL;
  }

  node->data = data;
  node->type = type;
  node->next = NULL;
  node->prev = NULL;

  return node;
}

// -- add head --
struct dll_node *dll_list_add_head(struct dll_list *list, void *data, struct dll_type *type) {
  struct dll_node *node = dll_node_create(data, type);

  if (node == NULL) {
    return NULL;
  }

  if (list->head != NULL) {
    list->head->prev = node;
    node->next = list->head;
  }
  if (list->tail == NULL) {
    list->tail = node;
  }

  list->head = node;
  list->length++;

  return node;
}

// -- add tail --
struct dll_node *dll_list_add_tail(struct dll_list *list, void *data, struct dll_type *type) {
  struct dll_node *node = dll_node_create(data, type);

  if (node == NULL) {
    return NULL;
  }

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

// -- insert at --
struct dll_node *dll_list_insert_at(struct dll_list *list, void *data, struct dll_type *type,
                                    size_t index) {
  if (index > list->length) {
    fprintf(stderr, "ERROR: dll_list_insert_at index %zu out of bounds\n", index);
    return NULL;
  }

  struct dll_node *node = dll_node_create(data, type);

  if (node == NULL) {
    return NULL;
  }

  // insert at head / tail
  if (index == 0) {
    if (list->head != NULL) {
      list->head->prev = node;
      node->next = list->head;
    }
    if (list->tail == NULL) {
      list->tail = node;
    }

    list->head = node;
    list->length++;

    return node;
  }

  if (index == list->length) {
    if (list->tail != NULL) {
      list->tail->next = node;
      node->prev = list->tail;
    }
    // realistically this line shouldn't ever be hit
    if (list->head == NULL) {
      list->head = node;
    }

    list->tail = node;
    list->length++;

    return node;
  }

  // find the prev and next nodes
  // TODO/optimisation: We could walk backwards if index > length/2
  struct dll_node *prev_node = list->head;
  for (size_t i = 1; i < index; i++) {
    if (prev_node->next == NULL) {
      fprintf(stderr, "ERROR: dll_list_insert_at broken chain at index %zu\n", i);
      return NULL;
    }
    prev_node = prev_node->next;
  }
  struct dll_node *next_node = prev_node->next;

  // insert our node between prev and next
  node->prev = prev_node;
  prev_node->next = node;

  node->next = next_node;
  next_node->prev = node;

  list->length++;

  return node;
}
