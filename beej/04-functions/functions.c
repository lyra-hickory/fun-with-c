#include <stdio.h>

int plus_one(int n) {
	return n + 1;
}

void hello(void) {
	printf("Hello!\n");
}

// ____ Prototype ____
int foo(int a);

int main(void) {
	int i = 10, j;

	j = plus_one(i);

	printf("i + 1 is %d\n", j);
	
	hello();

	printf("foo: %d\n", foo(i));
}

int foo(int a) {
	return ++a;
}


