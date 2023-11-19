#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
// For example,the score of letter 'A' is equal to POINTS[0], and letter 'B' is equal to POINTS[1]
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word, int points[]);
void toupper_sting(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1, POINTS);
    int score2 = compute_score(word2, POINTS);

    //compare score1 with score2
    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Use the case statement to go through every character in the string
// Return back the score of each player
// Mayber there is another better to compute the score?
// A little to long
// Need to be optimized
int compute_score(string word, int points[])
{
    // Compute and return score for string
    toupper_sting(word);
    int score = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        switch (word[i])
        {
            case 'A':
                score += points[0];
                break;
            case 'B':
                score += points[1];
                break;
            case 'C':
                score += points[2];
                break;
            case 'D':
                score += points[3];
                break;
            case 'E':
                score += points[4];
                break;
            case 'F':
                score += points[5];
                break;
            case 'G':
                score += points[6];
                break;
            case 'H':
                score += points[7];
                break;
            case 'I':
                score += points[8];
                break;
            case 'J':
                score += points[9];
                break;
            case 'K':
                score += points[10];
                break;
            case 'L':
                score += points[11];
                break;
            case 'M':
                score += points[12];
                break;
            case 'N':
                score += points[13];
                break;
            case 'O':
                score += points[14];
                break;
            case 'P':
                score += points[15];
                break;
            case 'Q':
                score += points[16];
                break;
            case 'R':
                score += points[17];
                break;
            case 'S':
                score += points[18];
                break;
            case 'T':
                score += points[19];
                break;
            case 'U':
                score += points[20];
                break;
            case 'V':
                score += points[21];
                break;
            case 'W':
                score += points[22];
                break;
            case 'X':
                score += points[23];
                break;
            case 'Y':
                score += points[24];
                break;
            case 'Z':
                score += points[25];
                break;
        }
    }

    return score;
}

//Compute the string case-insensitive!!!
// Make sure the letters in a sting that the user give are all uppercase letter
// If is is not a uppercase letter,then convert it into upper case

void toupper_sting(string word)
{
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            word[i] = toupper(word[i]);
        }
    }
}

