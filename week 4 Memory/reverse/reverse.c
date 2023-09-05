#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

#define header_size 44
int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc !=3)
    {
        printf("Usage :/reverse input.wav output.wav\n");
        return 1;
    }
    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Error open file %s.\n", argv[1]);
        return 1;
    }
    // Read header
    // TODO #3
    WAVHEADER header_info;
    fread(&header_info, sizeof(WAVHEADER), 1, input);
    int byte_count = 0;
    for (int i = 0; i < 4; i++)
    {
        printf("chunk ID[%i] = 0x%x\n", byte_count++, header_info.chunkID[i]);
    }
    printf("%i chunksize = %4x\n",  byte_count++, header_info.chunkSize);

    for (int i = 0; i < 4; i++)
    {
        printf("formant[%i] = 0x%x\n", i, header_info.format[i]);
    }

    
    // Use check_format to ensure WAV format
    // TODO #4
    if (header_info.format[0] != 0x57 || header_info.format[1] != 0x41 || header_info.format[2] != 0x56 || header_info.format[3] != 0x45)
    {
        printf("%s is not a wav file.\n", argv[1]);
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Error writing file %s.\n", argv[2]);
    }
    // Write header to file
    // TODO #6
    fwrite(&header_info, sizeof(WAVHEADER), 1, output);
    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = header_info.numChannels * (header_info.bitsPerSample / 8);
    // Write reversed audio to file
    // TODO #8
    BYTE *sample_block = (BYTE *) malloc(block_size);
    int block_count = 0;
    fseek(input, -block_size, SEEK_END);
    while (ftell(input) > 44)
    {
        fread(sample_block, block_size, 1, input);
        fwrite(sample_block, block_size, 1, output);
        fseek(input, -block_size * 2, SEEK_CUR);
    }
    
    fclose(input);
    fclose(output);
    free(sample_block);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return 0;
}
