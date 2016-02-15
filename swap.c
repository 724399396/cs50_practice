#include <stdio.h>

void swap(int *a, int *b);

int main()
{
  int x = 1;
  int y = 2;
  printf("before swap, x is %d, y is %d\n", x, y);
  swap(&x, &y);
  printf("after swap, x is %d, y is %d\n", x, y);
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
