#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct whale_bin_header {
  uint8_t count;
  char signature[4];
};

struct whale_bin {
  uint8_t name_length;
  char name[32];
  uint16_t length_scaled;
  uint16_t mass;
};

struct whale {
  char name[32];
  float length;
  int mass;
};

void print_all(struct whale *arr, int count) {
  for (int i = 0; i < count; i++) {
    printf("%d: name: %s ; length: %.1f ; mass: %d\n", i + 1, arr[i].name,
           arr[i].length, arr[i].mass);
  }
}

struct whale *find_heaviest(struct whale *arr, int count) {
  struct whale *heaviest = &arr[0];

  for (int i = 0; i < count; i++) {
    if (arr[i].mass > heaviest->mass) {
      heaviest = &arr[i];
    }
  }

  return heaviest;
}

int raise_write_err(FILE *fp) {
  perror("fwrite");
  fclose(fp);
  return -1;
}

int save_binary(const char *path, struct whale *arr, int count) {
  int i;

  // Header definitions
  struct whale_bin_header header = {.count = count,
                                    .signature = {'W', 'H', 'L', '1'}};

  // Casting our whales to our desired binary format
  struct whale_bin whales_bin[count];
  for (i = 0; i < count; i++) {
    // Casting the whales_bin
    strcpy(whales_bin[i].name, arr[i].name);
    whales_bin[i].name_length =
        strlen(arr[i].name) + 1; // include the terminator char \0
    whales_bin[i].length_scaled = arr[i].length * 10;
    whales_bin[i].mass = arr[i].mass;
  }

  // Writing to the binary file
  FILE *fp;

  fp = fopen("whales.bin", "wb");

  if (fp == NULL) {
    perror("fopen");
    return -1;
  }

  int wc;
  // -- signature --
  wc = fwrite(header.signature, sizeof(char), 4, fp);
  if (wc != 4)
    return raise_write_err(fp);

  // -- whale count --
  wc = fwrite(&header.count, sizeof header.count, 1, fp);
  if (wc != 1)
    return raise_write_err(fp);

  for (i = 0; i < header.count; i++) {
    // -- name length --
    wc = fwrite(&whales_bin[i].name_length, sizeof whales_bin[i].name_length, 1,
                fp);
    if (wc != 1)
      return raise_write_err(fp);

    // -- name --
    wc =
        fwrite(whales_bin[i].name, sizeof(char), whales_bin[i].name_length, fp);
    if (wc != whales_bin[i].name_length)
      return raise_write_err(fp);

    // -- length --
    wc = fwrite(&whales_bin[i].length_scaled, sizeof(uint16_t), 1, fp);
    if (wc != 1)
      return raise_write_err(fp);

    // -- mass --
    wc = fwrite(&whales_bin[i].mass, sizeof(uint16_t), 1, fp);
    if (wc != 1)
      return raise_write_err(fp);
  }

  // -- signature --
  wc = fwrite(header.signature, sizeof(char), 4, fp);
  if (wc != 4)
    return raise_write_err(fp);

  fclose(fp);
  printf("Successfully wrote %d whales to %s\n", header.count, path);

  return 0;
}

int load_whales(const char *path, struct whale *whales, int limit) {
  // Load the file
  FILE *fp;

  fp = fopen(path, "r");

  if (fp == NULL) {
    perror("fopen");
    return -1;
  }

  char line[1024]; // bigger than any line we expect to encounter
  int line_num = 0;
  int count = 0;

  char name[32];
  float length;
  int mass;

  while (count < limit && fgets(line, sizeof line, fp) != NULL) {
    line_num++;

    int n = sscanf(line, "%31s %f %d", name, &length, &mass);

    if (n == 3) {
      strcpy(whales[count].name, name);
      whales[count].length = length;
      whales[count].mass = mass;

      count++;
    } else {
      printf("Line %d: skipped (malformed)\n", line_num);
    }
  }

  printf("Successfully loaded %d whales\n", count);

  fclose(fp);

  return count;
}

int main(void) {
  struct whale whales[100] = {0};

  int loaded = load_whales("001-whales.txt", whales, 100);

  if (loaded <= 0) {
    return 1;
  }

  print_all(whales, loaded);

  struct whale *heaviest = find_heaviest(whales, loaded);
  printf("Heaviest: name: %s; length: %.1f; mass: %d\n", heaviest->name,
         heaviest->length, heaviest->mass);

  save_binary("whales.bin", whales, loaded);
}
