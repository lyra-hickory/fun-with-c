#include <stdio.h>

int main(void) {
  // ---- Writing binary ----
  FILE *fp;
  unsigned char bytes[6] = {5, 37, 0, 88, 255, 12};

  fp = fopen("output.bin", "wb"); // w = write ; b = binary

  fwrite(bytes, sizeof(char), 6, fp);

  fclose(fp);

  // ---- Reading binary ----
  FILE *fr;
  unsigned char c;

  fr = fopen("output.bin", "rb");

  while (fread(&c, sizeof(char), 1, fr) > 0) {
    printf("%d\n", c);
  }

  fclose(fr);
}
