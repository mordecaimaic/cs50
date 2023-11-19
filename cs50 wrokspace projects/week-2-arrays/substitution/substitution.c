#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define wrong_key 1
#define ERROR 1
int check_key(int argc, char argv[]);
bool check_upper(char letter);
bool check_lower(char letter);
void keep_uppercase(char *letter);
void keep_lowercase(char *letter);

int main(int argc, char *argv[])
{
    int status;
    // Use the function check_key to ensure that the use input a correct key that is replaceable
    if (check_key(argc, arg v[1]))
    {
        return ERROR;
    }
    string text = get_string("plaintext: ");
    int length = strlen(text);
    int num = 0;

    // Replace the every single letter in the plaint_text according to the key that the user input
    for (int i = 0; i < length; i++)
    {
        if (check_upper(text[i]))
        {
            num = text[i] - 'A';
            text[i] = argv[1][num];
            // Make sure the uppercase letter still is uppercase
            keep_uppercase(&text[i]);
        }
        else if (check_lower(text[i]))
        {
            num = text[i] - 'a';
            text[i] = argv[1][num];
            // Make sure the lowercase letter still is lowercase
            keep_lowercase(&text[i]);
        }
        //printf("chang the %i letter into %c\n", i, argv[1][num]);
    }

    printf("ciphertext: %s\n", text);
}

// Check the key
int check_key(int argc, char message[])
{
    int status = 0;
    int count = 0;
    char alphabet [26] = "abcdefghijklmnopqrstuvwxyz";
    // Check if the user has typed only 2 command-line arguments
    // If not, exit the programe with status 1 and promt the user about the usage
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        status = ERROR;
        return status;
    }
    int length = strlen(message);
    // Check if the user have type 26 character in command-line argument[1]
    if (length != 26)
    {
        printf("Key must contain 26 characters.\n");
        status = ERROR;
        return status;
    }
    // Check if the key the user input contain 26 different letters, if contain the same character, return false
    for (int i = 0; i < length; i++)
    {
        if (message[i] < 'A' || (message[i] > 'Z' && message[i] < 'a') || message[i] > 'z')
        {
            printf("Key must contain only alphabetic characters.\n");
            status = ERROR;
            return status;
        }

        for (int j = 0; j < 26; j++)
        {
            // Use the alphabet to identify that the use type 26 different letters
            if (alphabet[j] == message[i] || alphabet[j] == message[i] + 32 || alphabet[j] == message[i] - 32)
            {
                alphabet[j] = 0;
                count++;
            }
        }
    }
    if (count != 26)
    {
        status = ERROR;
        printf("Key must contain 26 characters.\n");
        return status;
    }

    return status;
}

bool check_upper(char letter)
{
    if (letter >= 'A' && letter <= 'Z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool check_lower(char letter)
{
    if (letter >= 'a' && letter <= 'z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check if the letter is uppercase
// If not, change it into uppercase
void keep_uppercase(char *letter)
{
    if (*letter > 'Z')
    {
        *letter -= 32;
    }
}

// Check if the letter is lowercase
// If not, change it into a lowercase
void keep_lowercase(char *letter)
{
    if (*letter < 'a')
    {
        *letter += 32;
    }
}
