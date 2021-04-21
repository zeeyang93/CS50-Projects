#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0) //compare if voted name is the same as the candidate array
        {
            preferences[voter][rank] = i; //add the correct candidate index number to the preference array
            return true;
        }
    }
    return false; //if ballot doesn't match name, vote is not legit
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++) //loop through preference array first index (voters)
    {
        for (int r = 0; r < candidate_count; r++) //loop through preference array second index (ranks preference)
        {
            int c = preferences [i][r]; //collect the candidate number we received from "vote" function
            if (candidates[c].eliminated == false) //if candidate is not eliminated
            {
                candidates[c].votes++;
                break; //this command stops the nested loop. It is required as we have to jump to the next voter
            }
        }

    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (voter_count / 2)) //if candidate votes is over half
        {
            printf("%s\n", candidates[i].name); //print winner name
            return true;
        }
    }

    return false; //if no winner, function is void
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int minimumVote = voter_count; //initialise a variable with max number of votes to make sure loop starts correctly
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < minimumVote && candidates[i].eliminated == false) //if candidate is not eliminated
        {
            minimumVote = candidates[i].votes;
            //minimumVote variable will now takes vote count of non-elimated candidate, and return it to main function
        }
    }
    return minimumVote; //return to main function
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int tieCount = 0; //variable for number of tie candidates
    int remainingCandidates = 0; //variable for on run candidates

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min) //if candidates have minimum votes
        {
            tieCount++;
            remainingCandidates++;
        }
        else if (candidates[i].eliminated == false) //to tabulate the number of remaining candidates
        {
            remainingCandidates++;
        }
    }
    if (tieCount == remainingCandidates)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
