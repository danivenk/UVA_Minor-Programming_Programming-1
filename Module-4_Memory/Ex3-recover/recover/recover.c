/*
** recover.c recovers all JPG-files from a .raw-file
** Dani van Enk, 11823526
*/

// including used libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

// block size in words where a word is 32-bits
#define BLOCK_SIZE 16

// define DWORD as an unsigned 32bit integer
typedef uint32_t DWORD;

// define a BLOCK structure which saves all DWORDS of a BLOCK in an array
typedef struct
{
    DWORD words[BLOCK_SIZE];
} __attribute__((__packed__))
BLOCK;

// predefining used functions
void append_block_to_file(BLOCK *append_block, FILE *filepointer);

/*
** main loop with commandline arguments
*/
int main(int argc, char *argv[])
{
    // make sure at 1 commandline argument is given
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // remember filename
    char *infile = argv[1];

    // open input file for reading
    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;

        // close infile
        fclose(inptr);
    }

    // get file_size
    fseek(inptr, 0L, SEEK_END);
    int file_size = ftell(inptr);
    fseek(inptr, 0L, SEEK_SET);

    // initialize used variables
    bool file_found = false;
    int file_no = 0;
    FILE *outptr;

    // allocate memory for filename (3 numbers + .jpg\0 -> 8)
    char *file_name = malloc(8 * sizeof(char));
    if (!file_name)
    {
        fprintf(stderr, "Could not allocate memory.\n");


        // free allocated memory
        free(file_name);

        // close infile
        fclose(inptr);

        return 3;
    }

    // loop through the input filestream
    while (file_size > ftell(inptr))
    {
        // allocate memory for a block
        BLOCK *current_block = malloc(sizeof(BLOCK));
        if (!current_block)
        {
            fprintf(stderr, "Could not allocate memory.\n");

            // free allocated memory
            free(current_block);
            free(file_name);

            // close infile
            fclose(inptr);

            return 4;
        }

        // read 1 block of data from the input filestream (64 bytes)
        fread(current_block, sizeof(BLOCK), 1, inptr);

        // find the first word and split it into byte_4 and byte_1to3
        DWORD first_word = current_block->words[0];
        int byte_4 = (int)(first_word / pow(16, 6));
        int byte_1to3 = first_word % (int) pow(16, 6);

        // check for JPG identifier bytes
        bool JPG_check = (byte_1to3 == 0xffd8ff) &&
            (byte_4 >= 0xe0 && byte_4 < 0xf0);

        // if JPG has been found and no file is being made, create new file
        if (JPG_check && file_found == false)
        {
            // create a unique file_name
            sprintf(file_name, "%03d.jpg", file_no);

            // create a file with name file_name and open it for writing
            outptr = fopen(file_name, "w");

            // write current block to outputfile
            append_block_to_file(current_block, outptr);

            // declare file has found
            file_found = true;
        }
        // if a zero block has found or found JPG while making file, close file
        else if (JPG_check && file_found == true)
        {
            // close outfile, increase file count
            fclose(outptr);
            file_no++;

            // go back one block and declare found file has ended
            fseek(inptr, -sizeof(BLOCK), SEEK_CUR);
            file_found = false;
        }
        // if a JPG has been found write all following non-zero blocks
        else if (!JPG_check && file_found == true)
        {
            append_block_to_file(current_block, outptr);
        }

        // free allocated memory for current_block
        free(current_block);
    }

    // close files
    fclose(inptr);
    fclose(outptr);

    // free allocated memory for the filename
    free(file_name);

    // exit program
    return 0;
}

/*
** append_block_to_file() writes a block to a filestream
*/
void append_block_to_file(BLOCK *append_block, FILE *filepointer)
{
    // for every word in the block
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        // write it to the file stream
        DWORD current_word = append_block->words[i];
        fwrite(&current_word, sizeof(DWORD), 1, filepointer);
    }

    // exit
    return;
}