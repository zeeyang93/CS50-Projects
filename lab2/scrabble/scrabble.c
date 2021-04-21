#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int compute_score(string word);


//Main function once the program runs
int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("Tie!\n");
    }

}

//Function to calculate score from input of characters
int compute_score(string word)

{
    int score = 0;
    int var1 = 0;
    int var2 = 0;
    // TODO: Compute and return score for string
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        //checks for upper characters
        //converts word array to start from 0-25. To do that, minus off constant value 65 "A" or 97 "a"
        //Var1 and Var2 are new variables for the converted array value within 0-25
        if (isupper(word[i]))
        {
            var1 = word[i] - 'A';
            score += POINTS[var1];
        }

        else if (islower(word[i]))
        {
            var2 = word[i] - 'a';
            score += POINTS[var2];
        }
    }
    return score;
}