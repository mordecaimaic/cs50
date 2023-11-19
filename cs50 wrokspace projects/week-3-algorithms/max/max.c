// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);
// This programe is to find the biggest number in an array that the user input
int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

int max(int array[], int n)
{
    int max_number = array[0];
    for (int i = 0; i < n; i++)
    {
        if (array[i] > max_number)
        {
            max_number = array[i];
        }
    }
    return max_number;
}
