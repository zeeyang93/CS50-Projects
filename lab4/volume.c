// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

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

    //uint8_t is a type that stores 8-bit integer. Defines variable "header" type now
    uint8_t header[HEADER_SIZE];

    //read the file from "input" into "header". HEADER_SIZE is the total size of elements to be read, and 1 is number of times to read
    fread(header, HEADER_SIZE, 1, input);

    //write from header to output
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file

    //defines variable type "buffer". This variable is a temporary variable to hold the address of pointer
    int16_t buffer;

    //read 2 bytes each time, ie. size of int16_t
    //we are interested in the address of "buffer", not the value of buffer. Hence the symbol &
    //while you read, you write. Hence the use of while loop
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
