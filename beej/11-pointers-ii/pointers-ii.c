#include <stdio.h>
#include <string.h>

struct antelope {
  char *name;
};

int my_strlen(char *s) {
  char *p = s;

  while (*p != '\0') {
    p++;
  }

  return p - s;
}

void *my_memcpy(void *dest, void *src, int byte_count) {
  // convert void* to chars
  char *s = src, *d = dest;

  while (byte_count--) {
    *d++ = *s++;
  }

  return dest;
}

int main(void) {
  int a[] = {11, 22, 33, 44, 55, 999};

  int *p = &a[0];

  // iterate over our length, moving the pointed address up by each to go over
  // the cells in the array
  for (int i = 0; i < 5; i++) {
    printf("%d\n", *(p + i));
  }

  while (*p != 999) {
    printf("%d\n", *p);
    p++; // We can even increment pointers
  }

  char *my_str = "Meow meow!"; // 10 chars
  printf("Length of \"%s\": %d\n", my_str, my_strlen(my_str));

  // ---- array pointer equivalence ----
  p = a;

  printf("a[i]\n");
  for (int i = 0; i < 5; i++)
    printf("%d\n", a[i]);

  printf("p[i]\n");
  for (int i = 0; i < 5; i++)
    printf("%d\n", p[i]);

  printf("*(a + i)\n");
  for (int i = 0; i < 5; i++)
    printf("%d\n", *(a + i));

  printf("*(p + i)\n");
  for (int i = 0; i < 5; i++)
    printf("%d\n", *(p + i));

  // ---- void pointers ----
  // void* means we don't know what type

  char s[] = "Goats!";
  char t[100];

  memcpy(t, s, 7);
  // copy 7 bytes from starting address s into starting address t

  // int a[] = {11, 22, 33, 44, 55 };
  int b[5];

  memcpy(b, a, (3 * sizeof(int))); // 3 * ints worth of bytes

  // we can copy anything with memcpy
  struct antelope my_antelope;
  struct antelope my_clone_antelope;

  memcpy(&my_clone_antelope, &my_antelope, sizeof my_antelope);

  // casting void*
  char my_char = 'X';

  void *void_p_my_char = &my_char;
  char *p_my_char = void_p_my_char;

  // printf("%c\n", *void_p_my_char);  <- not allowed!
  printf("%c\n", *p_my_char); // allowed, we know it's a char now
}
