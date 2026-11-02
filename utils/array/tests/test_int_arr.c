#include "../../testing_harness/testing_harness.h"
#include "../int_arr.c"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

//
// ---- life cycle ----
//

int int_arr_test_create(void) {
  // Assemble
  int_arr *arr = int_arr_create();

  // Assert
  ASSERT(arr != NULL);
  ASSERT(arr->data != NULL);
  ASSERT(arr->capacity == INT_ARR_INITIAL_CAPACITY);
  ASSERT(arr->length == 0);

  // Destroy
  int_arr_destroy(arr);

  return 0;
}

int int_arr_test_destroy(void) {
  int_arr *arr = int_arr_create();

  ASSERT(arr != NULL);

  int_arr_destroy(arr);
  int_arr_destroy(NULL);

  return 0;
}

SECTION_DEF(int_arr_test_life_cycle) {
  TEST(int_arr_test_create);
  TEST(int_arr_test_destroy);
}

//
// ---- append ----
//

int int_arr_test_append_one_value(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return 1;

  int val = 10;

  // Act
  bool res = int_arr_append(arr, val);

  if (!res)
    return 1;

  // Assert
  ASSERT(arr->length == 1);
  ASSERT(arr->data[0] == val);

  // Destroy
  int_arr_destroy(arr);

  return 0;
}

int int_arr_test_append_ten_values(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return 1;

  int val_list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // Act
  for (int i = 0; i < 10; i++) {
    bool res = int_arr_append(arr, val_list[i]);

    if (!res)
      return 1;
  }

  // Assert
  ASSERT(arr->length == 10);
  for (int i = 0; i < 10; i++)
    ASSERT(arr->data[i] == val_list[i]);

  // Destroy
  int_arr_destroy(arr);

  return 0;
}

int int_arr_test_append_catch_too_large_capacity(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return 1;

  size_t too_big_for_more = SIZE_MAX / 2 + 100; // bigger than we should allow

  arr->capacity = too_big_for_more;
  arr->length = too_big_for_more;

  // Act
  bool res = int_arr_append(arr, 1); // should fail

  // Assert
  ASSERT(res == false);
  ASSERT(arr->capacity == too_big_for_more); // remain unchanged
  ASSERT(arr->length == too_big_for_more);   // remain unchanged

  // Destroy
  int_arr_destroy(arr);

  return 0;
}

int int_arr_test_append_catch_zero_capacity(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return 1;

  arr->capacity = 0;

  // Act
  bool res = int_arr_append(arr, 1);

  if (!res)
    return 1;

  // Assert
  ASSERT(arr->capacity ==
         INT_ARR_INITIAL_CAPACITY); // sets the 0 capacity to our initial
  ASSERT(arr->length == 1);         // addedd successfully
  ASSERT(arr->data[0] == 1);

  // Destroy
  int_arr_destroy(arr);

  return 0;
}

SECTION_DEF(int_arr_test_append) {
  TEST(int_arr_test_append_one_value);
  TEST(int_arr_test_append_ten_values);
  TEST(int_arr_test_append_catch_too_large_capacity);
  TEST(int_arr_test_append_catch_zero_capacity);
}

//
// ---- insert ----
//

int int_arr_test_insert_at_front(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return 1;

  for (int i = 0; i < 10; i++) {
    bool res = int_arr_append(arr, i);

    if (!res)
      return 1;
  }

  int val = 99;
  int pos = 0;

  // Act
  bool res = int_arr_insert(arr, pos, val);

  if (!res)
    return 1;

  // Assert
  ASSERT(arr->length == 11);
  ASSERT(arr->data[pos] == val);

  // Destroy
  int_arr_destroy(arr);

  return 0;
}

int int_arr_test_insert_at_tail(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return 1;

  for (int i = 0; i < 10; i++) {
    bool res = int_arr_append(arr, i);

    if (!res)
      return 1;
  }

  int val = 99;
  int pos = 10;

  // Act
  bool res = int_arr_insert(arr, pos, val);

  if (!res)
    return 1;

  // Assert
  ASSERT(arr->length == 11);
  ASSERT(arr->data[pos] == val);

  // Destroy
  int_arr_destroy(arr);

  return 0;
}

int int_arr_test_insert_from_empty(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return 1;

  // Act
  for (int i = 0; i < 10; i++) {
    bool res = int_arr_insert(arr, i, i);

    if (!res)
      return 1;
  }

  // Assert
  ASSERT(arr->length == 10);
  for (int i = 0; i < 10; i++) {
    ASSERT(arr->data[i] == i);
  }

  // Destroy
  int_arr_destroy(arr);

  return 0;
}

int int_arr_test_insert_catch_out_of_bounds(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return 1;

  for (int i = 0; i < 10; i++) {
    bool res = int_arr_append(arr, i);

    if (!res)
      return 1;
  }

  int val = 99;
  int pos = 99;

  // Act
  bool res = int_arr_insert(arr, pos, val);

  // Assert
  ASSERT(res == false);
  ASSERT(arr->length == 10);

  // Destroy
  int_arr_destroy(arr);

  return 0;
}

SECTION_DEF(int_arr_test_insert) {
  TEST(int_arr_test_insert_at_front);
  TEST(int_arr_test_insert_at_tail);
  TEST(int_arr_test_insert_from_empty);
  TEST(int_arr_test_insert_catch_out_of_bounds);
}

int main(void) {
  SECTION(int_arr_test_life_cycle);
  SECTION(int_arr_test_append);
  SECTION(int_arr_test_insert);

  RUN_TESTS();
}
