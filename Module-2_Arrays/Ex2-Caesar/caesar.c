// caesar.c encodes a user text using the Caesar Cipher, with a userdefined key
// Dani van Enk, 11823526

// including the standard I/O, standard library and ctype library
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// main loop with the accepted parameters
int main(int argc, char *argv[])
{
    // only accepting 1 parameter when executing the code
    if (argc == 2)
    {
        // defining SIZE and predefining the user_input
        int size = 1028;
        int ciph_key = atoi(argv[1]) % 26;
        char input[size];
        char output[size];

        // initializing output with NULL
        for (int j = 0; j < size; j++)
        {
            output[j] = '\0';
        }

        // promting user_input
        printf("Enter message: ");
        fgets(input, size, stdin);

        // begin printing the output
        printf("ciphertext: ");

        // encoding the input message
        for (int i = 0; i < size; i++)
        {
            // changing the capital letters
            if (input[i] != '\n' && (input[i] >= 65 && input[i] <= 90))
            {
                output[i] = (input[i] + ciph_key - 65) % 26 + 65;
            }
            // changing the lowercase letters
            else if (input[i] != '\n' && (input[i] >= 97 && input[i] <= 122))
            {
                output[i] = (input[i] + ciph_key - 97) % 26 + 97;
            }
            // breaking if at end of string
            else if (input[i] == '\n' || input[i] == '\0')
            {
                break;
            }
            // keep punctuation and numerical characters the same
            else
            {
                output[i] = input[i];
            }
        }

        // printing the full output
        printf("%s\n", output);
    }
    // error message for not enough parameters
    else
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }

    // end program
    return 0;
}