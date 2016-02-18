#include <stdio.h>
#include <cs50.h>

int checksum(long long int number);
int numlen(long long int number);
int get_special_bit(long long int number, int location, int length);
long long int ten_power(int time);
int add_by_bit(int number);

int main(void) 
{
    printf("Number: ");
    long long number = GetLongLong();
    int length = numlen(number);
    if (length < 13) {
        printf("INVALID\n");
    } else if (checksum(number) == 0)
    {
        int first = get_special_bit(number,1,length);
        int second = get_special_bit(number,2,length);
        if (first == 3)
        {
            if (second == 4 || second == 7)
            {
                printf("AMEX\n");
            }
        } else if (first == 5)
        {
            switch(second) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    printf("MASTERCARD\n"); break;
                default:
                    printf("INVALID\n");
            }
        } else if (first == 4) 
        {
            printf("VISA\n");    
        } else {
            printf("INVALID\n");
        }
    }
}

int numlen(long long int number)
{
    int length = 0;
    long long int i;
    for(i = number; i != 0; i /= 10) 
    {
        length++;
    }
    return length;
}

int checksum(long long int number) 
{
    int odd_sum = 0;
    int even_sum = 0;
    int length = numlen(number);
    for(int i = 1; i <= length; i++) 
    {
        if ((length - i)%2!=0) 
        {
            even_sum += add_by_bit(2 * get_special_bit(number,i,length));
        } else 
        {
            odd_sum += get_special_bit(number,i,length);
        }
    }
    return (even_sum + odd_sum) % 10;
}

int get_special_bit(long long int number, int location, int length)
{
    long long int base =  ten_power(length - location);
    return number % (base * 10) / base;
}

long long int ten_power(int time)
{
    long long int result = 1;
    for(; time > 0; time--) 
    {
        result *= 10;
    }
    return result;
}

int add_by_bit(int number)
{
    int length = numlen(number);
    if (length > 1)
    {
        return number % 10 + number / 10;
    } else 
    {
        return number;
    }
}