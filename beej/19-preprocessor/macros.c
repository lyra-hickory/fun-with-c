#include <stdio.h>
#include <stdlib.h>

#define HELLO "# is also called an octothorpe"
#define PI 3.14159

#define EXTRA_HAPPY
#define HAPPY_FACTOR 5

#define MODE_1

int main(void) {
  printf("%s, %f\n", HELLO, PI);

#ifdef EXTRA_HAPPY
  printf("I am extra happy! :)\n");
#endif

#ifndef EXTRA_HAPPY
  printf("I ok :|\n");
#endif

#ifdef EXTRA_HAPPY
  printf("Yayayay\n");
#else
  printf("meh\n");
#endif

// C23
#ifdef MODE_1
  printf("mode 1\n");
#elifdef MODE_2
  printf("mode 2\n");
#elifdef MODE_3
  printf("mode 3\n");
#else
  printf("mode n/a\n");
#endif

#if HAPPY_FACTOR == 0
  printf("I'm not happy!\n");
#elif HAPPY_FACTOR == 1
  printf("I'm a little bit happy\n");
#elif HAPPY_FACTOR >= 2
  printf("I'm very happy!\n");
#endif

#if defined FOO
  printf("foo~\n");
#elif !defined FOO
  printf("bar!\n");
#endif

#define GOATS
#ifdef GOATS
  printf("beej sure likes goats\n");
#endif
#undef GOATS
#ifdef GOATS
  printf("no goats here, beej\n");
#endif

  printf("\n");
  printf("------\n");
  printf("\n");
  printf("This function: %s\n", __func__);
  printf("This file: %s\n", __FILE__);
  printf("This line: %d\n", __LINE__);
  printf("Compiled on: %s %s\n", __DATE__, __TIME__);
  printf("C Version: %ld\n", __STDC_VERSION__);
  printf("\n");
  printf("------\n");
  printf("\n");

  // all of the paranthesis to avoid order of operations
#define SQR(x) ((x) * (x))

#define SQR_WRONG(x) x *x

  printf("%d\n", SQR(12));
  printf("%d\n", SQR_WRONG(3 + 7));
  printf("%d\n", SQR(3 + 7));

#define TRIANGLE_AREA(w, h) (0.5 * (w) * h)

#define X(a, b, ...) (10 * (a) + 20 * (b)), __VA_ARGS__
  printf("%d %f %s %d\n", X(5, 4, 3.14, "Hi!", 12));

#define S(...) #__VA_ARGS__
  printf("%s\n", S('m', 1, 4, "meow"));

#define PRINT_INT_VAL(x) printf("%s = %d\n", #x, x)
  int a = 5;
  PRINT_INT_VAL(a);

#define CAT(a, b) a##b
  printf("%f\n", CAT(3.14, 1592));

#define ASSERT_ENABLED 1
#if ASSERT_ENABLED
#define ASSERT(c, m)                                                           \
  do {                                                                         \
    if (!(c)) {                                                                \
      fprintf(stderr, __FILE__ ":%d: assertion %s failed: %s\n", __LINE__, #c, \
              m);                                                              \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)
#else
#define ASSERT(c, m)
#endif
  ASSERT((5 < 3), "oh no!");

  int random_ints[5] = {
      0
      // #embed "/dev/random" __limit__(5)
  };
  for (int i = 0; i < 5; i++)
    printf("%d\n", random_ints[i]);
}
