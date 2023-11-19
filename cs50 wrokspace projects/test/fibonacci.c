#include <stdio.h>

// partice how to use the recursion to make a "fibonacci"
int fibonacci(int n);
int main()
{
    printf("%i\n", fibonacci(3));
}

int fibonacci(int n)
{   printf("%i  ", n);
    if (n == 0)
    {
        return 0;
    }
    else if(n == 1)
    {
        return 1;
    }

    return fibonacci(n - 2) + fibonacci(n - 1);
}