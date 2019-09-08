// Bottles per water in a shower session
// Dani van Enk, 11823526

// including standard I/O header
#include <stdio.h>

// include selfmade functions
int get_number_int(char str[128]);
long long power(int x, int y);

// main loop
int main(void)
{
    // user input
    int minutes =
        get_number_int("How many minutes do you shower? (in whole minutes) ");

    // conversion to bottles
    int bottles = 1.5 * 128 / 16 * minutes;

    // output
    printf("This costs you %d bottles of water!\n", bottles);

    // exit main loop
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
        char input[128];
        char numbers[10] = "0123456789";
        int power_10 = 0;
        int found = 0;

        // create a clean 0 filled input array
        for (int k = 0; k < 128; k++)
        {
            input[k] = 0;
        }

        // reset to 0 each loop
        output = 0;

        // promt user for input
        printf("%s", str);
        scanf("%s", &input[0]);

        // loop for each position
        for (int i = 127; i >= 0; i--)
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
            }

            // ignoring zeros in the input and retry if non numerical
            if (input[i] == 0)
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
    int result = x;

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