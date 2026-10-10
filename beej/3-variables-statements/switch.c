#include <stdio.h>

int main(void) {
	int goat_count = 2;

	// switch-case evaluates on integers
	switch (goat_count) {
		case 0:
			printf("You have no goats :(\n");
			break;
		case 1:
			printf("You have a singal goat!\n");
			break;
		case 2:
			printf("You have two goats!!\n");
			[[fallthrough]];  // This is c23 convention to indicate fallthrough to the next case
					  // excluding a break means it will move on to the case 3
		case 3:
			printf("You have three goats!!!\n");
			break;
		default:
			printf("You have soooo many goats! Wowzers\n");
	}
}
