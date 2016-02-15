#include <stdio.h>

int increment(int a);

int main(int argc, char* argv[])
{
    int x = 2;
    printf("x is now %d\n", x);
    printf("Increamenting...\n");
    x = increment(x);
    printf("Incremented!\n");
    printf("x is now %d\n", x);
}

int increment(int a)
{
  return a + 1;
}
