#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct whale_bin_header {
  uint16_t count;
  char signature[4];
};

struct whale_bin {
  uint8_t name_length;
  char name[32];
  uint32_t length_scaled;
  uint32_t mass;
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

void print_all_bin(struct whale_bin *arr, int count) {
  for (int i = 0; i < count; i++) {
    printf("%d: name: %s ; length: %d ; mass: %d\n", i + 1, arr[i].name,
           arr[i].length_scaled, arr[i].mass);
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

int raise_read_err(FILE *fp) {
  perror("fread");
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

  fp = fopen(path, "wb");

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
    wc = fwrite(&whales_bin[i].length_scaled, sizeof(uint32_t), 1, fp);
    if (wc != 1)
      return raise_write_err(fp);

    // -- mass --
    wc = fwrite(&whales_bin[i].mass, sizeof(uint32_t), 1, fp);
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

int load_whales_bin(const char *path, struct whale_bin *arr, int limit) {
  FILE *fp;
  int i;
  int loaded;
  int skip_count = 0;
  int rc;

  fp = fopen(path, "rb");

  if (fp == NULL) {
    perror("fopen");
    return -1;
  }

  // -- signature --
  char sig_head[4];
  char expected_sig_head[] = {'W', 'H', 'L', '1'};

  for (i = 0; i < 4; i++) {
    rc = fread(&sig_head[i], sizeof(char), 1, fp);

    if (rc != 1)
      return raise_read_err(fp);

    if (sig_head[i] != expected_sig_head[i]) {
      fprintf(stderr, "load_whales_bin: bad signature in %s\n", path);
      fclose(fp);
      return -1;
    }
  }

  // -- count --
  uint16_t count;

  rc = fread(&count, sizeof(uint16_t), 1, fp);

  if (rc != 1)
    return raise_read_err(fp);

  // -- whales_bin --
  for (i = 0; i < count; i++) {
    // -- limit check --
    if (i == limit) {
      break;
    }

    // -- name size --

    uint8_t name_length = 0;
    rc = fread(&name_length, sizeof(uint8_t), 1, fp);

    if (rc != 1)
      return raise_read_err(fp);

    // -- name --
    char name[name_length];

    for (int c = 0; c < name_length; c++) {
      rc = fread(&name[c], sizeof(char), 1, fp);

      if (rc != 1)
        return raise_read_err(fp);
    }

    if (name[name_length - 1] != '\0') {
      printf("Skipping line %d due to malformed name\n", i);
      skip_count++;
      continue;
    }

    // -- length --
    uint32_t length_scaled = 0;
    rc = fread(&length_scaled, sizeof(uint32_t), 1, fp);

    if (rc != 1)
      return raise_read_err(fp);

    // -- mass --
    uint32_t mass = 0;
    rc = fread(&mass, sizeof(uint32_t), 1, fp);

    if (rc != 1)
      return raise_read_err(fp);

    // -- write to given array --
    arr[i].name_length = name_length;
    strcpy(arr[i].name, name);
    arr[i].length_scaled = length_scaled;
    arr[i].mass = mass;
  }

  loaded = i;

  // -- signature --
  char sig_footer[4];

  for (i = 0; i < 4; i++) {
    rc = fread(&sig_footer[i], sizeof(char), 1, fp);

    if (rc != 1)
      return raise_read_err(fp);

    if (sig_footer[i] != expected_sig_head[i]) {
      fprintf(stderr,
              "load_whales_bin: malaligned load, signature footer doesn't "
              "match for %s\n",
              path);
      fclose(fp);
      return -1;
    }
  }

  printf("Successfully loaded %d whales from binary, skipped %d\n",
         (loaded - skip_count), skip_count);
  fclose(fp);
  return (loaded - skip_count);
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

  struct whale_bin whales_bin[100];
  int loaded_bin = load_whales_bin("whales.bin", whales_bin, 100);

  print_all_bin(whales_bin, loaded_bin);
}
