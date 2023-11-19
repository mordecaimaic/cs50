#include <stdio.h>
#include <cs50.h>
#define ERROR 1
#define LENGTH 5

int binary_search(int number[], int target, int position, int length);
int bubble_sort(int number[], int length);
int binary_search_time = 0;
int main(void)
{
    int length = get_int("How many number that you want to input: ");
    int number[length];
    for (int i = 0; i < length; i++)
    {
        //printf("The %i number: ", i + 1);
        number[i] = get_int("Input no.%i number: ", i + 1);
    }
    bubble_sort(number, length);
    for (int i = 0; i < length; i++)
    {
        printf("%i\n", number[i]);
    }
    //int number[] = {1,7,8,9,10};
    int first_position = length / 2;
    int target = get_int("Input the number that you want to search: ");
    if (binary_search(number, target, first_position, length))
    {
        return 0;
    }
}


int binary_search(int number[], int target, int position, int length)
{
    int odd_even = length % 2;
    printf("current position is %i.\n", position);
    switch (odd_even)
    {
        case 0:
            if (target < number[position] && target > number[position - 1])
            {
                printf("Not found the number %i.\n", target);
                return ERROR;
            }
            if ((target != number[position] && target != number[position - 1] && position == 0)
                || (target != number[position] && target != number[position - 1] && position == length))
            {
                printf("Not found the number %i.\n", target);
                return ERROR;
            }

            if (number[position] == target)
            {
                printf("Found in the no.%i number.\n", position + 1);
                return 0;
            }
            else if (number[position - 1] == target)
            {
                printf("Found in the no.%i number.\n", position);
                return 0;
            }
            else if (target < number[position - 1])
            {
                if (position == 0 || position == length - 1)
                {
                    printf("Not found the number %i.\n", target);
                    return ERROR;
                }
                position /= 2;
                return binary_search(number, target, position, length);
            }
            else if (target > number[position])
            {
                if (position == 0 || position == length - 1)
                {
                    printf("Not found the number %i\n", target);
                    return ERROR;
                }
                position += position / 2;
                return binary_search(number, target, position, length);
            }
            break;

        case 1:

            if ((target != number[position] && target != number[position - 1] && position == 0)
                || (target != number[position] && target != number[position - 1] && position == length - 1))
            {
                printf("Not found the number %i.\n", target);
                return ERROR;
            }

            if (number[position] == target)
            {
                printf("Found in the no.%i number.\n", position + 1);
                return 0;
            }
            else if (target < number[position])
            {
                position /= 2;
                return binary_search(number, target, position, length);
            }
            else if (target > number[position])
            {
                position += position / 2;
                return binary_search(number, target, position, length);
            }
            break;

    }

    printf("programe should not be here.\n");
    return ERROR;
}

int bubble_sort(int number[], int length)
{
    int temp;
    bool swap = 0;
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - 1 - i; j++)
        {
            if (number[j] > number[j + 1])
            {
                swap = 1;
                temp = number[j + 1];
                number[j + 1] = number[j];
                number[j] = temp;
            }
        }
        // Use the virable swap to check if the array has been sorted already.
        // If if have been sorted, then we just need to get in 1 loop and then break.
        if (!swap)
        {
            printf("Bubble sort complete, alreay a sorted array.\n");
            return 0;
        }

    }
    printf("Bubble sort complete.\n");
    return 0;
}