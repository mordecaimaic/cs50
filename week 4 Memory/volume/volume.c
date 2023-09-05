// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

void print_array(uint8_t array[], int length);
int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t head_info[HEADER_SIZE];
    int16_t buffer;
    fread(head_info, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(head_info, sizeof(uint8_t), HEADER_SIZE, output);
    
    print_array(head_info, HEADER_SIZE);
    // TODO: Read samples from input file and write updated data to output file
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer = factor * buffer;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}

void print_array(uint8_t array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("i = %i, bit = 0x%x\n\n", i, array[i]);
    }
}
