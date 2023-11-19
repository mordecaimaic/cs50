#include "helpers.h"
#include <math.h>
// Convert image to grayscale
typedef struct
{
    int Gx;
    int Gy;
    int G;
} pixel;

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            pixel = image[i][width - j - 1];
            image[i][width - j - 1] = image[i][j];
            image[i][j] = pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE slide_window[3][3];
    RGBTRIPLE copy[height][width];
    RGBTRIPLE blur_pixel;
    int blur_pixel_red, blur_pixel_green, blur_pixel_blue;
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
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    slide_window[k][l].rgbtRed = 0;
                    slide_window[k][l].rgbtGreen = 0;
                    slide_window[k][l].rgbtBlue = 0;
                }
            }
            blur_pixel.rgbtRed = 0;
            blur_pixel.rgbtGreen = 0;
            blur_pixel.rgbtBlue = 0;
            // blur_pixel_red is an "int" type data, make sure not to use blur_pixel>regbRed to calcuate the sum
            // because it is an 16 bit type, it will overflow as a sum
            blur_pixel_red = 0;
            blur_pixel_green = 0;
            blur_pixel_blue = 0;

            count = 1;
            slide_window[1][1] = copy[i][j];
            if (i > 0)
            { // Up pixel
                slide_window[0][1] = copy[i - 1][j];
                count++;
            }
            if (i < height - 1)
            { // Bottom pixel
                slide_window[2][1] = copy[i + 1][j];
                count++;
            }
            if (j > 0)
            { // Left pixel
                slide_window[1][0] = copy[i][j - 1];
                count++;
            }
            if (j < width - 1)
            { // Right pixel
                slide_window[1][2] = copy[i][j + 1];
                count++;
            }
            if (i > 0 && j > 0)
            { // Top left pixel
                slide_window[0][0] = copy[i - 1][j - 1];
                count++;
            }
            if (i > 0 && j < width - 1)
            { // Top right pixel
                slide_window[0][2] = copy[i - 1][j + 1];
                count++;
            }
            if (i < height - 1 && j > 0)
            { // Bottom left pixel
                slide_window[2][0] = copy[i + 1][j - 1];
                count++;
            }
            if (i < height - 1 && j < width - 1)
            { // Bottom right pixel
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
            image[i][j] = blur_pixel;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //  Sobel operator
    int Gx_Kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy_Kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE copy[height][width];
    RGBTRIPLE slide_window[3][3];
    RGBTRIPLE temp_pixel;
    pixel red, green, blue;
    int Gx = 0, Gy = 0;
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
            // Initialize the slide window, set every element as 0
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    slide_window[k][l].rgbtRed = 0;
                    slide_window[k][l].rgbtGreen = 0;
                    slide_window[k][l].rgbtBlue = 0;
                }
            }
            // Initialize the virables, set them as 0 respectively
            red.Gx = 0;
            red.Gy = 0;
            green.Gx = 0;
            green.Gy = 0;
            blue.Gx = 0;
            blue.Gy = 0;
            temp_pixel.rgbtRed = 0;
            temp_pixel.rgbtGreen = 0;
            temp_pixel.rgbtBlue = 0;

            slide_window[1][1] = copy[i][j];
            if (i > 0)
            { // Up pixel
                slide_window[0][1] = copy[i - 1][j];
            }
            if (i < height - 1)
            { // Bottom pixel
                slide_window[2][1] = copy[i + 1][j];
            }
            if (j > 0)
            { // Left pixel
                slide_window[1][0] = copy[i][j - 1];
            }
            if (j < width - 1)
            { // Right pixel
                slide_window[1][2] = copy[i][j + 1];
            }
            if (i > 0 && j > 0)
            { // Top left pixel
                slide_window[0][0] = copy[i - 1][j - 1];
            }
            if (i > 0 && j < width - 1)
            { // Top right pixel
                slide_window[0][2] = copy[i - 1][j + 1];
            }
            if (i < height - 1 && j > 0)
            { // Bottom left pixel
                slide_window[2][0] = copy[i + 1][j - 1];
            }
            if (i < height - 1 && j < width - 1)
            { // Bottom right pixel
                slide_window[2][2] = copy[i + 1][j + 1];
            }

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    red.Gx += slide_window[k][l].rgbtRed * Gx_Kernel[k][l];
                    red.Gy += slide_window[k][l].rgbtRed * Gy_Kernel[k][l];
                    green.Gx += slide_window[k][l].rgbtGreen * Gx_Kernel[k][l];
                    green.Gy += slide_window[k][l].rgbtGreen * Gy_Kernel[k][l];
                    blue.Gx += slide_window[k][l].rgbtBlue * Gx_Kernel[k][l];
                    blue.Gy += slide_window[k][l].rgbtBlue * Gy_Kernel[k][l];
                }
            }
            red.G = round(sqrt(pow(red.Gx, 2) + pow(red.Gy, 2)));
            green.G = round(sqrt(pow(green.Gx, 2) + pow(green.Gy, 2)));
            blue.G = round(sqrt(pow(blue.Gx, 2) + pow(blue.Gy, 2)));
            if (red.G > 255)
            {
                red.G = 255;
            }
            if (green.G > 255)
            {
                green.G = 255;
            }
            if (blue.G > 255)
            {
                blue.G = 255;
            }
            temp_pixel.rgbtRed = red.G;
            temp_pixel.rgbtGreen = green.G;
            temp_pixel.rgbtBlue = blue.G;

            image[i][j] = temp_pixel;
        }
    }
    return;
}
