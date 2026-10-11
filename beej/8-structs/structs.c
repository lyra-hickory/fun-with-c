#include <stdio.h>

struct car {
  char *name;
  float price;
  int speed;
};

void set_price(struct car *c, float price) { (*c).price = price; }

void set_speed(struct car *c, int speed) { c->speed = speed; }

int main(void) {
  struct car saturn;

  saturn.name = "Saturn SL/2";
  saturn.price = 1999.99;
  saturn.speed = 175;

  printf("Name:         %s\n", saturn.name);
  printf("Price:        %f\n", saturn.price);
  printf("Top Speed:    %d km\n", saturn.speed);

  struct car suburu = {"Subuwu!", 16.99, 20};

  printf("Name:         %s\n", suburu.name);
  printf("Price:        %f\n", suburu.price);
  printf("Top Speed:    %d km\n", suburu.speed);

  struct car suburu2 = {.speed = 16, .price = 20.0, .name = "uwu"};

  printf("Name:         %s\n", suburu2.name);
  printf("Price:        %f\n", suburu2.price);
  printf("Top Speed:    %d km\n", suburu2.speed);

  set_price(&saturn, 99.9);
  set_speed(&saturn, 2000);
  printf("Saturn Price: %f\n", saturn.price);
  printf("Saturn Speed: %d\n", saturn.speed);

  struct car saturn2;
  saturn2 = saturn; // this does a shallow copy of the instance
  saturn2.name = "Second Saturn!";

  printf("Name:         %s\n", saturn2.name);
  printf("Price:        %f\n", saturn2.price);
  printf("Top Speed:    %d km\n", saturn2.speed);
}
