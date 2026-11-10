#include "double_linked_list.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// ---- LIFETIME ----
//

struct dll_list *dll_list_create(void) {
  struct dll_list *list = malloc(sizeof *list);

  if (list == NULL) {
    fprintf(stderr, "ERROR: dll_list failed to init, malloc error\n");
    return NULL;
  }

  list->head = NULL;
  list->tail = NULL;
  list->length = 0;

  return list;
}

static void dll_list_destroy_node(struct dll_node *node) {
  if (node->type != NULL && node->type->destroy != NULL) {
    node->type->destroy(node->data);
  }

  free(node);
}

void dll_list_destroy(struct dll_list *list) {
  if (list == NULL) {
    return;
  }

  struct dll_node *node = list->head;
  struct dll_node *next = NULL;

  while (node != NULL) {
    next = node->next;
    dll_list_destroy_node(node);
    node = next;
  }

  free(list);
}

//
// ---- NODE ADD ----
//

static struct dll_node *dll_node_create(void *data, struct dll_type *type) {
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
  if (list == NULL) {
    return NULL;
  }

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
  if (list == NULL) {
    return NULL;
  }

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
  if (list == NULL) {
    return NULL;
  }

  if (index > list->length) {
    fprintf(stderr, "ERROR: dll_list_insert_at index %zu out of bounds\n", index);
    return NULL;
  }

  // insert at head
  if (index == 0) {
    return dll_list_add_head(list, data, type);
  }
  // insert at tail
  if (index == list->length) {
    return dll_list_add_tail(list, data, type);
  }

  struct dll_node *node = dll_node_create(data, type);

  if (node == NULL) {
    return NULL;
  }

  // find the prev and next nodes
  struct dll_node *prev_node = list->head;
  for (size_t i = 1; i < index; i++) {
    assert(prev_node->next != NULL); // loud failure during debug
    prev_node = prev_node->next;
  }
  assert(prev_node->next != NULL); // loud failure during debug

  struct dll_node *next_node = prev_node->next;

  // insert our node between prev and next
  node->prev = prev_node;
  prev_node->next = node;

  node->next = next_node;
  next_node->prev = node;

  list->length++;

  return node;
}

//
// ---- NODE GET ----
//

struct dll_node *dll_list_get_at(struct dll_list *list, size_t index) {
  if (list == NULL || index >= list->length) {
    return NULL;
  }

  struct dll_node *node;
  if (index > list->length / 2) {
    size_t steps_back = list->length - (index + 1);
    node = list->tail;
    for (size_t i = 0; i < steps_back; i++) {
      if (node->prev == NULL) {
        return NULL;
      }
      node = node->prev;
    }
  } else {
    node = list->head;
    for (size_t i = 0; i < index; i++) {
      if (node->next == NULL) {
        return NULL;
      }
      node = node->next;
    }
  }

  return node;
}

//
// ---- NODE REMOVAL ----
//

static void unlink_node(struct dll_list *list, struct dll_node *node) {
  struct dll_node *prev = node->prev;
  struct dll_node *next = node->next;

  // neighbouring links
  if (prev != NULL) {
    prev->next = next;
  }
  if (next != NULL) {
    next->prev = prev;
  }

  // list index
  if (list->head == node) {
    list->head = next;
  }
  if (list->tail == node) {
    list->tail = prev;
  }

  list->length--;
}

size_t dll_list_pop_at(struct dll_list *list, size_t index, void **out) {
  if (list == NULL || index >= list->length) {
    return 0;
  }

  struct dll_node *node = dll_list_get_at(list, index);

  if (node == NULL) {
    return 0;
  }

  unlink_node(list, node);

  // out the data and destroy the node
  if (out != NULL) {
    *out = node->data;
  }

  free(node);

  return 1;
}

size_t dll_list_remove_at(struct dll_list *list, size_t index) {
  if (list == NULL || index >= list->length) {
    return 0;
  }

  struct dll_node *node = dll_list_get_at(list, index);

  if (node == NULL) {
    return 0;
  }

  unlink_node(list, node);

  dll_list_destroy_node(node);

  return 1;
}
