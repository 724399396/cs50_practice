#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int minute;
    do {
        printf("minutes: ");
        minute = GetInt();
    } while (minute <= 0);
    int bottles = minute * 12;
    printf("bottles: %d", bottles);
}