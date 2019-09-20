/*
** crack.c guesses the password (max 5 characters) when given a hash
** Dani van Enk, 11823526
*/

// including the used libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>
#include <string.h>

// predefining the used functions
char next_letter(char current_letter);
int no_of_z(char string[], int length);

/*
** main loop with the possibility of parameters
*/
int main(int argc, char *argv[])
{
    // only accepting 1 parameter when executing the code
    if (argc == 2)
    {
        /*
        ** defining size, position of least significant digit
        **  length, userdefined has, password, last password and salt.
        */
        int size = 6;
        int least_bit_pos = 0;
        int length = 1;
        char *hash = argv[1];
        char password[size];
        char lastpass[size];
        char salt[3] = {hash[0], hash[1]};

        // filling password and lastpass with zeros
        for (int i = 0; i < size; i++)
        {
            password[i] = '\0';
            lastpass[i] = '\0';
        }

        // looping for each try
        while (1)
        {
            // copy password onto lastpass
            for (int char1 = 0; char1 < size; char1++)
            {
                lastpass[char1] = password[char1];
            }

            /*
            ** if z is reached and the number of z is equal to length
            **  add a new character
            */
            if (lastpass[0] == 'z' && lastpass[least_bit_pos + 1] == '\0' &&
                no_of_z(lastpass, length) == length)
            {
                least_bit_pos++;
                length++;
                for (int char2 = least_bit_pos - 1; char2 >= 0; char2--)
                {
                    password[char2] = next_letter(lastpass[char2]);
                }
            }

            /*
            ** if z is reached and no new character is needed (no_of_z < length)
            **  set next letter for the more significant letter
            */
            if (lastpass[least_bit_pos] == 'z')
            {
                for (int char3 = length - 1; char3 >= 0; char3--)
                {
                    /*
                    ** for the next letter to be set, the less significant
                    **  letters must all be z, else break
                    */
                    if (lastpass[char3] == 'z')
                    {
                        password[char3 - 1] = next_letter(lastpass[char3 - 1]);
                    }
                    else
                    {
                        break;
                    }
                }
            }

            // next letter, least significant letter is on the right
            password[least_bit_pos] = next_letter(lastpass[least_bit_pos]);

            /*
            ** if the hash gotten from the guessed password is equal to
            **  the userdefined hash, correct password has been found
            */
            if (strcmp(hash, crypt(password, salt)) == 0)
            {
                printf("Found: %s\n", password);
                return 0;
            }
            // exit for an password larger than 5 characters
            else if (length > 5)
            {
                printf("Not Found 404\n");
                return 1;
            }
        }
    }
    // error message for not enough parameters
    else
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    // end program
    return 0;
}

/*
** next_letter() returns the next leter to the given letter
*/
char next_letter(char current_letter)
{
    // define current letter
    int i = (int) current_letter;

    // if Z is reached set letter to a
    if (i == 90)
    {
        i += 7;
    }
    // if z is reached set letter to A
    else if (i == 122 || i == 0)
    {
        i = 65;
    }
    // else just set to next letter
    else
    {
        i++;
    }

    // return character
    return (char) i;
}

/*
** no_of_z() returns the number of z in a string when given a string and length
*/
int no_of_z(char string[], int length)
{
    // begin with 0 z
    int no_z = 0;

    // loop over the characters of the string
    for (int i = 0; i < length; i++)
    {
        // if z is found increase no_z
        if (string[i] == 'z')
        {
            no_z++;
        }
    }

    // return the number of z
    return no_z;
}