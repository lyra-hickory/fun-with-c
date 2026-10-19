#include <stdio.h>
#include <stdlib.h>
int main(void) {
  char *val = getenv("FROTZ");

  if (val == NULL) {
    printf("Cannot find the FROTZ environment variable\n");
    return EXIT_FAILURE;
  }

  printf("FROTZ: %s\n", val);
}
