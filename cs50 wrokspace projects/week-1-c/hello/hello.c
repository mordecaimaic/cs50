#include <stdio.h>
#include <cs50.h>
int main(void)
{
    //say hello to a user
    string name;
    //prompt the user to input his/her name
    name = get_string("What is your name? ");
    printf("Hello, %s!\n", name);
}