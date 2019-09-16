// Dani van Enk, 11823526

// including the standard I/O, standard library and ctype library
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        // defining SIZE and predefining the user_input
        int size = 2;
        char *hash = argv[1];
        char password[size];
        char salt[3] = {hash[0], hash[1]};

        for (int i = 0; i < size; i++)
        {
            password[i] = '\0';
        }

        while (1)
        {
            for (int i = 0; i <= size; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    for (int k = 65; k <= 122; k++)
                    {
                        if (k == 90)
                        {
                            k += 7;
                        }
                        password[j] = (char) k;

                        printf("Try: %s, i %d, j %d, k %d\n", password, i, j, k);

                        if (hash == crypt(password, salt))
                        {
                            printf("Found: %s\n", password);
                            return 0;
                        }
                    }
                }
            }

            return 0;
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