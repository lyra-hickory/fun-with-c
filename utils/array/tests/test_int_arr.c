#include "../int_arr.c"
#include <assert.h>
#include <stdio.h>

// bool int_arr_test_(){}

//
// ---- life cycle ----
//

bool int_arr_test_create() {
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

bool int_arr_test_destroy() {
  int_arr *arr = int_arr_create();

  assert(arr != NULL);

  int_arr_destroy(arr);
  int_arr_destroy(NULL);

  return true;
}

//
// ---- append ----
//

bool int_arr_test_append_one_value() {
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

bool int_arr_test_append_ten_values() {
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
