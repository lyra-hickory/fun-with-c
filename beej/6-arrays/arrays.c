#include <stdio.h>

// Constant
#define COUNT 5

// Example funcs
// Passing as a pointer to the first element
void times2(int *a, int len) {
  for (int i = 0; i < len; i++)
    printf("%d\n", a[i] * 2);
}

// Same thing, but using array notation
void times3(int a[], int len) {
  for (int i = 0; i < len; i++)
    printf("%d\n", a[i] * 3);
}

// Same thing, but using array notation with size
void times4(int a[5], int len) {
  for (int i = 0; i < len; i++)
    printf("%d\n", a[i] * 4);
}

void double_array(int *a, int len) {
  for (int i = 0; i < len; i++) {
    a[i] *= 2;
  }
}

void print_2d_array(int a[2][3]) {
  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 3; col++) {
      printf("%d ", a[row][col]);
    }
    printf("\n");
  }
}

int main(void) {
  // ---- 6.1 ----
  //
  int i;
  float f[4]; // Declare an array of 4 floats

  f[0] = 3.14159;
  f[1] = 1.41;
  f[2] = 1.41;
  f[3] = 1.41;

  for (i = 0; i < 4; i++) {
    printf("%f\n", f[i]);
  }

  // ---- 6.2 ----
  // So we don't have a stored array length natively
  int l = sizeof f / sizeof(float);
  printf("%d is the calculated length\n", l);

  printf("%d\n", sizeof(double[48]));

  // ---- 6.3 ----
  //
  int a[5] = {22, 37, 66, 77, 55}; // init array with values

  printf("a:\n");
  for (i = 0; i < 5; i++) {
    printf("%d\n", a[i]);
  }

  int b[10] = {0, 11, [5] = 55, 66, [9] = 77};

  printf("b:\n");
  for (i = 0; i < 10; i++) {
    printf("%d\n", b[i]);
  }

  int c[] = {1, 2, 3, 4};

  // ---- 6.4 ----
  // Undefined behaviour, bad bad
  printf("Out of bounds:\n");
  for (i = 0; i < 10; i++) {
    printf("%d\n", a[i]);
  }

  // ---- 6.5 ----
  //
  int d1[5];
  int d2[3][5];
  int d3[2][5][3];

  // multidimensional arrays needs bounds set
  int da[2][5] = {{0, 1, 2, 3, 4}, {10, 11, 12, 13, 14}};

  int x;
  int y;
  for (x = 0; x < 2; x++) {
    for (y = 0; y < 5; y++) {
      printf("%d\n", da[x][y]);
    }
  }

  // ---- 6.6 ----
  //
  printf("Pointer to arrays:\n");
  int *p;
  p = &a[0]; // p points to the first element
  printf("%d\n", *p);

  p = a; // This means the same as &a[0]
  printf("%d\n", *p);

  int e[5] = {11, 22, 33, 44, 55};
  times2(e, 5);
  times3(e, 5);
  times4(e, 5);

  double_array(e, 5);

  for (i = 0; i < 5; i++) {
    printf("%d, ", e[i]);
  }
  printf("\n");

  int ex[2][3] = {{1, 4, 6}, {5, 2, 7}};
  print_2d_array(ex);
}
