#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
bool makes_circle(int winner, int loser);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int a = 0; a < candidate_count; a++)
    {
        int i = ranks[a]; // i = 1, a = 1 ranks[] = {2, 0, 1}
        // "3" is the winner to "1" and "2", and we have 3 records. 1.that "2" is winner and "0" is loser
        // 2."2" is winner and "1" is loser
        // 3,"0" is winner and "1" is loser
        for (int b = a + 1; b < candidate_count; b++)
        {
            int j = ranks[b];
            preferences[i][j]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int vote_difference[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        vote_difference[i] = preferences[winner][loser] - preferences[loser][winner];
    }

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i; j++)
        {
            if (vote_difference[i] < vote_difference[i + 1])
            {
                // 优化TODO: use a swap function
                int temp = vote_difference[i];
                vote_difference[i] = vote_difference[i + 1];
                vote_difference[i + 1] = temp;
                pair temp2 = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp2;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int winner, loser;
    for (int i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;
        // 优化：TODO: use a detect function
        if (!makes_circle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// makes_circle is referenced from stackoverflow
bool makes_circle(int winner, int loser)
{
    if (winner == loser)
    {
        return true;
    }

    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[loser][j] == true)
        {
            // Recursively check if there is an circle
            // If there is an circle, aka: "winner" == "loser", return ture
            // And we will skip this pairs
            if (makes_circle(winner, j) == true)
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int winner;
    for (int j = 0; j < candidate_count; j++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == true)
            {
                break;
            }
            else if (i == candidate_count - 1)
            {
                winner = j;
                printf("%s\n", candidates[j]);
            }
        }
    }
    return;
}
