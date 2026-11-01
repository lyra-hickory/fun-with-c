# Testing Harness

A small testing harness for easily writing readable and expandable tests.

## Usage

```
int test_fn(void);  // Test function

SECTION_DEF(section_name) {  // Function definition for the group
  TEST(test_1);  // Registers the test to the group
  TEST(test_2);
  TEST(test_3);
}

int main(void) {
  SECTION(section_name);  // Registers the test group

  RUN_TESTS();  // Runs the tests!
}
```
