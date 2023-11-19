#include <stdio.h>
#include <stdlib.h>
int main()
{
    char name[6] = "mike";
    FILE *ptr_1 = fopen("new_file.txt", "r");
    FILE *ptr_2 = fopen("new_file.txt", "a");
    fwrite(name, sizeof(char), 4, ptr_2);
    fprintf(ptr_2, "%s","hello world\n");
    char *ch = malloc(80 * sizeof(char));
    fread(ch, sizeof(char), 10, ptr_1);
    fclose(ptr_1);
    printf("%s", ch);
    return 0;
}