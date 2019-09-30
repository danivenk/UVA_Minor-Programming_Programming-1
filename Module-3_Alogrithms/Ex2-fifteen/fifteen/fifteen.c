/* Implements Game of Fifteen (generalized to d x d)
** Dani van Enk, 11823526
*/

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Constants
#define DIM_MIN 3
#define DIM_MAX 9
#define COLOR "\033[32m"

// Board
int board[DIM_MAX][DIM_MAX];

// Dimensions
int d;

// Prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

/*
** main loop with parameter arguments
*/
int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        int tile = get_int("Tile to move: ");

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(50000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/*
** clears screen using ANSI escape sequences
*/
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/*
** greets player
*/
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/*
** Initializes the game's board with tiles numbered 1 through d*d - 1
** (i.e., fills 2D array with values but does not actually print them)
*/
void init(void)
{
    // defining the maximum integer on the board
    int max_int = d * d - 1;

    // create the board from top left to lower right & highest to lowest integer
    for (int row = 0; row < d; row++)
    {
        for (int column = 0; column < d; column++)
        {
            board[row][column] = max_int;
            max_int--;
        }
    }

    // if the dimension is an even number, swap the 1 and 2
    if (d % 2 == 0)
    {
        board[d - 1][d - 2] = 2;
        board[d - 1][d - 3] = 1;
    }

    // put a _ in the lower right most position
    board[d - 1][d - 1] = '_';
}

/*
** prints the board in its current state
*/
void draw(void)
{
    // looping over every position
    for (int row = 0; row < d; row++)
    {
        for (int column = 0; column < d; column++)
        {
            // printing out the 2D array/board with space corrections for > 10
            if (board[row][column] != '_' && board[row][column] > 9)
            {
                printf("%d ", board[row][column]);
            }
            else if  (board[row][column] != '_' && board[row][column] <= 9)
            {
                printf("%d  ", board[row][column]);
            }
            // print the empty space
            else
            {
                printf("%c  ", board[row][column]);
            }
        }

        // print newline for every row
        printf("\n");
    }
}

/*
** if tile borders empty space, moves tile and returns true, else returns false
*/
bool move(int tile)
{
    // loop over every position in the 2D array/on the board
    for (int row = 0; row < d; row++)
    {
        for (int column = 0; column < d; column++)
        {
            // check if the neighboring position is the _ character and swap it
            if (board[row][column] == tile && board[row - 1][column] == '_')
            {
                board[row - 1][column] = tile;
                board[row][column] = '_';
                return true;
            }
            else if(board[row][column] == tile && board[row][column - 1] == '_')
            {
                board[row][column - 1] = tile;
                board[row][column] = '_';
                return true;
            }
            else if(board[row][column] == tile && board[row + 1][column] == '_')
            {
                board[row + 1][column] = tile;
                board[row][column] = '_';
                return true;
            }
            else if(board[row][column] == tile && board[row][column + 1] == '_')
            {
                board[row][column + 1] = tile;
                board[row][column] = '_';
                return true;
            }
        }
    }

    // return false for illegal move
    return false;
}

/*
** returns true if game is won (i.e., board is in winning configuration), else false
*/
bool won(void)
{
    // defining used variables
    int win_check = 0;
    int checking_number = 1;

    // loop over all positions in the 2D array/on the board
    for (int row = 0; row < d; row++)
    {
        for (int column = 0; column < d; column++)
        {
            // _ must be in the lower right most position
            if (board[d - 1][d - 1] == '_')
            {
                // check if all numbers are in order
                if (board[row][column] == checking_number)
                {
                    win_check += 1;
                    checking_number++;
                }
            }
        }
    }

    // return for correct order else return false
    if (win_check == d * d - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
