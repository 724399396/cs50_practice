#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char *name = GetString();
    int find_letter = 0;
    int length = strlen(name);
    for(int i = 0; i < length; i++)
    {
        char c = name[i];
        if (c == ' ') {
            find_letter = 0;
        } else {
            if (!find_letter) {
                printf("%c", toupper(c));
            }
            find_letter = 1;
        }
    }
    printf("\n");
}