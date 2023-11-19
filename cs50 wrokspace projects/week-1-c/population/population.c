#include <cs50.h>
#include <stdio.h>

int calculate_year(int start, int end);
int main(void)
{
    int start_size, end_size, years;
    // TODO: Prompt for start size
    do
    {
        start_size = get_int("Start size:");
    }
    while (start_size < 9);


    // TODO: Prompt for end size
    do
    {
        end_size = get_int("End size:");
    }
    while (start_size > end_size);


    // TODO: Calculate number of years until we reach threshold
    years = calculate_year(start_size, end_size);

    // TODO: Print number of years
    printf("Years: %i\n", years);
}

int calculate_year(int start, int end)
{
    int years = 0;
    while (start < end)
    {
        start = start + start / 3 - start / 4;
        //printf("start =%i\n",start);
        years++;
    }
    return years;

}



