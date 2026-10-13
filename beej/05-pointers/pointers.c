#include <stdio.h>

void increment(int *a) {
	*a = *a + 1;
}

int main(void) {
	int i = 10;

	printf("The value of i is %d\n", i);
	printf("The sizeof of i is %zu\n", sizeof(i));
	printf("The address of i is %p\n", (void *)&i);
	// (void *) is a type coercion so that the compiler doesn't complain
	
	int *p;  // int * = pointer of type int
	p = &i;  // point p to i's address
	printf("The value of p is %p\n", p);

	printf("The value of dereferenced p is %d\n", *p);

	// We can even reassign it with the indirection operator
	*p = 20;
	printf("i is now %d\n", i);

	increment(p);
	printf("p got passed and i got incremented!\n");
	printf("i is now %d\n", i);

	increment(&i);
	printf("&i got passed and i got incremented!\n");
	printf("i is now %d\n", i);

	// Meant as a placeholder, will be pointing to garbage
	int *n = NULL;

	int a, *b;  // a = int ; b = pointer to int
	int *c, d;  // c = pointer ; d = int
	int* e, f;  // e = pointer ; f = int
	// * is tied to the variable, not the type declaration
}
