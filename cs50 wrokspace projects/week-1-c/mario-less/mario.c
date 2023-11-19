#include <cs50.h>
#include <stdio.h>
//this about is about walls of mario in cs50 Harvard
int main(void)
{
    int height;
    //get height of walls
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //print the walls
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }

        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }


        printf("\n");
    }


}