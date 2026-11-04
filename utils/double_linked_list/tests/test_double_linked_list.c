#include "../../testing_harness/testing_harness.h"
#include "../double_linked_list.c"

//
// ---- LIFETIME ----
//
int dll_list_test_create_destroy(void) {
  // Assemble
  struct dll_list *list = dll_list_create();

  // Assert
  ASSERT(list != NULL);

  // Destroy
  dll_list_destroy(list);
  return 0;
}

void test_type_destroy(void *data) { free(data); }

int dll_list_test_type_destroy(void) {
  // Assemble
  struct dll_list *list = dll_list_create();

  struct dll_type type = {.name = "destroy", .destroy = test_type_destroy};

  char *data = strdup("some data!");
  dll_list_add(list, data, &type);

  // Destroy
  dll_list_destroy(list);
  return 0;
}

SECTION_DEF(DLL_TEST_LIFETIME) {
  TEST(dll_list_test_create_destroy);
  TEST(dll_list_test_type_destroy);
}

//
// ---- NODE ADD ----
//
int dll_list_test_add_one(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  char *data = "test data!";

  // Act
  struct dll_node *node = dll_list_add(list, data, NULL);

  // Assert
  ASSERT(node != NULL);
  ASSERT(node->data == data);

  ASSERT(list->head == node);
  ASSERT(list->tail == node);
  ASSERT(list->length == 1);

  // Destroy
  dll_list_destroy(list);
  return 0;
}

int dll_list_test_add_two(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  char *data_1 = "test data!";
  char *data_2 = "more data!";

  // Act
  struct dll_node *node_1 = dll_list_add(list, data_1, NULL);
  struct dll_node *node_2 = dll_list_add(list, data_2, NULL);

  // Assert
  ASSERT(node_1 != NULL);
  ASSERT(node_2 != NULL);

  ASSERT(list->head == node_1);
  ASSERT(list->tail == node_2);
  ASSERT(list->length == 2);

  ASSERT(node_1->next == node_2);
  ASSERT(node_1->prev == NULL);

  ASSERT(node_2->next == NULL);
  ASSERT(node_2->prev == node_1);

  // Destroy
  dll_list_destroy(list);
  return 0;
}

int dll_list_test_one_with_type(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  char *data = "some data";
  struct dll_type type = {.name = "string", .destroy = NULL};

  // Act
  struct dll_node *node = dll_list_add(list, data, &type);

  // Assert
  ASSERT(node != NULL);
  ASSERT(node->type == &type);

  // Destroy
  dll_list_destroy(list);
  return 0;
}

SECTION_DEF(DLL_TEST_ADD) {
  TEST(dll_list_test_add_one);
  TEST(dll_list_test_add_two);
  TEST(dll_list_test_one_with_type);
}
//
// ---- MAIN ----
//
int main(void) {
  SECTION(DLL_TEST_LIFETIME);
  SECTION(DLL_TEST_ADD);

  RUN_TESTS();
}
