#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main (void)
{
    string a = get_string("alpha check: ");
    for (int i = 1, length = strlen(a); i <length; i++)
    {
        if(a[i] < a[i-1])
        {
            printf("%i %i\n", a[i], a[i-1]);
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    return 0;
}