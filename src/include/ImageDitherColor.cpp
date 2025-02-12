/*
ImageDitherColor.cpp
Inkplate Arduino library
David Zovko, Borna Biro, Denis Vajak, Zvonimir Haramustek @ e-radionica.com
February 12, 2021
https://github.com/e-radionicacom/Inkplate-Arduino-library

For support, please reach over forums: forum.e-radionica.com/en
For more info about the product, please check: www.inkplate.io

This code is released under the GNU Lesser General Public License v3.0: https://www.gnu.org/licenses/lgpl-3.0.en.html
Please review the LICENSE file included with this example.
If you have any questions about licensing, please contact techsupport@e-radionica.com
Distributed as-is; no warranty is given.
*/

#include "Image.h"

#ifdef ARDUINO_INKPLATECOLOR

extern Image *_imagePtrJpeg;

static uint32_t pallete[] = {
    0x000000ll, 0xFFFFFFll, 0x008000ll, 0x0000FFll, 0xFF0000ll, 0xFFFF00ll, 0xFFAA00ll,
};

static unsigned int width = E_INK_WIDTH, height = E_INK_HEIGHT;

uint8_t Image::findClosestPalette(uint32_t c)
{
    int mi = 0;
    for (int i = 1; i < sizeof pallete / sizeof pallete[0]; ++i)
    {
        if (COLORDISTSQR(c, pallete[i]) < COLORDISTSQR(c, pallete[mi]))
            mi = i;
    }
    return mi;
}

uint8_t Image::ditherGetPixelBmp(uint32_t px, int i, int j, int w, bool paletted)
{
    if (paletted)
        px = ditherPalette[px];

    int16_t r = RED8(px) + ditherBuffer[0][j % kernelHeight][i];
    int16_t g = GREEN8(px) + ditherBuffer[1][j % kernelHeight][i];
    int16_t b = BLUE8(px) + ditherBuffer[2][j % kernelHeight][i];

    ditherBuffer[0][j % kernelHeight][i] = 0;
    ditherBuffer[1][j % kernelHeight][i] = 0;
    ditherBuffer[2][j % kernelHeight][i] = 0;

    r = max((int16_t)0, min((int16_t)255, r));
    g = max((int16_t)0, min((int16_t)255, g));
    b = max((int16_t)0, min((int16_t)255, b));

    int closest = findClosestPalette(((uint32_t)r << 16) | ((uint32_t)g << 8) | ((uint32_t)b));

    int32_t rErr = r - (int32_t)((pallete[closest] >> 16) & 0xFF);
    int32_t gErr = g - (int32_t)((pallete[closest] >> 8) & 0xFF);
    int32_t bErr = b - (int32_t)((pallete[closest] >> 0) & 0xFF);

    for (int k = 0; k < kernelHeight; ++k)
    {
        for (int l = -kernelX; l < kernelWidth - kernelX; ++l)
        {
            if (!(0 <= i + l && i + l < w))
                continue;
            ditherBuffer[0][(j + k) % kernelHeight][i + l] += (kernel[k][l] * rErr) / coef;
            ditherBuffer[1][(j + k) % kernelHeight][i + l] += (kernel[k][l] * gErr) / coef;
            ditherBuffer[2][(j + k) % kernelHeight][i + l] += (kernel[k][l] * bErr) / coef;
        }
    }

    return closest;
}

uint8_t Image::ditherGetPixelJpeg(uint8_t px, int i, int j, int x, int y, int w, int h)
{
    // Not used
    return 0;
}

void Image::ditherSwap(int)
{
    // Not used
}

void Image::ditherSwapBlockJpeg(int x)
{
    // Not used
}


#endif