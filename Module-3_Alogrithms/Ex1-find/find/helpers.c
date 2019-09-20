// Helper functions

#include <cs50.h>
#include <stdio.h>
#include <math.h>

#include "helpers.h"

// Returns true if value is in array of n values, else false
bool search(int value, int values[], int n)
{
    if (n >= 0)
    {
        int pos = pow(2, -1) * n;

        for (int i = -2; i > log2(1 / n); i--)
        {
            int increment = pow(2, i) * n;
            if (increment < 1)
            {
                increment = 1;
            }

            printf("%d, %d\n", pos, increment);
            if (values[pos] == value)
            {
                return true;
            }
            else if (values[pos] > value)
            {
                pos -= increment * n;
            }
            else if (values[pos] < value)
            {
                pos += increment * n;
            }

        }
    }
    // TODO: implement a searching algorithm
    return false;
}

// Sorts array of n values
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    return;
}
