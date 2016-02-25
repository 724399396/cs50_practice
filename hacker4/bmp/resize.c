#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Usage: ./resize scale input output");
        return 1;
    }
    
    double scale = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];
    
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Can't open %s\n", infile);
        return 2;
    }
    
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        printf("Can't create file %s\n", outfile);
        free(inptr);
        return 3;
    }
    
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 0x36 
        || bi.biCompression != 0 || bi.biSize != 0x28 || bi.biBitCount != 0x18)
    {
        printf("Unsupported file format\n");
        free(inptr);
        free(outptr);
        return 4;
    }
    
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    RGBTRIPLE image[abs(bi.biHeight)][bi.biWidth];
    for(int i = 0; i < abs(bi.biHeight); i++)
    {
        for(int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            image[i][j] = triple;
        }
        fseek(inptr,padding,SEEK_CUR);
    }
    
    bi.biWidth *= scale;
    bi.biHeight *= scale;
    bi.biSizeImage = 4 * bi.biWidth * bi.biHeight;
    bf.bfSize = bi.biSizeImage + 0x36;
    padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
     
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    for(int i = 0; i < abs(bi.biHeight); i++)
    {
        for(int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple = image[(int)(i / scale)][(int)(j / scale)];
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
        for(int k = 0; k < padding; k++)
        {
            fputc(0x00,outptr);
        }
    }
    
    fclose(outptr);
    fclose(inptr);
    return 0;
}