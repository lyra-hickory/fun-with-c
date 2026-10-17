#include "../int_arr.c"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

// bool int_arr_test_(){}

//
// ---- life cycle ----
//

bool int_arr_test_create(void) {
  // Assemble
  int_arr *arr = int_arr_create();

  // Assert
  assert(arr != NULL);
  assert(arr->data != NULL);
  assert(arr->capacity == INT_ARR_INITIAL_CAPACITY);
  assert(arr->length == 0);

  // Destroy
  int_arr_destroy(arr);

  return true;
}

bool int_arr_test_destroy(void) {
  int_arr *arr = int_arr_create();

  assert(arr != NULL);

  int_arr_destroy(arr);
  int_arr_destroy(NULL);

  return true;
}

//
// ---- append ----
//

bool int_arr_test_append_one_value(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return false;

  int val = 10;

  // Act
  bool res = int_arr_append(arr, val);

  if (!res)
    return false;

  // Assert
  assert(arr->length == 1);
  assert(arr->data[0] == val);

  // Destroy
  int_arr_destroy(arr);

  return true;
}

bool int_arr_test_append_ten_values(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return false;

  int val_list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // Act
  for (int i = 0; i < 10; i++) {
    bool res = int_arr_append(arr, val_list[i]);

    if (!res)
      return false;
  }

  // Assert
  assert(arr->length == 10);
  for (int i = 0; i < 10; i++)
    assert(arr->data[i] == val_list[i]);

  // Destroy
  int_arr_destroy(arr);

  return true;
}

bool int_arr_test_append_catch_too_large_capacity(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return false;

  size_t too_big_for_more = SIZE_MAX / 2 + 100; // bigger than we should allow

  arr->capacity = too_big_for_more;
  arr->length = too_big_for_more;

  // Act
  bool res = int_arr_append(arr, 1); // should fail

  // Assert
  assert(res == false);
  assert(arr->capacity == too_big_for_more); // remain unchanged
  assert(arr->length == too_big_for_more);   // remain unchanged

  // Destroy
  int_arr_destroy(arr);

  return true;
}

bool int_arr_test_append_catch_zero_capacity(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return false;

  arr->capacity = 0;

  // Act
  bool res = int_arr_append(arr, 1);

  if (!res)
    return false;

  // Assert
  assert(arr->capacity ==
         INT_ARR_INITIAL_CAPACITY); // sets the 0 capacity to our initial
  assert(arr->length == 1);         // addedd successfully
  assert(arr->data[0] == 1);

  // Destroy
  int_arr_destroy(arr);

  return true;
}

//
// ---- insert ----
//

bool int_arr_test_insert_at_front(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return false;

  for (int i = 0; i < 10; i++) {
    bool res = int_arr_append(arr, i);

    if (!res)
      return false;
  }

  int val = 99;
  int pos = 0;

  // Act
  bool res = int_arr_insert(arr, pos, val);

  if (!res)
    return false;

  // Assert
  assert(arr->length == 11);
  assert(arr->data[pos] == val);

  // Destroy
  int_arr_destroy(arr);

  return true;
}

bool int_arr_test_insert_at_tail(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return false;

  for (int i = 0; i < 10; i++) {
    bool res = int_arr_append(arr, i);

    if (!res)
      return false;
  }

  int val = 99;
  int pos = 10;

  // Act
  bool res = int_arr_insert(arr, pos, val);

  if (!res)
    return false;

  // Assert
  assert(arr->length == 11);
  assert(arr->data[pos] == val);

  // Destroy
  int_arr_destroy(arr);

  return true;
}

bool int_arr_test_insert_from_empty(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return false;

  // Act
  for (int i = 0; i < 10; i++) {
    bool res = int_arr_insert(arr, i, i);

    if (!res)
      return false;
  }

  // Assert
  assert(arr->length == 10);
  for (int i = 0; i < 10; i++) {
    assert(arr->data[i] == i);
  }

  // Destroy
  int_arr_destroy(arr);

  return true;
}

bool int_arr_test_insert_catch_out_of_bounds(void) {
  // Assemble
  int_arr *arr = int_arr_create();
  if (arr == NULL)
    return false;

  for (int i = 0; i < 10; i++) {
    bool res = int_arr_append(arr, i);

    if (!res)
      return false;
  }

  int val = 99;
  int pos = 99;

  // Act
  bool res = int_arr_insert(arr, pos, val);

  // Assert
  assert(res == false);
  assert(arr->length == 10);

  // Destroy
  int_arr_destroy(arr);

  return true;
}

int main(void) {
  printf("---- Starting int_arr test suite ----\n\n");
  int total_tests = 0;
  int passed_count = 0;
  int failure_count = 0;
  char *failures[100] = {0};

  bool test_passed = false;
  bool has_failed = false;

  printf("---- life cycle ----\n");
  {
    has_failed = false;

    test_passed = int_arr_test_create();
    total_tests++;
    if (test_passed) {
      passed_count++;
    } else {
      failures[failure_count++] = "Failure: int_arr_test_create";
      has_failed = true;
    }

    test_passed = int_arr_test_destroy();
    total_tests++;
    if (test_passed) {
      passed_count++;
    } else {
      failures[failure_count++] = "Failure: int_arr_test_destroy";
      has_failed = true;
    }

    if (!has_failed)
      printf("Passed: ok!\n\n");
  }

  printf("---- append ----\n");
  {
    has_failed = false;

    test_passed = int_arr_test_append_one_value();
    total_tests++;
    if (test_passed) {
      passed_count++;
    } else {
      failures[failure_count++] = "Failure: int_arr_test_append_one_value";
      has_failed = true;
    }

    test_passed = int_arr_test_append_ten_values();
    total_tests++;
    if (test_passed) {
      passed_count++;
    } else {
      failures[failure_count++] = "Failure: int_arr_test_append_ten_values";
      has_failed = true;
    }

    test_passed = int_arr_test_append_catch_too_large_capacity();
    total_tests++;
    if (test_passed) {
      passed_count++;
    } else {
      failures[failure_count++] =
          "Failure: int_arr_test_append_catch_too_large_capacity";
      has_failed = true;
    }

    test_passed = int_arr_test_append_catch_zero_capacity();
    total_tests++;
    if (test_passed) {
      passed_count++;
    } else {
      failures[failure_count++] =
          "Failure: int_arr_test_append_catch_zero_capacity";
      has_failed = true;
    }

    if (!has_failed)
      printf("Passed: ok!\n\n");
  }

  printf("---- insert ----\n");
  {
    has_failed = false;

    test_passed = int_arr_test_insert_at_front();
    total_tests++;
    if (test_passed) {
      passed_count++;
    } else {
      failures[failure_count++] = "Failure: int_arr_test_insert_at_front";
      has_failed = true;
    }

    test_passed = int_arr_test_insert_at_tail();
    total_tests++;
    if (test_passed) {
      passed_count++;
    } else {
      failures[failure_count++] = "Failure: int_arr_test_insert_at_tail";
      has_failed = true;
    }

    test_passed = int_arr_test_insert_from_empty();
    total_tests++;
    if (test_passed) {
      passed_count++;
    } else {
      failures[failure_count++] = "Failure: int_arr_test_insert_from_empty";
      has_failed = true;
    }

    test_passed = int_arr_test_insert_catch_out_of_bounds();
    total_tests++;
    if (test_passed) {
      passed_count++;
    } else {
      failures[failure_count++] =
          "Failure: int_arr_test_insert_catch_out_of_bounds";
      has_failed = true;
    }

    if (!has_failed)
      printf("Passed: ok!\n\n");
  }

  printf("---- Tests done ----\n");
  {
    printf("Tests passed: %d/%d\n", passed_count, total_tests);

    if (failure_count > 0) {
      printf("Failing tests:\n");

      for (int i = 0; i < failure_count; i++)
        printf("%s\n", failures[i]);
    } else {
      printf("All Passed: ok!\n");
    }
  }
}
