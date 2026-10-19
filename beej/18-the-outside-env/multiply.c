#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("usage: mult x y\n");
    return EXIT_FAILURE;
  }

  int x = strtol(argv[1], NULL, 10);
  int y = strtol(argv[2], NULL, 10);

  printf("%d\n", (x * y));
  return EXIT_SUCCESS;
}
