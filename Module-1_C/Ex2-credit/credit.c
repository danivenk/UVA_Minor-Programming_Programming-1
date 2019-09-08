// credit.c Validates a credit card number and says if it is
//  an American Express, a MasterCard or a VISA credit card
// Dani van Enk, 11823526

//including standard I/O header
#include <stdio.h>

// predefining the used funcitons
int valid(long num);
long get_number_long(char str[128]);
long long power(int x, int y);

// main loop
int main(void)
{
    // get user credit card number and validate it
    long cred_num = get_number_long("Please type your credit-card number here: ");
    int validation = valid(cred_num);

    // find out which company the card is
    //  if not known say "INVALID" or if the card is not valid
    if (validation == 1)
    {
        if ((cred_num - 34 * power(10, 13) > 0 && cred_num - 35 * power(10, 13) < 0) ||
            (cred_num - 37 * power(10, 13) > 0 && cred_num - 38 * power(10, 13) < 0))
        {
            printf("AMEX\n");
        }
        else if (cred_num - 51 * power(10, 14) > 0 &&
                 cred_num - 56 * power(10, 14) < 0)
        {
            printf("MASTERCARD\n");
        }
        else if (cred_num - 4 * power(10, 15) > 0 &&
                 cred_num - 5 * power(10, 15) < 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    // end program
    return 0;
}

// valid() validates the card number
int valid(long num)
{
    // initialize variables
    long num1 = num / 10;
    long num2 = num;
    int first = 0;
    int second = 0;

    // double every other number starting with second to last
    while (num1 != 0)
    {

        // double digit
        int digit = 2 * (num1 - num1 / 10 * 10);

        // if the doubled digit is more than 10 add up the digits
        if (digit >= 10 && digit < 20)
        {
            int digitdigit = 0;

            // add up the digits of the double digit
            while (digit != 0)
            {
                digitdigit += (digit - digit / 10 * 10);
                digit /= 10;
            }

            // adding that to the first part of the validating sum
            first += digitdigit;
        }
        else if (digit > 20)
        {
            // if doubling the digit ends up being more then 20 something is wrong.
            printf("Something went wrong, please try again.\n");
            return 0;
        }
        else
        {
            // adding that to the first part of the validating sum
            first += digit;
        }

        // next digit
        num1 /= 100;
    }

    // adding up the remainig digits
    while (num2 != 0)
    {
        // adding them up
        second += (num2 - num2 / 10 * 10);

        // next digit
        num2 /= 100;
    }

    // if validating sum is multiple of 10, valid, if not, invalid
    if ((first + second) % 10 == 0)
    {
        return 1;
    }
    else
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