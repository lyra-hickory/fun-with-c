#include <stdio.h>

struct animal {
  char *name;
};

typedef struct animal animal;

typedef struct {
  char *name
} fish;

typedef float app_float; // in case we want to update the type

typedef float *float_ptr;

typedef int five_ints[5];

int main(void) {
  struct animal horse;
  animal zebra;

  five_ints my_five_ints;
}
