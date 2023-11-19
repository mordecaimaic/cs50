#include <stdio.h>
#include <cs50.h>
// char* get_text(char message[]);
int get_length(char text[]);
int get_letters(char text[]);
int get_words(char text[]);
int get_sentences(char text[]);


//Formula: index = 0.0588 * L - 0.296 * S - 15.8
//where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.


int main(void)
{
    int letters, words, sentences, grade;
    int Tenths = 0;
    float L, S, index;
    string text = get_string("Text: ");
    letters = get_letters(text);
    //printf("letter: %i\n", letters);

    words = get_words(text);
    //printf("words: %i\n", words);

    sentences = get_sentences(text);
    //printf("sentences: %i\n", sentences);

    L = 100 * (float)letters / words;
    S = 100 * (float)sentences / words;
    index = 0.0588 * L - 0.296 * S - 15.8;
    //printf("L = %f, S = % f index = %f\n", L, S, index);

    //round off the grade
    Tenths = (int)(index * 10) % 10;
    if (Tenths < 5)
    {
        grade = (int)index;
    }
    else
    {
        grade = (int)index + 1;
    }


    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}


// char* get_text(char message[])
// {
//     char text[200];
//     char *p = text;
//     printf("%s",message);
//     scanf("%s", text);
//     //printf("%s\n",text);
//     return "abc";
// }



int get_length(char text[])
{
    int length = 0;
    while (text[length] != '\0')
    {
        length++;
    }
    return length;
}

int get_letters(char text[])
{
    int letters = 0;
    int length = get_length(text);
    for (int i = 0; i < length;  i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }
    }
    return letters;
}

int get_words(char text[])
{
    int words = 1;
    int length = get_length(text);

    for (int i = 0; i < length; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    return words;
}

int get_sentences(char text[])
{
    int sentences = 0;
    int length = get_length(text);
    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }

    return sentences;
}