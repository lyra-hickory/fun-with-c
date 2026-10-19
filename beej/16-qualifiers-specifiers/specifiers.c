#include <stdio.h>
void counter(void) {
  static int count = 1; // only initialised once per programme run

  printf("This has been called (%d) times!\n", count);

  count++;
}

int main(void) {
  counter(); // This has been called (1) times!
  counter(); // This has been called (2) times!
  counter(); // This has been called (3) times!

  static int foo; // auto assigns to 0;
  printf("foo: %d\n", foo);
}
