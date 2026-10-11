#include <stdio.h>

int main(void) {
  // ---- Read char by char ----
  FILE *fp;
  int c;

  fp = fopen("hello.txt", "r");

  while ((c = fgetc(fp)) != EOF) {
    printf("%c", c);
  }

  fclose(fp);

  // ---- Read line by line ----
  FILE *fq;
  char s[1024];
  int linecount = 0;

  fq = fopen("quote.txt", "r");

  while (fgets(s, sizeof s, fq) != NULL) {
    printf("%d: %s", ++linecount, s);
  }

  fclose(fq);

  // ---- Formatted input ----
  FILE *fwhales;
  char name[1024];
  float length;
  int mass;

  fwhales = fopen("whales.txt", "r");

  while (fscanf(fwhales, "%s %f %d", name, &length, &mass) != EOF) {
    printf("%s whale, %d tonnes, %.1f meters\n", name, mass, length);
  }

  fclose(fwhales);

  // ---- Writing text files ----
  FILE *output;
  int x = 32;

  output = fopen("output.txt", "w");

  fputc('B', output);
  fputc('\n', output);
  fprintf(output, "x = %d\n", x);
  fputs("Hellow world!\n", output);

  fclose(output);

  // stdout is a file, so we can output to the console with this
  FILE *console;

  console = stdout;

  fputc('B', console);
  fputc('\n', console);
  fprintf(console, "x = %d\n", x);
  fputs("Hellow world!\n", console);

  fclose(console);
}
