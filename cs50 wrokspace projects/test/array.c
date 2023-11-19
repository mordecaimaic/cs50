#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Use recursive to copy a string array

void copy_string(char *s1, char *s2, int i);
int main (void)
{
    char *p = "Hi";
    char *t = malloc(strlen(p) + 1);
    copy_string(p, t, 0);
    t[0] = 'a';
    printf("%s\n", p);
    printf("%s\n", t);
    int a = 10;
}

void copy_string(char *s1, char*s2, int i)
{
    if (s1[i] == '\0')
    {
        s2[i] = s1[i];
        return;
    }

    s2[i] = s1[i];
    copy_string(s1, s2, ++i);
}