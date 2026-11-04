#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

//
// ---- STRUCTS ----
//

// dll_type is owned by the implementation, never by dll
// dll_type->destroy = NULL; is a noop for destruction of data
struct dll_type;

struct dll_node;

struct dll_list;

//
// ---- LIFETIME ----
//

// inits the list of usage
struct dll_list *dll_list_create(void);

// full cleanup function, this destroys the nodes and their data as well
void dll_list_destroy(struct dll_list *list);

//
// ---- NODE ADD ----
//

struct dll_node *dll_list_add(struct dll_list *list, void *data, struct dll_type *type);

#endif
