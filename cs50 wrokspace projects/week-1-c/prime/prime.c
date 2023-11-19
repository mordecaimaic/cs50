#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    //prompt the use to input the min number
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    //prompt the use to input the biggerst number
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}


//check if the number input is a prime,if it is a prime return true
//else return false
bool prime(int number)
{
    // TODO
    if (number == 1)
    {
        return 0;
    }
    for (int i = 2; i <= number / 2; i++)
    {
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}
