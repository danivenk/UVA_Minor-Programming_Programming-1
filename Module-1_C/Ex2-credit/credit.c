//Dani van Enk, 11823526

//including standard I/O header
#include <stdio.h>

char valid(long num);
long get_number_long(char str[128]);
long long power(int x, int y);

int main(void)
{
    long cred_num = get_number_long("Please type your credit-card number here: ");
    int validation = valid(cred_num);
    // char output

    // if (validation == 1)
    // {
    //     output = "VALID\n";
    // } else
    // {
    //     output = "INVALID\n";
    // }

    printf("%d\n", validation);

    return 0;
}

char valid(long num)
{
    long num1 = num/10;
    long num2 = num;
    int first = 0;
    int second = 0;

    while (num1 != 0)
    {

        int digit = 2*(num1 - num1/10*10);

        if (digit >= 10 && digit < 20)
        {
            int digitdigit = 0;

            while (digit != 0)
            {
                digitdigit += (digit - digit/10*10);
                digit /= 10;
            }

            first += digitdigit;
        } else if (digit > 20)
        {
            printf("Something went wrong, please try again.\n");
        } else
        {
            first += digit;
        }

        num1 /= 100;
    }

    while (num2 != 0)
    {
        second += (num2 - num2/10*10);

        num2 /= 100;
    }

    if ((first + second) % 10 == 0)
    {
        return 1;
    } else
    {
        return 0;
    }
}

// get_number_long prompts user with userdefined string (maxlen is 128)
// it only accepts integer values and converts them to a usable int variable
// dependencies: power() see below
// change get_number_long to get_number_int or get_number_longlong by changing
//  datatype of output and of the function
long get_number_long(char str[128])
{
    // output intializer
    long output = 0;

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
                    output += j*power(10, power_10);
                    power_10++;
                    found++;
                    break;
                }
            }

            // ignoring zeros in the input and retry if non numerical
            if (input[i] == 0)
            {
                continue;
            } else if (found == 0)
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
    } else if (y == 1)
    {
        return result;
    } else
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