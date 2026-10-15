#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  // ---- numbers to string ----
  char s[10];
  float f = 3.14159;

  snprintf(s, 10, "%f", f); // take s and write at most 10 chars including \0

  printf("%s\n", s);

  // ---- string to numbers ----
  // atoi       String to Int
  // atof       String to Float
  // atol       String to Long Int
  // atoll      String to Long Long Int

  char *pi = "3.14159";

  f = atof(pi);

  printf("%f\n", f);

  printf(
      "%d\n",
      atoi(
          "what")); // do not do this! Sometimes gives back 0 but not guaranteed

  // strtol     String to Long Int
  // strtoll     String to Long Long Int
  // strtoul     String to Unsigned Long
  // strtoull    String to Unsigned Long Long
  // strtof      String to Float
  // strtod      String to Double
  // strtold     String to Long Double

  strcpy(s, "3490");

  // Convert string s to a number in base 10
  // NULL = don't care about error information
  unsigned long int x = strtoul(s, NULL, 10);

  printf("%lu\n", x);

  // We can do a different base if we want
  strcpy(s, "101010");

  x = strtoul(s, NULL, 2);

  printf("%lu\n", x);

  // handling errors
  strcpy(s, "34x90"); // invalid in base 10
  char *badchar;

  x = strtoul(s, &badchar, 10);

  if (*badchar == '\0') {
    printf("Successful conversion: %lu\n", x);
  } else {
    printf("Partial conversion: %lu\n", x);
    printf("Invalid character: %c\n", *badchar);
  }

  // ---- converting chars ----
  char c = '6';
  int n = c;
  int y = n - '0'; // numbers are guaranteed to be in sequence, starting at '0'

  printf("Char code point: %d\n", c);
  printf("Converted: %d\n", y);
  printf("Can do it the other way around: %c\n", (y + '0'));

  // ---- implicit conversions ----
  char a = 50, b = 52;

  int sum =
      a + b; // this converts a, b into ints during the arithmetic conversion

  printf("a: %c sizeof %d\n", a, sizeof(a));
  printf("b: %c sizeof %d\n", b, sizeof(b));
  printf("s: %c sizeof %d\n", sum, sizeof(sum));
}
