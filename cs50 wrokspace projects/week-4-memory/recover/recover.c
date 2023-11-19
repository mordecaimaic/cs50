#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define block_size 512
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage :.\recover IMAGE\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    FILE *output;
    BYTE *buffer = (BYTE *) malloc(sizeof(BYTE) * block_size);
    int count = -1;
    char output_name[10];
    while (fread(buffer, sizeof(BYTE), block_size, input) == block_size)
    { // Because the head file data will only in the first 4 bytes of each block(512 bytes)
      // So we just need the check the firtst 4 bytes of each block
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if (buffer[3] == 0xe0 || buffer[3] == 0xe1 || buffer[3] == 0xe2 || buffer[3] == 0xe3 || buffer[3] == 0xe4 ||
                buffer[3] == 0xe5 || buffer[3] == 0xe6 || buffer[3] == 0xe7 || buffer[3] == 0xe8 || buffer[3] == 0xe9 ||
                buffer[3] == 0xea || buffer[3] == 0xeb || buffer[3] == 0xec || buffer[3] == 0xed || buffer[3] == 0xee ||
                buffer[3] == 0xef)
            {
                if (count > -1)
                {
                    fclose(output);
                }
                sprintf(output_name, "%03i.jpg", ++count);
                output = fopen(output_name, "w");
                // Write the first block into the output file
                fwrite(buffer, sizeof(BYTE), block_size, output);
                // printf("%x %x %x %x", buffer[block_size -4], buffer[block_size - 3], buffer[block_size - 2], buffer[block_size -
                // 1]);
                continue;
            }
        }
        // int i = 0;
        // Check if there is bolck contain all 0, if yes, quit because no data remain in the rest
        // for (i = 0; i < block_size; i++)
        // {
        //     if (buffer[i] != 0)
        //     {
        //         break;
        //     }
        // }
        // if (i == block_size - 1)
        // {
        //     printf("end\n");
        //     break;
        // }

        if (count > -1)
        {
            // Keep writing the data into the output file(except the head data of the first block)
            fwrite(buffer, sizeof(BYTE), block_size, output);
        }
    }
    fclose(output);
    fclose(input);
    free(buffer);
    return 0;
}