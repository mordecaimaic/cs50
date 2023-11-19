// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>
void replace(char *argv);
int main(int argc, char *argv[])
{
    int length;
    switch(argc)
    {
        case 1:
        printf("Usage: ./no-vowels word\n");
        return 1;

        case 2:
        replace(argv[1]);
        printf("%s\n", argv[1]);
    }

}

void replace(char *argv)
{
    for (int i = 0, length = strlen(argv); i < length; i++)
    {
        switch (argv[i])
        {
            case 'a':
            argv[i] = '6';
            break;

            case 'e':
            argv[i] = '3';
            break;

            case 'i':
            argv[i] = '1';
            break;

            case 'o':
            argv[i] = '0';
            break;
        }
    }
}
