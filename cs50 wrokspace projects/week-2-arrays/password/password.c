// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>

bool valid(string password);
int get_length(char password[]);
int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

//define a function that is equal to strlen in library in <string.h>
int get_length(char password[])
{
    int length = 0;
    while (password[length] != '\0')
    {
        length++;
    }

    return length;
}

// TODO: Complete the Boolean function below
//Use 4 flag to detect if the password is contain the lowwer case letter, upper case letter, number, symbol at the same time
//If the password meet the rule, return true
//else return false
bool valid(string password)
{
    bool lowercase, uppercase, number, symbol = false;
    int length = get_length(password);
    for (int i = 0; i < length; i++)
    {
        if (password[i] >= ' ' && password[i] <= '/')
        {
            symbol = true;
        }
        else if (password[i] >= ':' && password[i] <= '@')
        {
            symbol = true;
        }
        else if (password[i] >= '[' && password[i] <= '`')
        {
            symbol = true;
        }
        else if (password[i] >= '{' && password[i] <= '~')
        {
            symbol = true;
        }

        if (password[i] >= '1' && password[i] <= '9')
        {
            number = true;
        }

        if (password[i] >= 'a' && password[i] <= 'z')
        {
            lowercase = true;
        }

        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            uppercase = true;
        }
    }
    if (lowercase && uppercase && number && symbol)
    {
        return true;
    }
    else
    {
        return false;
    }

}
