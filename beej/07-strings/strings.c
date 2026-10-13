#include <stdio.h>
#include <string.h>

int my_strlen(char *s) {
  int count = 0;

  while (s[count] != '\0')
    count++;

  return count;
}

int main(void) {
  char s[] = "Hello world!";

  printf("%s\n", s);

  for (int i = 0; i < 12; i++) {
    printf("%c", s[i]);
  }
  printf("\n");

  char *ss = "Hello, world!";
  char t[] = "Hello, again!";
  // s[0] = 'z'  // Don't do this, string literals are read-only memory tossed
  // into a chunk far far away
  t[0] = 'z'; // Safe! We can modify array slots
  printf("%s\n", t);

  printf("The string is %zu bytes long.\n", strlen(ss));
  printf("The string is %zu bytes long.\n", my_strlen(ss));

  char t_copy[100];  // enough room? 100 is plenty for us
  strcpy(t_copy, s); // This is a built in byte-for-byte string copy
  t_copy[0] = 'z';
  printf("%s\n", s);
  printf("%s\n", t_copy);
}
