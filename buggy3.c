#include <stdio.h>

void swap(int a, int b);

int main(void) {
  int x = 1;
  int y = 2;
  printf("x is %d\n", x);
  printf("y is %d\n", y);
  printf("start swap");
  swap(x, y);
  printf("end swap");
  printf("x is %d\n", x);
  printf("y is %d\n", y);
}

void swap(int a, int b) {
  int tmp = a;
  a = b;
  b = tmp;
}
