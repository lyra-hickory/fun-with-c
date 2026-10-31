//
// ---- INCLUDE ----
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
//  ---- TYPES & STRUCTS ----
//
typedef int (*harness_section_test_t)(void);

struct harness_test_s {
  char *name;
  harness_section_test_t test;
};

struct harness_section_s {
  int total;
  int passed;
  int failed;

  char *name;
  struct harness_test_s *tests;
};

typedef void (*harness_section_t)(struct harness_section_s *h);

//
// ---- REGISTERS ----
//

struct harness_section_s *sections;

int total_tests = 0;
int total_passed = 0;
int total_failed = 0;

// ---- registers the test ----
void harness_define_test_impl(struct harness_section_s *h,
                              harness_section_test_t test, char *test_name) {
  struct harness_test_s *t = malloc(sizeof *t);
  if (!t) {
    fprintf(stderr, "ERROR: Failed to load test \"%s:%s\" | malloc failure\n",
            h->name, test_name);
    return;
  }

  t->name = malloc(strlen(test_name) + 1);
  if (!t->name) {
    fprintf(stderr, "ERROR: Failed to load test \"%s:%s\" | malloc failure\n",
            h->name, test_name);
    free(t);
    return;
  }

  strcpy(t->name, test_name);
  t->test = test;

  // add test to section
  h->total++;
}
#define harness_define_test(h, f) harness_define_test_impl(h, f, #f)

void harness_test_s_destroy(struct harness_test_s *test) {
  if (test == NULL)
    return;

  free(test->name);
  free(test);
}

// ---- registers the test section ----
void harness_define_section_impl(harness_section_t section,
                                 char *section_name) {
  struct harness_section_s h = {
      .total = 0, .passed = 0, .failed = 0, .name = section_name};

  section(&h);

  printf("\n---- %s ----\n", h.name);
  for (int i = 0; i < h.total; i++) {
    int r = h.tests[i].test();
    if (r == 0) {
      h.passed++;
    } else {
      h.failed++;
      printf("%s:%s FAILED: exit code %d\n", h.name, h.tests[i].name, r);
    }
  }
}
#define harness_define_section(f) harness_define_section_impl(f, #f)

//
// ---- MOCK ----
//
int mock_test_1() { return 0; }
int mock_test_2() { return 0; }
int mock_test_3() { return 0; }

void mock_section_1(struct harness_section_s *h) {
  harness_define_test(h, mock_test_1);
  harness_define_test(h, mock_test_2);
  harness_define_test(h, mock_test_3);
}

void mock_section_2(struct harness_section_s *h) {
  harness_define_test(h, mock_test_1);
  harness_define_test(h, mock_test_2);
  harness_define_test(h, mock_test_3);
}

int main(void) {
  harness_define_section(mock_section_1);
  harness_define_section(mock_section_2);
}
