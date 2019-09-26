/* helper.c defines search and sort algorithms used for find.c
** Dani van Enk, 11823526
*/

// including used libraries
#include <cs50.h>
#include <stdio.h>
#include <math.h>

// including helpers header
#include "helpers.h"

/*
** Returns true if value is in array of n values, else false
*/
bool search(int value, int values[], int n)
{
    // only execute if specified length is positive
    if (n >= 0)
    {
        // predefining variables
        int pos = n / 2;
        int increment = n / 4;
        int search = 0;

        // find the half in which value is located
        do
        {
            // make sure the increment does not surpass 1
            if (increment < 1)
            {
                increment = 1;
            }

            // return true if value is found
            if (values[pos] == value)
            {
                return true;
            }
            // continue search in the left half if value is lower
            else if (values[pos] > value)
            {
                pos -= increment;
                search++;
            }
            // continue search in the right half if value is higher
            else if (values[pos] < value)
            {
                pos += increment;
                search++;
            }

            // break if pos goes outside values array or tried to many times
            if (pos > n || pos < 0 || search > n)
            {
                break;
            }

            // make increment half as much
            increment /= 2;
        } while (1);
    }

    // if not found return false
    return false;
}

/*
** Sorts array of n values
*/
void sort(int values[], int n)
{
    // predefine used variables
    int max_value = 65536;
    int value_counter[max_value];
    int counter1 = 0;

    // make all entries in the value_counter array 0
    for (int i = 0; i < max_value; i++)
    {
        value_counter[i] = 0;
    }

    // loop over the possible integer values
    for (int valcount = 0; valcount < max_value; valcount++)
    {
        // loop over the values array
        for (int valpos = 0; valpos < n; valpos++)
        {
            // add count in counting array if number is in value array
            if (valcount == values[valpos])
            {
                value_counter[valcount] += 1;
            }
        }
    }

    // loop over the counting array
    for (int valcount = 0; valcount < max_value; valcount++)
    {
        // append numbers sorted in the value array
        for (int counter2 = 0; counter2 < value_counter[valcount] &&
                value_counter[valcount] != 0; counter2++)
            values[counter1 + counter2] = valcount;

        counter1 += value_counter[valcount];
    }

    // exit function
    return;
}