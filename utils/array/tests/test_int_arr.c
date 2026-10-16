#include "../int_arr.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
  // ---- life cycle ----
  int_arr *arr = int_arr_create();

  assert(arr != NULL);

  int_arr_destroy(arr);
  printf("%d\n", sizeof *arr);
}
