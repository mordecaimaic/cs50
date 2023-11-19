#include <stdio.h>
#include <string.h>
#include <cs50.h>

typedef struct
{
    string name;
    int votes;
} candidate;
//canditate;
candidate get_candidate(string prompt);

int main(void)
{
    int num = get_int("Input the number of candidates: ");
    candidate president[num];
    for (int i = 0; i < num; i++)
    {
        president[i] = get_candidate("Input candidate here: ");
    }

     for (int i = 0; i < num; i++)
    {
         printf("Your name is %s, your votes is %i.\n", president[i].name, president[i].votes);
    }

}

candidate get_candidate(string prompt)
{
    candidate c;
    printf("%s\n", prompt);
    c.name = get_string("Input name: ");
    c.votes = get_int("Input votes:");
    return c;
}