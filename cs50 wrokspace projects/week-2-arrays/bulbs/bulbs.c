#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
int convert_binary(int num, int binary[BITS_IN_BYTE]);
int pow_int(int base, int index);


int main(void)
{
    // Prompt the use to input a message
    string message = get_string("Message: ");
    int binary[BITS_IN_BYTE] = {0};
    int length = strlen(message);

    for (int i = 0; i < length; i++)
    {
        convert_binary(message[i], binary);
        // As the binary array is reversed
        // We need to print the bulbs from back to front
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            print_bulb(binary[j]);
            binary[j] = 0;
        }
        printf("\n");
    }
}




void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}


// A function that convert a character into 8 bit binary numbers and store in the array called "binary"
// For example, 'H' is equal to integer 72, and 72 = 64 + 8 = 2^6 + 2^3 = 0 1 0 0 1 0 0 0
// And then the binary array will be referenced back to = {0,0,0,1,0,0,1,0} (The order of the number is reversed, the original binary numbers of 72 is" 0 1 0 0 1 0 0 0")
// So we need to print the bulbs from back to front

int convert_binary(int num, int binary[BITS_IN_BYTE])
{
    // int binary[BITS_IN_BYTE] = {0};
    int bit = 0;
    int count = 0;
    while (num)
    {
        bit = num % 2;
        binary[count] = bit;
        num = num / 2;
        count++;
        //printf("current bit = %i\n", bit);
    }
    return bit;
}

// A pow function that return base^index, for example: pow_int(2,5) will return 32
// This function can only take the positive integers as input
int pow_int(int base, int index)
{
    int result = 1;
    for (int i = 1; i <= index; i++)
    {
        result *= base;
    }
    return result;
}