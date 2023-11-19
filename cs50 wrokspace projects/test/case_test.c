#include<stdio.h>

int getInt(char string[]);
int main(void)
{
    //a programe teach you how to use case
    int num;
    num  = getInt("Please int 1 or 2 or 3\n");
    printf("num +2 = %i", num +=2 );
    switch (num)
    {
        case (1):
            printf("you printf one\n");
            break;
        case (2):
            printf("you printf two\n");
        case (3):
            printf("you printf three\n");
    }

    //printf("int put ");
}

//A function that help you get a integer
int getInt(char string[])
{
    int intNum;
    printf("%s", string);
    scanf("%d", &intNum);
    return intNum;
}