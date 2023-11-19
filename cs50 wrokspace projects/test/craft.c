#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 100
int factorial(int n);

typedef char* string;
void modify_string (const string str);
int main()
{
    string a = (string)malloc(10);
    strcpy(a, "hello");
    modify_string(a);
}

int factorial(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
       return factorial(n - 1) * n;
    }
}

void modify_string (const string str)
{
    str[0] = 'a';
    printf("%s\n", str);
}