#include "int_arr.h"
#include <stdlib.h>

//
// ---- CONSTANTS ----
//
#define INT_ARR_INITIAL_CAPACITY 8

//
// ---- life time functions ----
//

int_arr *int_arr_create(void) {
  int_arr *arr = malloc(sizeof *arr);
  if (arr == NULL) {
    // Failed to allocate memory for the struct
    return NULL;
  }

  arr->data = malloc(INT_ARR_INITIAL_CAPACITY * sizeof *arr->data);
  if (arr->data == NULL) {
    // Failed to allocate memory for the data
    free(arr);
    return NULL;
  }

  arr->capacity = INT_ARR_INITIAL_CAPACITY;
  arr->length = 0;

  return arr;
}

void int_arr_destroy(int_arr *arr) {
  if (arr == NULL) {
    return;
  }

  free(arr->data);
  free(arr);
}

//
// ---- add ----
//

bool int_arr_append(int_arr *arr, int val) {}

bool int_arr_insert(int_arr *arr, size_t pos, int val) {}

bool int_arr_replace(int_arr *arr, size_t pos, int val) {}

//
// ---- remove ----
//

bool int_arr_pop(int_arr *arr, int *out) {}

bool int_arr_remove_at(int_arr *arr, size_t pos, int *out) {}
