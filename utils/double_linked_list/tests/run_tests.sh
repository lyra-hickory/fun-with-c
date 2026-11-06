gcc -g -fsanitize=address,undefined -Wall -Wextra -Wshadow -o test_double_linked_list test_double_linked_list.c ../../testing_harness/testing_harness.o \
&& ./test_double_linked_list
