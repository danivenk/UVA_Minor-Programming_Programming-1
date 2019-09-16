// Dani van Enk, 11823526

// including the standard I/O, standard library and ctype library
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>

char next_letter(char current_letter);
int no_of_z(char string[], int length);

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        // defining SIZE and predefining the user_input
        int size = 6;
        int least_bit_pos = 0;
        int length = 1;
        int roll_over = 0;
        int next_digit = 0;
        char *hash = argv[1];
        char password[size];
        char lastpass[size];
        char salt[3] = {hash[0], hash[1]};
        char input = 0;

        for (int i = 0; i < size; i++)
        {
            password[i] = '\0';
            lastpass[i] = '\0';
        }

        while (1)
        {
            for (int i = 0; i < size; i++)
            {
                lastpass[i] = password[i];
            }

            if (lastpass[0] == 'z' && lastpass[least_bit_pos + 1] == '\0' &&
                no_of_z(lastpass, length) == length)
            {
                least_bit_pos++;
                length++;
                for (int i = least_bit_pos - 1; i >= 0; i--)
                {
                    password[i] = next_letter(lastpass[i]);
                }
            }
            password[least_bit_pos] = next_letter(lastpass[least_bit_pos]);

            // printf("Try: %s, Length: %d\n", password, length);

            for (int i = 1; i <= length; i++)
            {
                if (lastpass[i] == 'z' && (lastpass[i + 1] == 'z' || lastpass[i + 1] == '\0'))
                {
                    password[i - 1] = next_letter(lastpass[i - 1]);
                    if (length > 3 && no_of_z(lastpass, size) >= 2)
                    {
                        fgets(&input, size, stdin);
                        printf("Try: %s\n", password);
                    }
                }
            }

            // printf("Try: %s, Length: %d\n", password, length);


            // printf("Try: %s\n", password);


            // if (password[0] == 'z' && password[1] == 'z')
            // {
            //     fgets(&input, size, stdin);
            // }
            if (hash == crypt(password, salt))
            {
                printf("Found: %s\n", password);
                return 0;
            }
            else if (length > 5)
            {
                printf("Not Found 404\n");
                return 1;
            }

            //fgets(&input, size, stdin);
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

char next_letter(char current_letter)
{
    int i = (int) current_letter;
    if (i == 90)
    {
        i += 7;
    }
    else if (i == 122 || i == 0)
    {
        i = 65;
    }
    else
    {
        i++;
    }

    return (char) i;
}

int no_of_z(char string[], int length)
{
    int no_z = 0;
    for (int i = 0; i < length; i++)
    {
        if (string[i] == 'z')
        {
            no_z++;
        }
    }

    return no_z;
}