#include <cs50.h>
#include <stdio.h>

#define DIGITS_11 10000000000
#define DIGITS_12 100000000000
#define DIGITS_13 1000000000000
#define DIGITS_14 10000000000000
#define DIGITS_15 100000000000000
#define DIGITS_16 1000000000000000

#define AMEX 1
#define VISA 1
#define MASTER 1
#define LUHN_VERIFIED 1
#define LENGTH_13 13
#define LENGTH_15 15
#define LENGTH_16 16


int check_length_valid(long int numbers);
int get_digits(long int numbers);
int check_luhn(long int numbers);
int check_visa_begin(long int numbers, int length);
int check_Amex_begin(long int numbers, int length);
int check_Master_begin(long int numbers, int length);

int main(void)
{
    //get the card number
    long int card_numbers;
    int length;
    int verified_flag = false;
    card_numbers = get_long("Numbers: ");

    //check if the length of the credit card number is right, if right get back the digits numbers
    length = check_length_valid(card_numbers);
    //chck if the card numbers is correct under the Luhn's algorithm
    //if the card numbers are ed to the principle of VISA card, the output "VISA"
    // if (length)
    // {
    //     verified_flag = check_luhn(card_numbers);
    // }
    //switch the length of the number, to figure out that if the number is valid
    //sort out the cardnumbers
    //deal with it in different situation of the length
    switch (length)
    {
        case (LENGTH_13):
            verified_flag = check_visa_begin(card_numbers, LENGTH_13);
            verified_flag = verified_flag * check_luhn(card_numbers);
            if (verified_flag)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
            break;

        case (15):
            verified_flag = check_Amex_begin(card_numbers, LENGTH_15);
            verified_flag = verified_flag * check_luhn(card_numbers);
            if (verified_flag)
            {
                printf("AMEX\n");
                break;
            }
            else
            {
                printf("INVALID\n");
                break;
            }


        case (16):
            verified_flag = check_visa_begin(card_numbers, LENGTH_16);
            verified_flag = verified_flag * check_luhn(card_numbers);
            if (verified_flag)
            {
                printf("VISA\n");
                break;
            }
            else
            {
                verified_flag = check_Master_begin(card_numbers, LENGTH_16);
                verified_flag = verified_flag * check_luhn(card_numbers);
                if (verified_flag)
                {
                    printf("MASTERCARD\n");
                    break;
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            }
    }

}


//check the credit card length
//if the lenght of the number is not the length that we want,out put INVALID
int check_length_valid(long int numbers)
{
    if (numbers / DIGITS_13 > 0 && numbers / DIGITS_13 < 10)
    {
        return 13;
    }

    else if (numbers / DIGITS_15 > 0 && numbers / DIGITS_15 < 10)
    {
        return 15;
    }

    else if (numbers / DIGITS_16 > 0 && numbers / DIGITS_16 < 10)
    {
        return 16;
    }

    else
    {
        printf("INVALID\n");
        return 0;
    }

}

//check if the first digit of the visa number is 4
//if the first number is not 4, then return ERROR
int check_visa_begin(long int numbers, int length)
{
    switch (length)
    {
        case (LENGTH_13):
        {
            if (numbers / DIGITS_13 == 4)
            {
                return VISA;
            }
            else
            {
                return 0;
            }
        }

        case (LENGTH_16):
        {
            if (numbers / DIGITS_16 == 4)
            {
                return VISA;
            }
            else
            {
                return 0;
            }
        }
    }

    return 0;
}


//check if the first two number of American Express is 34 or 37
//if the first two number is not 34 or 34, then return ERROR
int check_Amex_begin(long int numbers, int length)
{
    if (numbers / DIGITS_14 == 34 || numbers / DIGITS_14 == 37)
    {
        return AMEX;
    }
    else
    {
        return 0;
    }
}

//check if the first tow number of Master card is 51 or 52 or 53 or 54 or 55
//if the first two number is not 51 or 52 or 53 or 54 or 55, then return ERROR
int check_Master_begin(long int numbers, int length)
{
    if (numbers / DIGITS_15 == 51 || numbers / DIGITS_15 == 52 || numbers / DIGITS_15 == 53 || numbers / DIGITS_15 == 54
        || numbers / DIGITS_15 == 55)
    {
        return MASTER;
    }
    else
    {
        return 0;
    }
}


//check if the number meet to the rule of luhn algotithm
int check_luhn(long int numbers)
{
    int digits = 0, position = 0, sum = 0;

    //divide every digit of the number, and put it into the luhn principle
    while (numbers > 0)
    {
        digits = numbers % 10;
        numbers = numbers / 10;
        if (position % 2 == 0)
        {
            sum += digits;
        }

        if (position % 2 != 0)
        {
            if (digits < 5)
            {
                sum += digits * 2;
            }
            else
            {
                sum += digits * 2 % 10 + digits * 2 / 10;
            }
        }

        position ++;
    }

    if (sum % 10 == 0)
    {
        // printf("sum = %i\n", sum);
        return LUHN_VERIFIED;
    }
    else
    {
        // printf("luhn error\n");
        return 0;
    }

}