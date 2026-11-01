#ifndef TESTING_HARNESS
#define TESTING_HARNESS

//
//  ---- TYPES & STRUCTS ----
//

typedef int (*harness_section_test_t)(void);

struct harness_test_item;

struct harness_section;

typedef void (*harness_section_register_t)(struct harness_section *harness_ctx);

//
// ---- REGISTERS ----
//

void harness_define_test_impl(struct harness_section *harness_ctx,
                              harness_section_test_t test, char *test_name);
#define harness_define_test(harness_ctx, fn)                                   \
  harness_define_test_impl(harness_ctx, fn, #fn);

void harness_define_section_impl(harness_section_register_t register_section_fn,
                                 char *section_name);
#define harness_define_section(fn) harness_define_section_impl(fn, #fn)

//
// ---- RUNNER ----
//

void harness_run_tests(void);

//
// ---- USER FACING ----
//

#define TEST(fn) harness_define_test(harness_ctx, fn)
#define SECTION_DEF(fn) void fn(struct harness_section *harness_ctx)
#define SECTION(fn) harness_define_section(fn)

#define ASSERT(c)                                                              \
  do {                                                                         \
    if (!(c)) {                                                                \
      fprintf(stderr, __FILE__ ":%d: assertion failed: %s\n", __LINE__, #c);   \
      return (1);                                                              \
    }                                                                          \
  } while (0)
#endif

#define RUN_TESTS() harness_run_tests()

//
// ---- USAGE ----
//

//
// test fn's return 0 as passed and any other code as failure
//
// SECTION_DEF for defining the sections, otherwise pass (struct
// harness_section *harness_ctx) into the section function
//
// SECTION accepts the section functions and registers them along with the
// tests
//
// TEST expects a (struct harness_section *h) passed in
//
// Run harness_run_tests in order to actually run the tests
//

/*
 * int test_true(void) { ASSERT(1); }
 *
 * SECTION_DEF(section_name) {
 *  TEST(test_true);
 * }
 *
 * int main(void) {
 *  SECTION(section_name);
 *  RUN_TESTS();
 * }
 */
