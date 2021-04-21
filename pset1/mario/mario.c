
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get user input for Height, with conditions 1 <= h <= 8
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    //Set variable b = number of blocks, r = number of rows, s = number of spaces (or not)
    //NOTE TO SELF: pay attention to the actual number of variables within each loop!! Each loop is run individually

    for (int r = 1; r <= h; r++)
    {
        // Print spaces. Number of spaces = Height - Current Row. Hence loop start from highest value, and becomes smaller
        for (int s = h; s > r; s--)
        {
            printf(" ");
        }

        // Print hashes. Number of hashes = Current row. Usual loop function
        for (int b = 0; b < r; b++)
        {
            printf("#");
        }

        printf("  ");

        // Print right pyramid but with same concept as above.
        for (int b = 0; b < r; b++)
        {
            printf("#");
        }

        printf("\n");
    }


}