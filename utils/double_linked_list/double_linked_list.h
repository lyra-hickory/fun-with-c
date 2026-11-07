#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <stddef.h>

//
// ---- STRUCTS ----
//

typedef void (*destructor_fn)(void *data);

// dll_type is owned by the implementation, never by dll
// dll_type->destroy = NULL; is a noop for destruction of data
struct dll_type {
  char *name;
  destructor_fn destroy;
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

// inits the list for usage
struct dll_list *dll_list_create(void);

// full cleanup function, this destroys the nodes and their data as well
void dll_list_destroy(struct dll_list *list);

//
// ---- NODE ADD ----
//

struct dll_node *dll_list_add_head(struct dll_list *list, void *data, struct dll_type *type);

struct dll_node *dll_list_add_tail(struct dll_list *list, void *data, struct dll_type *type);

struct dll_node *dll_list_insert_at(struct dll_list *list, void *data, struct dll_type *type,
                                    size_t index);

//
// ---- NODE GET ----
//

struct dll_node *dll_list_get_at(struct dll_list *list, size_t index);

// ---- END ----
#endif
