/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t  BYTE;

typedef struct 
{
    BYTE first;
    BYTE second;
    BYTE third;
    BYTE fouth;
    BYTE left[508]; 
} __attribute__((__packed__))
BLOCK;

int main(int argc, char* argv[])
{
    FILE *inptr = fopen("card.raw", "r");
    if (inptr == NULL) {
        printf("Can't open card.raw\n");    
    }
    
    int image_number = -1;
    
    int JPG_FIRST = 0xff;  
    int JPG_SECOND = 0xd8;
    int JPG_THIRD = 0xff;
    int JPG_FOURTH = 0xe0;
    
    BLOCK tmp;
    bool found = false;
    FILE *outptr = NULL;
    while (fread(&tmp, sizeof(BLOCK), 1, inptr) == 1) 
    {
        if(tmp.first == JPG_FIRST && tmp.second == JPG_SECOND 
            && tmp.third == JPG_THIRD && (tmp.fouth & 0xe0) == JPG_FOURTH)
        {
            found = true;
            image_number++;
            char outfile[8];
            sprintf(outfile, "%03x.jpg", image_number);
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            outptr = fopen(outfile,"w");
        }
        if (found)
        {
            fwrite(&tmp, sizeof(BLOCK), 1, outptr);
        }
    }

 

    if (feof(inptr))
    {
      fclose(inptr);
      return 0;
    }
    else
    {
      // some other error interrupted read
      printf("some error interruped read");
      fclose(inptr);
      return 1;
    }
}
