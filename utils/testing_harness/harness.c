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

struct harness_test_item {
  char *name;
  harness_section_test_t test;

  struct harness_test_item *next;
};

struct harness_section {
  int total;
  int passed;
  int failed;

  char *name;
  struct harness_section *next;

  struct harness_test_item *tests_head;
  struct harness_test_item *tests_tail;
};

typedef void (*harness_section_register_t)(struct harness_section *h);

//
// ---- STRUCT CLEANUP ----
//

void harness_test_item_list_destroy(struct harness_test_item *head) {
  struct harness_test_item *h = head;

  while (h != NULL) {
    if (h->name != NULL) {
      free(h->name);
    }
    struct harness_test_item *next = h->next;
    free(h);
    h = next;
  }
}

void harness_section_list_destroy(struct harness_section *head) {
  struct harness_section *h = head;

  while (h != NULL) {
    if (h->name != NULL) {
      free(h->name);
    }

    if (h->tests_head != NULL) {
      harness_test_item_list_destroy(h->tests_head);
      h->tests_head = NULL;
      h->tests_tail = NULL;
    }

    struct harness_section *next = h->next;
    free(h);
    h = next;
  }
}

//
// ---- REGISTERS ----
//

struct harness_section *sections_head = NULL;
struct harness_section *sections_tail = NULL;

int total_tests = 0;
int total_passed = 0;
int total_failed = 0;

// ---- registers the test item ----
void harness_define_test_impl(struct harness_section *h,
                              harness_section_test_t test, char *test_name) {
  struct harness_test_item *test_item = malloc(sizeof *test_item);
  if (test_item == NULL) {
    fprintf(stderr, "ERROR: Failed to load test \"%s:%s\" | malloc failure\n",
            h->name, test_name);
    return;
  }

  test_item->name = malloc(strlen(test_name) + 1);
  if (test_item->name == NULL) {
    fprintf(stderr, "ERROR: Failed to load test \"%s:%s\" | malloc failure\n",
            h->name, test_name);
    free(test_item);
    return;
  }

  strcpy(test_item->name, test_name);
  test_item->test = test;
  test_item->next = NULL;

  // add test to section
  h->total++;
  h->tests_tail->next = test_item;
  h->tests_tail = test_item;
}
#define harness_define_test(h, fn) harness_define_test_impl(h, fn, #fn)

// ---- registers the test section ----
void harness_define_section_impl(harness_section_register_t register_section_fn,
                                 char *section_name) {
  struct harness_section *h = malloc(sizeof *h);
  if (h == NULL) {
    fprintf(stderr, "ERROR: Failed to load section \"%s\" | malloc failure\n",
            h->name);
    return;
  }

  // init the struct
  h->total = 0;
  h->passed = 0;
  h->failed = 0;
  h->tests_head = NULL;
  h->tests_tail = NULL;
  h->next = NULL;

  // name!
  char *s = malloc(strlen(section_name));
  if (s == NULL) {
    fprintf(stderr, "ERROR: Failed to load section \"%s\" | malloc failure\n",
            h->name);
    free(h);
    return;
  }
  h->name = s;

  // link 'em up with the tail
  if (sections_tail != NULL) {
    sections_tail->next = h;
  }

  // update the global list
  if (sections_head == NULL) {
    sections_head = h;
  }
  sections_tail = h;

  register_section_fn(h);
  total_tests += h->total;
}
#define harness_define_section(fn) harness_define_section_impl(fn, #fn)

//
// ---- RUNNER ----
//

void harness_run_tests(void) {
  printf("---- Running Testing Harness ----\n");

  struct harness_section *h = sections_head;

  while (h != NULL) {
    printf("---- Running : %s ----\n", h->name);

    struct harness_test_item *t = h->tests_head;

    while (t != NULL) {
      int result_code = t->test();

      if (result_code == 0) {
        h->passed++;
      } else {
        h->failed++;
        printf("TEST FAILED %s:%s, exit code %d\n", h->name, t->name,
               result_code);
      }

      t = t->next;
    }

    printf("%s | passed: %d | failed: %d\n\n", h->name, h->passed, h->failed);

    total_passed += h->passed;
    total_failed += h->failed;

    h = h->next;
  }

  printf("---- Ran %d tests ----\n", total_tests);
  printf("Total Passed: %d\n", total_passed);
  printf("Total Failed: %d\n", total_passed);

  harness_section_list_destroy(sections_head);
}

//
// ---- API ----
//

#define TEST(fn) harness_define_test(h, fn)
#define SECTION_DEF(fn) void fn(struct harness_section *h)
#define SECTION(fn) harness_define_section(fn)

#define ASSERT(c)                                                              \
  do {                                                                         \
    if (!(c)) {                                                                \
      fprintf(stderr, __FILE__ ":%d: assertion failed: %s\n", __LINE__, #c);   \
      return (1);                                                              \
    }                                                                          \
  } while (0)
