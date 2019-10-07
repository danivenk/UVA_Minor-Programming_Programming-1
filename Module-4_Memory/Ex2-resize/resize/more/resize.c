// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

void resize_header(BITMAPFILEHEADER *bf, BITMAPINFOHEADER *bi, double f);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (!outptr)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // create pointer for factor
    double *f = (double *) malloc(sizeof(double));

    // set pointer value to the userdefined factor
    *f = atof(argv[1]);
    if (!f)
    {
        fprintf(stderr, "Could not allocate memory or f is out of bounds.\n");
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    fprintf(stdout, "Width %d\n", bi.biWidth);
    fprintf(stdout, "Height %d\n", bi.biHeight);
    fprintf(stdout, "SizeImage %d\n", bi.biSizeImage);
    fprintf(stdout, "Size %d\n", bf.bfSize);

    resize_header(&bf, &bi, *f);

    fprintf(stdout, "Width %d\n", bi.biWidth);
    fprintf(stdout, "Height %d\n", bi.biHeight);
    fprintf(stdout, "SizeImage %d\n", bi.biSizeImage);
    fprintf(stdout, "Size %d\n", bf.bfSize);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // free up used space for f
    free(f);

    // success
    return 0;
}

void resize_header(BITMAPFILEHEADER *bf, BITMAPINFOHEADER *bi, double f)
{
    int triple_byte_size = 3;

    int resize_width = round(f * bi->biWidth);
    int resize_height = round(f * bi->biHeight);
    int padding = 4 - resize_width % 4;

    bi->biWidth = resize_width;
    bi->biHeight = resize_height;

    bi->biSizeImage = triple_byte_size*(resize_width + padding)*abs(resize_height);
    bf->bfSize = bi->biSizeImage + bf->bfOffBits;

    return;
}