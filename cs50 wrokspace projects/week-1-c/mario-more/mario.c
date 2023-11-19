#include <cs50.h>
#include <stdio.h>

//a programe to print pyramid of mario in cs50
int main(void)
{
    int height;
    //input the height
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //start printing
    //useb 5 for loops
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

        printf("  ");

        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }

        /*for (int m = 0; m < height - i - 1; m++)
        {
            printf(" ");
        }*/
        printf("\n");
    }


}