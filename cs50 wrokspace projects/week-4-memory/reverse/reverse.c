#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"
#define header_size 44
#define bits_per_byte 8
typedef uint8_t BYTE;
int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage :/reverse input.wav output.wav\n");
        return 1;
    }
    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Error open file %s\n", argv[1]);
        return 1;
    }

    // Read header
    WAVHEADER header_info;
    fread(&header_info, sizeof(WAVHEADER), 1, input);
    // Use check_format to ensure WAV format
    if (check_format(header_info))
    {
        printf("%s is not a wav file.\n", argv[1]);
        return 1;
    }
    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Error write %s", argv[2]);
        return 1;
    }
    // Write header to file
    fwrite(&header_info, sizeof(WAVHEADER), 1, output);
    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header_info);
    // Write reversed audio to file
    fseek(input, -block_size, SEEK_END);
    BYTE *sample_block = (BYTE *) malloc(block_size);
    while (ftell(input) >= 44)
    {
        fread(sample_block, block_size, 1, input);
        fwrite(sample_block, block_size, 1, output);
        fseek(input, -(2 * block_size), SEEK_CUR);
    }
    fclose(input);
    fclose(output);
    free(sample_block);
    return 0;
}

int check_format(WAVHEADER header)
{
    if (header.format[0] != 0x57 || header.format[1] != 0x41 || header.format[2] != 0x56 || header.format[3] != 0x45)
    {
        return 1;
    }

    return 0;
}

int get_block_size(WAVHEADER header)
{
    int block_size = header.numChannels * (header.bitsPerSample / bits_per_byte);
    return block_size;
}