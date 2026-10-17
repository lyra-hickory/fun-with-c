#include "int_arr.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//
// ---- CONSTANTS ----
//
#define INT_ARR_INITIAL_CAPACITY 8

//
// ---- struct defintion ----
//

struct int_arr {
  size_t capacity;
  size_t length;
  int *data;
};

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

static bool double_data_capacity(int_arr *arr) {
  // helper for expanding our capacity

  // -- safety checks --
  if (arr == NULL) {
    return false;
  }

  if (arr->data == NULL) {
    return false;
  }

  if (arr->capacity > (SIZE_MAX / sizeof(int) / 2)) {
    // Our new capacity is too big and would integer overflow size_t
    return false;
  }

  size_t new_capacity = arr->capacity * 2;

  if (new_capacity == 0) {
    // Unlikely to ever happen but a guard against having a 0 capacity
    new_capacity = INT_ARR_INITIAL_CAPACITY;
  }

  size_t new_byte_max = (sizeof *arr->data) * new_capacity;

  int *tmp = realloc(arr->data, new_byte_max);

  if (tmp == NULL) {
    return false;
  }

  // safety checks passed, new data block, so set the new capacity and the new
  // block pointer
  arr->capacity = new_capacity;
  arr->data = tmp;

  return true;
}

//
// ---- add ----
//

bool int_arr_append(int_arr *arr, int val) {
  // -- safety checks --
  if (arr == NULL) {
    return false;
  }

  if (arr->data == NULL) {
    return false;
  }

  // -- managing capacity --
  if (arr->length >= arr->capacity) {
    bool success = double_data_capacity(arr);

    if (success == false) {
      return false;
    }
  }

  // -- appending the value --
  arr->data[arr->length++] = val;
  return true;
}

bool int_arr_insert(int_arr *arr, size_t pos, int val) {
  if (arr == NULL) {
    return false;
  }

  if (arr->data == NULL) {
    return false;
  }

  // trying to insert it out of assigned slots is a failure
  if (pos > arr->length) {
    return false;
  }

  // -- managing capacity --
  if (arr->length >= arr->capacity) {
    bool success = double_data_capacity(arr);

    if (success == false) {
      return false;
    }
  }

  // -- inserting and pushing out the tail --
  size_t tail_length = arr->length - pos; // 2

  memmove(&arr->data[pos + 1], &arr->data[pos],
          sizeof *arr->data * tail_length);

  arr->length++;
  arr->data[pos] = val;

  return true;
}

bool int_arr_replace(int_arr *arr, size_t pos, int val) {}

//
// ---- remove ----
//

bool int_arr_pop(int_arr *arr, int *out) {}

bool int_arr_remove_at(int_arr *arr, size_t pos, int *out) {}
