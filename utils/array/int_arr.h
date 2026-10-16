#ifndef INT_ARR_H
#define INT_ARR_H

#include <stdbool.h>
#include <stddef.h>

//
// ---- int_arr ----
//
typedef struct int_arr int_arr; // opaque struct

//
// ---- life time functions ----
//

// Returns a new empty array on success, NULL on allocation failure
// The caller must own its lifecycle and call int_arr_destroy
int_arr *int_arr_create(void);

// Frees the int_arr and its data, safe to call on NULL
void int_arr_destroy(int_arr *arr);

//
// ---- add ----
//

// adds to the tail of the array
bool int_arr_append(int_arr *arr, int val);

// inserts at the position, moving the tail out
bool int_arr_insert(int_arr *arr, size_t pos, int val);

// replaces the value at the position
bool int_arr_replace(int_arr *arr, size_t pos, int val);

//
// ---- remove ----
//

// removes from the tail of the array, passing the removed value into out
bool int_arr_pop(int_arr *arr, int *out);

// removes from the position, moving the tail up, passing the removed value into
// out
bool int_arr_remove_at(int_arr *arr, size_t pos, int *out);

#endif
