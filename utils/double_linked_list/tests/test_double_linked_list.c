#include "../../testing_harness/testing_harness.h"
#include "../double_linked_list.c"
#include <stdlib.h>

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
  dll_list_add_tail(list, data, &type);

  // Destroy
  dll_list_destroy(list);
  return 0; // expected to raise an issue if left over data stays
}

SECTION_DEF(DLL_TEST_LIFETIME) {
  TEST(dll_list_test_create_destroy);
  TEST(dll_list_test_type_destroy);
}

//
// ---- NODE ADD ----
//

// -- add head --

int dll_list_test_add_head_one(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  char *data = "some data";

  // Act
  struct dll_node *node = dll_list_add_head(list, data, NULL);

  // Assert
  ASSERT(node != NULL);

  ASSERT(list->head == node);
  ASSERT(list->tail == node);
  ASSERT(list->length == 1);

  // Destroy
  dll_list_destroy(list);
  return 0;
}

int dll_list_test_add_head_two(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  char *data = "some data";

  // Act
  struct dll_node *node_1 = dll_list_add_head(list, data, NULL);
  struct dll_node *node_2 = dll_list_add_head(list, data, NULL);

  // Assert
  ASSERT(node_1 != NULL);
  ASSERT(node_2 != NULL);

  ASSERT(list->head == node_2);
  ASSERT(list->tail == node_1);

  ASSERT(node_1->prev == node_2);
  ASSERT(node_2->next == node_1);
  ASSERT(list->length == 2);

  // Destroy
  dll_list_destroy(list);
  return 0;
}

// -- add tail --

int dll_list_test_add_tail_one(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  char *data = "test data!";

  // Act
  struct dll_node *node = dll_list_add_tail(list, data, NULL);

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

int dll_list_test_add_tail_two(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  char *data_1 = "test data!";
  char *data_2 = "more data!";

  // Act
  struct dll_node *node_1 = dll_list_add_tail(list, data_1, NULL);
  struct dll_node *node_2 = dll_list_add_tail(list, data_2, NULL);

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

int dll_list_test_add_one_with_type(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  char *data = "some data";
  struct dll_type type = {.name = "string", .destroy = NULL};

  // Act
  struct dll_node *node = dll_list_add_tail(list, data, &type);

  // Assert
  ASSERT(node != NULL);
  ASSERT(node->type == &type);

  // Destroy
  dll_list_destroy(list);
  return 0;
}

// -- insert at --

int dll_list_test_insert_at_head(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  char *data = "some data";
  struct dll_node *tail = dll_list_add_tail(list, data, NULL);

  // Act
  struct dll_node *node = dll_list_insert_at(list, data, NULL, 0);

  // Assert
  ASSERT(node != NULL);

  ASSERT(list->head == node);
  ASSERT(list->tail == tail);
  ASSERT(list->length == 2);

  ASSERT(node->next == tail);
  ASSERT(tail->prev == node);

  // Destroy
  dll_list_destroy(list);
  return 0;
}

int dll_list_test_insert_at_tail(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  char *data = "some data";
  struct dll_node *head = dll_list_add_head(list, data, NULL);

  // Act
  struct dll_node *node = dll_list_insert_at(list, data, NULL, 1);

  // Assert
  ASSERT(node != NULL);

  ASSERT(list->head == head);
  ASSERT(list->tail == node);
  ASSERT(list->length == 2);

  ASSERT(head->next == node);
  ASSERT(node->prev == head);

  // Destroy
  dll_list_destroy(list);
  return 0;
}

int dll_list_test_insert_at_the_middle(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  char *data = "some data";
  struct dll_node *head = dll_list_add_head(list, data, NULL);
  struct dll_node *tail = dll_list_add_tail(list, data, NULL);

  // Act
  struct dll_node *node = dll_list_insert_at(list, data, NULL, 1);

  // Assert
  ASSERT(node != NULL);

  ASSERT(list->head == head);
  ASSERT(list->tail == tail);
  ASSERT(list->length == 3);

  ASSERT(head->next == node);
  ASSERT(node->prev == head);

  ASSERT(tail->prev == node);
  ASSERT(node->next == tail);

  // Destroy
  dll_list_destroy(list);
  return 0;
}

int dll_list_test_insert_at_index_5(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  struct dll_type dll_int = {.name = "name", .destroy = free};
  char *char_data = "some data";

  for (int i = 0; i < 10; i++) {
    int *num_data = malloc(sizeof *num_data);
    if (num_data == NULL) {
      dll_list_destroy(list);
      return 2; // exit code 2 for other failure
    }
    *num_data = i;
    dll_list_add_tail(list, num_data, &dll_int);
  }

  // Act
  struct dll_node *node = dll_list_insert_at(list, char_data, NULL, 5);

  // Assert
  ASSERT(node != NULL);

  ASSERT(*(int *)list->head->data == 0);
  ASSERT(*(int *)list->tail->data == 9);
  ASSERT(list->length == 11);

  struct dll_node *expected_node = list->head;
  for (int i = 0; i < 5; i++) {
    expected_node = expected_node->next;
  }
  ASSERT(expected_node == node);
  // when inserting between nodes, the neigbours are k-1 and k
  ASSERT(*(int *)node->prev->data == 4); // k-1
  ASSERT(*(int *)node->next->data == 5); // k

  // Destroy
  dll_list_destroy(list);
  return 0;
}

int dll_list_test_insert_at_out_of_bounds(void) {
  // Assemble
  struct dll_list *list = dll_list_create();
  char *data = "some data";

  // Act
  // TODO: reduce noise here, expected to get a stderr output
  struct dll_node *node = dll_list_insert_at(list, data, NULL, 5);

  // Assert
  ASSERT(node == NULL);

  ASSERT(list->head == NULL);
  ASSERT(list->tail == NULL);
  ASSERT(list->length == 0);

  // Destroy
  dll_list_destroy(list);
  return 0;
}

SECTION_DEF(DLL_TEST_ADD) {
  // add_head
  TEST(dll_list_test_add_head_one);
  TEST(dll_list_test_add_head_two);

  // add_tail
  TEST(dll_list_test_add_tail_one);
  TEST(dll_list_test_add_tail_two);
  TEST(dll_list_test_add_one_with_type);

  // insert_at
  TEST(dll_list_test_insert_at_head);
  TEST(dll_list_test_insert_at_tail);
  TEST(dll_list_test_insert_at_the_middle);
  TEST(dll_list_test_insert_at_index_5);
  TEST(dll_list_test_insert_at_out_of_bounds);
}

//
// ---- MAIN ----
//
int main(void) {
  SECTION(DLL_TEST_LIFETIME);
  SECTION(DLL_TEST_ADD);

  RUN_TESTS();
}
