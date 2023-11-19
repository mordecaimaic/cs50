#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert_recursive(string input, int length);
int main(void)
{
    string input = get_string("Enter a positive integer: ");
    int length = strlen(input);
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert_recursive(input, strlen(input)));
    printf("2 * %i = %i\n", convert_recursive(input, strlen(input)), 2 * convert_recursive(input, strlen(input)));
}

int convert_recursive(string input, int length)
{
    char character = input[length - 1];
    if (length == 1 || input[length - 2] > '9' || input[length - 2] < '0')
    {
        return character - '0';
    }
    else
    {
        return (character - '0') + 10 * convert_recursive(input, length - 1);
    }
}