/*
** resize.c resizes a bmp file for a factor between 0.0 and 100.0
** Dani van Enk, 11823526
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

// defining global variable for the number of colors in RGB
#define RGB 3

// predefining used functions
void resize_header(BITMAPFILEHEADER *fileheader,
    BITMAPINFOHEADER *infoheader, double f);
void resize_data(int formats[4], float (*image_data)[formats[1]][RGB],
    float (*image_data_resize)[formats[3]][RGB]);

/*
** main loop with commandline arguments
*/
int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // create pointer for factor
    double *f = malloc(sizeof(double));

    // set pointer value to the userdefined factor
    *f = atof(argv[1]);
    if (!f)
    {
        fprintf(stderr, "Could not allocate memory.\n");

        // free allocated memory
        free(f);

        return 2;
    }

    // check for correct interval for the userdefined factor
    if (*f < 0 || *f >= 100)
    {
        fprintf(stderr, "Could not use this factor, " \
            "please choose an f in the interval (0,100]\n");

        return 3;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        fprintf(stderr, "Could not open %s.\n", infile);

        // free allocated memory
        free(f);

        return 4;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (!outptr)
    {
        fprintf(stderr, "Could not create %s.\n", outfile);

        // free allocated memory
        free(f);

        // close files
        fclose(inptr);

        return 5;
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
        fprintf(stderr, "Unsupported file format.\n");

        // free allocated memory
        free(f);

        // close files
        fclose(inptr);
        fclose(outptr);

        return 4;
    }

    // saving width and height of the original bmp-file
    int width = bi.biWidth;
    int height = abs(bi.biHeight);

    // change the resize parameters in the file and info headers
    resize_header(&bf, &bi, *f);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines (original and resized)
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_r = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // array with width and height (original and resized)
    int sizes[4] = {width, height, bi.biWidth, abs(bi.biHeight)};

    // allocate memory for data and data_resize
    float (*data)[sizes[1]][RGB] =
        malloc(sizeof(float[sizes[0]][sizes[1]][RGB]));
    float (*data_resize)[sizes[3]][RGB] =
        malloc(sizeof(float[sizes[2]][sizes[3]][RGB]));
    if (!data || !data_resize)
    {
        fprintf(stderr, "Could not allocate memory.\n");

        // free allocated memory
        free(f);

        // close files
        fclose(inptr);
        fclose(outptr);

        return 5;
    }

    // setting all entries of the resized dataset to 0 for now
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            data_resize[i][j][0] = 0;
            data_resize[i][j][1] = 0;
            data_resize[i][j][2] = 0;
        }
    }

    // iterate over infile's scanlines
    for (int i = 0; i < height; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // append to dataset array
            data[i][j][0] = triple.rgbtBlue;
            data[i][j][1] = triple.rgbtGreen;
            data[i][j][2] = triple.rgbtRed;
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // resize the data array to new size and put it in data_resize
    resize_data(sizes, data, data_resize);

    // iterate over infile's scanlines
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // write each pixel to the temp triple
            triple.rgbtBlue =  round(data_resize[i][j][0]);
            triple.rgbtGreen =  round(data_resize[i][j][1]);
            triple.rgbtRed =  round(data_resize[i][j][2]);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding_r; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // free up used space for f, data and data_resize
    free(f);
    free(data);
    free(data_resize);

    // success
    return 0;
}

/*
** resize_header changes the biWidth, biHeight, biSizeImage, bfSize when given
** a fileheader/infoheader pointer and a resize factor
*/
void resize_header(BITMAPFILEHEADER *fileheader,
    BITMAPINFOHEADER *infoheader, double f)
{
    // triple byte size
    int triple_byte_size = 3;

    // resize width/height and padding
    int resize_width = round(f * infoheader->biWidth);
    int resize_height = round(f * infoheader->biHeight);
    int padding = (4 - (resize_width * triple_byte_size) % 4) % 4;

    // change width and height in the header
    infoheader->biWidth = resize_width;
    infoheader->biHeight = resize_height;

    // change SizeImage and file Sie
    infoheader->biSizeImage =
        (padding + triple_byte_size*resize_width)*abs(resize_height);
    fileheader->bfSize = infoheader->biSizeImage + fileheader->bfOffBits;

    return;
}

/*
** resize_data transforms image_data to the size of image_data_resize
** the sizes are in the formats array and the data in the image_data array
** it returns void as specified
*/
void resize_data(int formats[4], float (*image_data)[formats[1]][RGB],
    float (*image_data_resize)[formats[3]][RGB])
{
    // calculating factored grid and original area
    int factored_width = formats[0] * formats[2];
    int factored_height = formats[1] * formats[3];
    float area = formats[0]*formats[1];

    // go over the factored grid
    for (int i = 0; i < factored_height; i++)
    {
        for (int j = 0; j < factored_width; j++)
        {
            // append the correct average over the overlapping pixels
            image_data_resize[i / formats[0]][j / formats[1]][0] +=
                image_data[i / formats[2]][j / formats[3]][0] / area;
            image_data_resize[i / formats[0]][j / formats[1]][1] +=
                image_data[i / formats[2]][j / formats[3]][1] / area;
            image_data_resize[i / formats[0]][j / formats[1]][2] +=
                image_data[i / formats[2]][j / formats[3]][2] / area;
        }
    }

    return;
}