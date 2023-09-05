#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Convert image to grayscale
typedef struct
{
    int Gx;
    int Gy;
    int G;
}pixel;
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int value;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            value = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtRed = value;
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
        for (int j = 0; j< width; j++)
        {
            sepiaRed = round(.593 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            
            sepiaGreen = round(.449 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .334 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            
            if(sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            
            if(sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if(sepiaBlue > 255)
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
    int temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][width - j].rgbtBlue;
            image[i][width - j].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = temp;
            
            temp = image[i][width - j].rgbtGreen;
            image[i][width - j].rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = temp;
            
            temp = image[i][width - j].rgbtRed;
            image[i][width - j].rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = temp;
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
            blur_pixel_red = 0;
            blur_pixel_blue = 0;
            blur_pixel_green = 0;
            
            
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
            
            // Iterate every singal pixel from nested
            slide_window[1][1] = copy[i][j];
            if (i > 0)
            {   //判断所在的像素点的正上方，是否有元素
                slide_window[0][1] = copy[i - 1][j];
                count++;
            }
            if (i < height - 1)
            {   //判断所在的像素点的正下方，是否有元素
                slide_window[2][1] = copy[i + 1][j];
                count++;
            }
            if (j > 0)
            {   //判断所在的像素点的正左方，是否有元素
                slide_window[1][0] = copy[i][j - 1];
                count++;
            }
            if (j < width - 1)
            {   ////判断所在的像素点的正右方，是否有元素
                slide_window[1][2] = copy[i][j + 1];
                count++;
            }
            if (i > 0 && j > 0)
            {   //判断所在的像素点的左上方，是否有元素
                slide_window[0][0] = copy[i - 1][j - 1];
                count++;
            }
            if (i > 0 && j < width - 1)
            {   //判断所在的像素点的右上方，是否有元素
                slide_window[0][2] = copy[i - 1][j + 1];
                count++;
            }
            if (i < height - 1 && j > 0)
            {   //判断所在的像素点的左下方，是否有元素
                slide_window[2][0] = copy[i + 1][j - 1];
                count++;
            }
            if (i < height - 1 && j < width - 1)
            {   //判断所在的像素点的右下方，是否有元素
                slide_window[2][2] = copy[i + 1][j + 1];
                count++;
            }
            
            
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    blur_pixel_red += slide_window[k][l].rgbtRed;
                    blur_pixel_blue += slide_window[k][l].rgbtGreen;
                    blur_pixel_green += slide_window[k][l].rgbtBlue;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
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
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    slide_window[k][l].rgbtRed = 0;
                    slide_window[k][l].rgbtGreen = 0;
                    slide_window[k][l].rgbtBlue = 0;
                }
            }
                ///////////////////
                red.Gx = 0;
                red.Gy = 0;
                green.Gx = 0;
                green.Gy = 0;
                blue.Gx = 0;
                blue.Gy = 0;
                temp_pixel.rgbtRed = 0;
                temp_pixel.rgbtGreen = 0;
                temp_pixel.rgbtBlue = 0;
                ///////////////////

                slide_window[1][1] = copy[i][j];
                if (i > 0)
                {   // Up pixel
                    slide_window[0][1] = copy[i - 1][j];
                }
                if (i < height - 1)
                {   // Bottom pixel
                    slide_window[2][1] = copy[i + 1][j];
                }
                if (j > 0)
                {   // Left pixel
                    slide_window[1][0] = copy[i][j - 1];
                }
                if (j < width - 1)
                {   // Right pixel
                    slide_window[1][2] = copy[i][j + 1];
                }
                if (i > 0 && j > 0)
                {   // Top left pixel
                    slide_window[0][0] = copy[i - 1][j - 1];
                }
                if (i > 0 && j < width - 1)
                {   // Top right pixel
                    slide_window[0][2] = copy[i - 1][j + 1];
                }
                if (i < height - 1 && j > 0)
                {   // Bottom left pixel
                    slide_window[2][0] = copy[i + 1][j - 1];
                }
                if (i < height - 1 && j < width -1)
                {   // Bottom right pixel
                    slide_window[2][2] = copy[i + 1][j + 1];
                }

                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        red.Gx += slide_window[k][l].rgbtRed * Gx_Kernel[k][l];
                        red.Gy += slide_window[k][l].rgbtRed * Gy_Kernel[k][l];
                        green.Gx += slide_window[k][l].rgbtGreen* Gx_Kernel[k][l];
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
