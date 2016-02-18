 #define _XOPEN_SOURCE
 #include <unistd.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <cs50.h>
 #include <string.h>
 
 #define BASE_CHARACTER_LENGTH 64
 #define TEST_LENGTH 8
 
 char *salt_str(void);
 int numlen(long long int number);
 int get_special_bit(long long int number, int location, int length);
long long int base_power(int time);
 
 int main(int argc, char **argv)
 {
     if (argc != 2) {
         return 1; // arg number is not 1
     }
     char *crypto = argv[1];
     char *salt = salt_str();
     char *test_salt = malloc(2 + 1 * sizeof(char));
     for(int test_length = 1; test_length <= TEST_LENGTH; test_length++) {
         char *test_passwd = malloc(test_length + 1 * sizeof(char));
         for (int j = 0; j < base_power(test_length); j++) {
             for(int k = 0; k < test_length; k++) {
                 test_passwd[k] = salt[get_special_bit(j, k+1,test_length)];
             }
             test_passwd[test_length] = '\0';
             for (int m = 0; m < base_power(2); m++) {
                for(int n = 0; n < 2; n++) {
                     test_salt[n] = salt[get_special_bit(m, n+1,2)];
                }
                test_salt[2] = '\0';
                char *crypto_res = crypt(test_passwd, test_salt);
               
                if (strcmp(crypto_res, crypto) == 0) {
                    printf("%s\n", test_passwd);
                    free(test_passwd);
                    free(test_salt);
                    free(salt);
                    return 0;
                }
             }
        }
        free(test_passwd);
     }
    free(test_salt);
    free(salt);
 }

char *salt_str(void)
{
    char *salt = malloc(BASE_CHARACTER_LENGTH + 1 * sizeof(char));
    int i = 0;
    for(; i < 10; i++) {
        salt[i] = (char)'0' + i;
    }
    for(; i < 10 + 26; i++) {
        salt[i] = (char)'a' + i - 10;
    }
    for(; i < 10 + 26 + 26; i++) {
        salt[i] = (char)'A' + i - 26 -10;
    }

    salt[i++] = '.';
    salt[i++] = '/';
    salt[i] = '\0';
    return salt;
}

int numlen(long long int number)
{
    int length = 0;
    long long int i;
    for(i = number; i != 0; i /= BASE_CHARACTER_LENGTH) 
    {
        length++;
    }
    return length;
}

int get_special_bit(long long int number, int location, int length)
{
    long long int base =  base_power(length - location);
    return number % (base * BASE_CHARACTER_LENGTH) / base;
}

long long int base_power(int time)
{
    long long int result = 1;
    for(; time > 0; time--) 
    {
        result *= BASE_CHARACTER_LENGTH;
    }
    return result;
}
