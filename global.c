#include <stdio.h>

//global variable
int x;

// function prototype
void increment(void);

int main(void)
{
  printf("x is %d\n", x);
  increment();
  printf("x is %d\n", x);
}


void increment(void)
{
  x++;
}
