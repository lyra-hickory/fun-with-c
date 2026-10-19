#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
  int total = 0;

  for (int i = 1; i < argc; i++) {
    int val = strtol(argv[i], NULL, 10);

    total += val;
  }

  printf("Your total is: %d\n", total);
}
