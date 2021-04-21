#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    else
    {
        //Open card.raw
        //Take the input file and assign it to pointer.
        //Here, input_file is a pointer pointing to argv[1], which is the file name.
        char *input_file = argv[1];
        FILE *input_pointer = fopen(input_file, "r");

        if (input_file == NULL)
        {
            printf("Unable to open: %s\n", input_file);
            return 2;
        }

        //Initialise variables

        //Create a buffer array of 512 bytes
        BYTE buffer[512];

        //Count keeps track of number of images recovered
        int count = 0;

        //img_pointer is the file that will be written to
        FILE *output_pointer = NULL;

        //img_name will store the name of JPEGs generated
        char img_name[8];

        //Loop starts. While there are blocks to read
        while (fread(&buffer, 512, 1, input_pointer) == 1)
        {
            //If start of new JPEG (0xff, 0xd8, 0xff, 0xe*)
            //Buffer[3] uses bitwise AND. 0xf0 is 11110000, since we are only interested in the first half. We want the result to be 11100000, ie. 0xe0
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                //If found a new JPEG, close previous file. Only time this is not relevant is first file.
                if (count != 0)
                {
                    fclose(output_pointer);
                }

                //From here onwards occurs when first JPEG is found
                //Initialise files

                //%03i means 0 must be placed in front, 3 numbers to be printed, and expecting data type integer
                //sprintf here means write string to array img_name
                sprintf(img_name, "%03i.jpg", count);

                //"w" means create empty file for writing.
                output_pointer = fopen(img_name, "w");
                count++;
            }

            //If JPEG has been found, write to file from buffer
            if (count != 0)
            {
                fwrite(&buffer, 512, 1, output_pointer);
            }

        }

        fclose(input_pointer);
        fclose(output_pointer);

        return 0;

    }
}