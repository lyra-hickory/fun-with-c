#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

//
// ---- STRUCTS ----
//

typedef void (*destructor_fn)(void *data);

typedef bool (*dll_match_fn)(void *data, void *ctx);

typedef bool (*dll_compare_fn)(void *data_front, void *data_back, void *ctx);

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

//
// ---- NODE REMOVAL ----
//

// **out for returning the data, ownership of data is on the user
// node gets destroyed
size_t dll_list_pop_at(struct dll_list *list, void **out, size_t index);

// Complete cleanup, node is destroyed and so is the data
size_t dll_list_remove_at(struct dll_list *list, size_t index);

// Remove by a match_fn acting on the data
// true   :   node gets destroy
// false  :   node gets skipped
//
// Note that the test_fn acts on node->data
size_t dll_list_remove_by(struct dll_list *list, dll_match_fn match_fn, void *ctx);

// Split by a match_fn acting on the data, returning a new list with the matched nodes at the given
// pointer
//
// true   :   node gets popped
// false  :   node gets skipped
//
// Note that the test_fn acts on node->data
//
// Note that the returned list is a compilation of the matched nodes,
// not new nodes with the same data
//
// Note that NULL means a failure occured
size_t dll_list_split_by(struct dll_list *in_list, struct dll_list **out_list,
                         dll_match_fn match_fn, void *ctx);

//
// ---- NODE SORT ----
//

// Sort the nodes by match_fn
//
// true   :   ??
// false  :   ??
// void dll_list_sort_by(struct dll_list *list, dll_compare_fn test_fn, void *ctx);

// ---- END ----
#endif
