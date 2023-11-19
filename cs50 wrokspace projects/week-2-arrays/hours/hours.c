#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks;
    //ask the use to input the numbers of weeks that they already taken the CS50 courses
    do
    {
        weeks = get_int("Number of weeks taking CS50: ");
    }
    while (weeks < 1);
    int hours[weeks];
    //use a for loop to input the hours that they the courses in each week
    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }
    //If the user print 'T', output the total number of hours
    //If the user print 'A', output the average number of hours
    //case-insensitive
    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// to calcuate the number that use want to get
float calc_hours(int hours[], int weeks, char output)
{
    int total_hours = 0;
    float average_hours = 0;
    for (int i = 0; i < weeks ; i++)
    {
        total_hours += hours[i];
    }
    average_hours = (float)total_hours / weeks;
    if (output == 'T')
    {
        return total_hours;
    }
    else
    {
        return average_hours;
    }
}