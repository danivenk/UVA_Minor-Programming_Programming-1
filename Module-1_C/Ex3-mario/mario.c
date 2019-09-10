// mario.c makes a piramid seen in mario with a height
//  which the user chooses (maximum of 23)
// Dani van Enk, 11823526

// including the standard I/O and standard library
#include <stdio.h>
#include <stdlib.h>

// predeclare used functions
int get_number_int(char str[128]);
long long power(int x, int y);

// main loop
int main(void)
{
    // defining SIZE and predefining the user_input
    int SIZE = 128;
    int user_input;

    // ask for a positive and less than 23 user input, else ask again
    do
    {
        user_input = get_number_int("What height would you like? ");
    }
    while (user_input < 0 || user_input > 23);


    // writing howmany lines the user defined
    for (int i = 0; i < user_input; i++)
    {
        // printing the left half piramid
        for (int j = user_input - i - 1; j > 0; j--)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        // printing the 2 character gap
        printf("  ");

        // printing the right half piramid
        for (int l = i; l >= 0; l--)
        {
            printf("#");
        }

        // make a new line
        printf("\n");
    }

    // exit program
    return 0;
}

// get_number_int prompts user with userdefined string (maxlen is 128)
// it only accepts integer values and converts them to a usable int variable
// dependencies: power() see below
// change get_number_int to get_number_long or get_number_longlong by changing
//  datatype of output and of the function
int get_number_int(char str[128])
{
    // output intializer
    int output = 0;

    // loop untill correct input
    while (1)
    {
        // predefine input, numbers and intialize powers
        int power_10 = 0;
        int found = 0;
        int size = 128;
        char input[size];
        char numbers[10] = "0123456789";

        // create a clean 0 filled input array
        for (int k = 0; k < 128; k++)
        {
            input[k] = 0;
        }

        // reset to 0 each loop
        output = 0;

        // promt user for input
        printf("%s", str);
        fgets(input, size, stdin);

        // loop for each position
        for (int i = size - 1; i >= 0; i--)
        {
            // convert the string to numbers
            for (int j = 0; j < 10; j++)
            {
                if (input[i] == numbers[j])
                {
                    // not forgetting to use the correct powers of 10
                    output += j * power(10, power_10);
                    power_10++;
                    found++;
                    break;
                }
                else
                {
                    found = 0;
                }
            }

            // ignoring zeros in the input and retry if non numerical
            if (input[i] == 0 || input[i] == '\n')
            {
                continue;
            }
            else if (found == 0)
            {
                break;
            }
        }

        // if numbers have been found break out of the ask sequence
        if (found != 0)
        {
            break;
        }
    }

    // return final result
    return output;
}

// power does x^y, where x and y are integers where y >= 0
long long power(int x, int y)
{
    // begin with 1 x
    long long result = x;

    // special cases for y = 0 and y = 1
    if (y == 0)
    {
        result = 1;
    }
    else if (y == 1)
    {
        return result;
    }
    else
    {
        // times x till y is gone
        while (y > 1)
        {
            result *= x;
            y--;
        }
    }

    // return the result
    return result;
}