#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = temp;
            image[i][j].rgbtGreen = temp;
            image[i][j].rgbtBlue = temp;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //      sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    //      sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    //      sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);

            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    int odds = width % 2;
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][width - j - 1];
            image[i][width - j - 1] = image[i][j];
            image[i][j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    RGBTRIPLE slide_window[3][3];
    RGBTRIPLE blur_pixel;
    int blur_pixel_red;
    int blur_pixel_green;
    int blur_pixel_blue;

    int count = 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize the slide window set as 0 as default
            blur_pixel.rgbtRed = 0;
            blur_pixel.rgbtGreen = 0;
            blur_pixel.rgbtBlue = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    slide_window[k][l].rgbtRed = 0;
                    slide_window[k][l].rgbtGreen = 0;
                    slide_window[k][l].rgbtBlue = 0;
                }
            }
            count = 1;
            blur_pixel_red = 0;
            blur_pixel_green = 0;
            blur_pixel_blue = 0;

            // Iterate every singal pixel from nested
            slide_window[1][1] = copy[i][j];
            if (i > 0)
            { // check if there is pixel at the "top" of the current pixel
                slide_window[0][1] = copy[i - 1][j];
                count++;
            }
            if (i < height - 1)
            { // check if there is pixel at the "bottom" of the current pixel
                slide_window[2][1] = copy[i + 1][j];
                count++;
            }
            if (j > 0)
            { // check if there is pixel in the "left" of the current pixel
                slide_window[1][0] = copy[i][j - 1];
                count++;
            }
            if (j < width - 1)
            { // check if there is pixel in the "right" of the current pixel
                slide_window[1][2] = copy[i][j + 1];
                count++;
            }
            if (i > 0 && j > 0)
            { // check if there is pixel in the "top left" of the current pixel
                slide_window[0][0] = copy[i - 1][j - 1];
                count++;
            }
            if (i > 0 && j < width - 1)
            { // check if there is pixel in the "top right" of the current pixel
                slide_window[0][2] = copy[i - 1][j + 1];
                count++;
            }
            if (i < height - 1 && j > 0)
            { // check if there is pixel in the "bottom left" of the current pixel
                slide_window[2][0] = copy[i + 1][j - 1];
                count++;
            }
            if (i < height - 1 && j < width - 1)
            { // check if there is pixel in the "bottom right" of the current pixel
                slide_window[2][2] = copy[i + 1][j + 1];
                count++;
            }
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    blur_pixel_red += slide_window[k][l].rgbtRed;
                    blur_pixel_green += slide_window[k][l].rgbtGreen;
                    blur_pixel_blue += slide_window[k][l].rgbtBlue;
                }
            }
            blur_pixel.rgbtRed = round(1.0 * blur_pixel_red / count);
            blur_pixel.rgbtGreen = round(1.0 * blur_pixel_green / count);
            blur_pixel.rgbtBlue = round(1.0 * blur_pixel_blue / count);
            if (blur_pixel.rgbtRed > 255)
            {
                blur_pixel.rgbtRed = 255;
            }
            if (blur_pixel.rgbtGreen > 255)
            {
                blur_pixel.rgbtGreen = 255;
            }
            if (blur_pixel.rgbtBlue > 255)
            {
                blur_pixel.rgbtBlue = 255;
            }
            image[i][j] = blur_pixel;
        }
    }

    return;
}
