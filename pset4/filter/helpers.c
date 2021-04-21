#include "helpers.h"
#include <stdio.h>
#include <math.h>


// Convert image to grayscale
//RGBTRIPLE is a data type defined in another file. Here is means image[i][j] is data type RGBPTRIPLE
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Loop through the rows using nested loop for Height + Width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Get RGBTriple Values
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;

            //Calculate the average value
            int average = round((red + blue + green) / 3);

            //To make grayscale, all values must be same as average calculated
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;

            //convert to Sepia value
            int sepiaRed = round(0.393 * red + 0.769 * green + 0.189 * blue);
            int sepiaGreen = round(0.349 * red + 0.686 * green + 0.168 * blue);
            int sepiaBlue = round(0.272 * red + 0.534 * green + 0.131 * blue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Loop through height/width with nested loops
    //We will only loop through halfway point of width. Otherwise, half of pixels will be lost. When we reach the 2nd half, the first half is already reflected !
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            //Reflect the picture
            //Set a temporary variable temp
            RGBTRIPLE temp = image[i][j];

            //Set current pixel to the reflected pixel
            image[i][j] = image[i][width - (j + 1)];

            //The reflected pixel can now take the value of temp
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
// Set RGB values to the average of the surrounding 9 pixels
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temporary placeholder
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    // Loop through width/height

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Initialise values
            float sum_red = 0;
            float sum_blue = 0;
            float sum_green = 0;
            int counter = 0;


            //Check if surrounding pixels exist. We loop pixel up/down left/right by 1. If the moved pixel is outside the range of 0 to height/width, pixel doesn't exist and can be skipped.
            //k ranges from -1 to 1, as we check both sides
            // Continue skips the current interation of the loop and continue with next iteration. It doesn't break the program
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }

                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    //if
                    else
                    {
                        sum_red = sum_red + temp[i + k][j + l].rgbtRed;
                        sum_blue = sum_blue + temp[i + k][j + l].rgbtBlue;
                        sum_green = sum_green + temp[i + k][j + l].rgbtGreen;
                        counter++;
                        //counter is the number of pixels that is detected
                    }
                }
            }

            //Average
            image[i][j].rgbtRed = round(sum_red / counter);
            image[i][j].rgbtBlue = round(sum_blue / counter);
            image[i][j].rgbtGreen = round(sum_green / counter);
        }
    }

    return;
}
