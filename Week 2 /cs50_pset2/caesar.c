#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Check if there is only 2 argument in the command line
    // If not, promt the user about the usage
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check if there is all number in the second argument
    // If not, promt the user about the usage
    int key_length = strlen(argv[1]);
     for (int i = 0; i < key_length; i++)
    {
        if (isdigit(argv[1][i]) == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Function atoi: convert the string numbers into int numbers
    int key = atoi(argv[1]);
    string message = get_string("Plaintext: ");
    int mes_length = strlen(message);

    for (int i = 0; i < mes_length; i++)
    {
        if (isupper(message[i]))
        {

            message[i] = (message[i] - 65 + key) % 26 + 'A';

        }

        if (islower(message[i]))
        {

            message[i] = (message[i] - 97 + key) % 26 + 'a';

        }
        //printf("%c", message[i]);
    }

    printf("ciphertext: %s\n", message);
}
