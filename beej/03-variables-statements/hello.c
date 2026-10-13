#include <stdio.h>
#include <stdbool.h>  // not needed in C23

int main(void) {
	// 
	// ____ Simple variables and printf ____
	//
	int i = 2;
	float f = 3.14;
	char * s = "Did you know # is also called an octothorpe";

	printf("%s i = %d and f = %f\n", s, i , f);

	//
	// ____ Booleans ____
	//
	int is_true = 1;  // True
	int is_false = 0;  // False
	bool x = true;

	if(x) {
		printf("x is true!\n");
	}

	printf("1 compared to true: %d\n", true == 1);
	printf("12 compared to true: %d\n", true == 12);

	//
	// ____ Operators ____
	//
	
	// Super basics
	
	// +
	i = i + 3;
	i += 3;

	// -
	i = i - 3;
	i -= 3;

	// *
	i = i * 9;
	i *= 9;

	// /
	i = i / 2;
	i /= 2;

	// %
	i = i % 5;
	i %= 5;

	// It has terinary operators!
	
	int y = 0;
	y += x > 10 ? 20 : 5;
	printf("The number %d is %s\n", x, x % 2 == 0 ? "even" : "odd");

	// Pre- and Post- increment
	
	int a = 10;
	int b = 5 + a++;  // Compute 5 + a *then* increment i
	printf("%d, %d\n", a, b);

	a = 10;
	b = 5 + ++a;  // Increment a, *then* compute 5 + a
	printf("%d, %d\n", a , b);

	// Sizeof
	
	// %zu for sizeof type
	printf("sizeof a : %zu\n", sizeof a);
	printf("sizeof 200 + 500 : %zu\n", sizeof(200 + 500));
	printf("sizeof 3.14 : %zu\n", sizeof 3.14);

	printf("sizeof int : %zu\n", sizeof(int));
	printf("sizeof float : %zu\n", sizeof(float));
	printf("sizeof char : %zu\n", sizeof(char));
}
