#include <stdio.h>
#include <cs50.h>

void print_half_pyramids(int size, int max_size);
void print_n_times(int n, char *c);

int main(void)
{
    int height;
    do {
        printf("Enter a non-negative integer < 24: ");
        height = GetInt();
    } while (height >= 24);
    for(int i = 1; i <= height; i++) {
        print_half_pyramids(i, height);
    }
}

void print_half_pyramids(int size, int max_size)
{
    print_n_times(max_size - size," ");
    print_n_times(size, "#");
    print_n_times(2, " ");
    print_n_times(size, "#");
    printf("\n");
}

void print_n_times(int n, char *c)
{
    for(int i = n; i > 0; i--)
    {
        printf("%s",c);
    }
}