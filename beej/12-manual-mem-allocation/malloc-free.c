#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  // ---- malloc ----
  int *p = malloc(sizeof(int));

  *p = 12;

  printf("%d\n", *p);

  free(p);

  int *x;

  if ((x = malloc(sizeof(int) * 10)) == NULL) {
    fprintf(stderr, "Error allocating 10 ints\n");
  } else {
    memset(x, 0, 10 * sizeof(int));
    free(x);
  }

  // ---- calloc ----
  int *q;

  if ((q = calloc(10, sizeof(int))) == NULL) {
    fprintf(stderr, "Error allocating 10 ints\n");
  } else {
    free(q);
  }

  // ---- realloc ----
  int *y;

  if ((y = calloc(10, sizeof(int))) == NULL) {
    fprintf(stderr, "Error allocating 10 ints\n");
  } else {
    y[5] = 10;
    // realloc returns a new pointer (possibly) and accepts the number of bytes
    if ((y = realloc(y, 20 * sizeof(int))) == NULL) {
      fprintf(stderr, "Error allocating 20 ints\n");
    } else {
      y[15] = 20;
      printf("y[5]: %d; y[15]: %d\n", y[5], y[15]);
      free(y);
    }
  }
}
