/*
Image.cpp
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

#include "../libs/TJpeg/TJpg_Decoder.h"
#include "defines.h"
#include "pgmspace.h"

Image *_imagePtrJpeg = nullptr;
Image *_imagePtrPng = nullptr;

Image::Image(int16_t w, int16_t h) : Adafruit_GFX(w, h)
{
    _imagePtrJpeg = this;
    _imagePtrPng = this;
}

bool Image::drawImage(const String path, int x, int y, bool dither, bool invert)
{
    return drawImage(path.c_str(), x, y, dither, invert);
};

bool Image::drawImage(const char *path, int x, int y, bool dither, bool invert)
{
    if (strncmp(path, "http://", 7) == 0 || strncmp(path, "https://", 8) == 0)
    {
        if (strstr(path, ".bmp") != NULL || strstr(path, ".dib") != NULL)
            return drawBitmapFromWeb(path, x, y, dither, invert);
        if (strstr(path, ".jpg") != NULL || strstr(path, ".jpeg") != NULL)
            return drawJpegFromWeb(path, x, y, dither, invert);
        if (strstr(path, ".png") != NULL)
            return drawPngFromWeb(path, x, y, dither, invert);
    }
    else
    {
        if (strstr(path, ".bmp") != NULL || strstr(path, ".dib") != NULL)
            return drawBitmapFromSd(path, x, y, dither, invert);
        if (strstr(path, ".jpg") != NULL || strstr(path, ".jpeg") != NULL)
            return drawJpegFromSd(path, x, y, dither, invert);
        if (strstr(path, ".png") != NULL)
            return drawPngFromSd(path, x, y, dither, invert);
    }
    return 0;
};

bool Image::drawImage(const uint8_t *buf, int x, int y, int16_t w, int16_t h, uint8_t c, uint8_t bg)
{
#ifdef ARDUINO_INKPLATECOLOR
    // TODO: implement
    return 0;
#else
    if (getDisplayMode() == INKPLATE_1BIT && bg == 0xFF)
        drawBitmap(x, y, buf, w, h, c);
    else if (getDisplayMode() == INKPLATE_1BIT && bg != 0xFF)
        drawBitmap(x, y, buf, w, h, c, bg);
    else if (getDisplayMode() == INKPLATE_3BIT)
        drawBitmap3Bit(x, y, buf, w, h);
    return 1;
#endif
}

bool Image::drawImage(const String path, const Format &format, const int x, const int y, const bool dither,
                      const bool invert)
{
    return drawImage(path.c_str(), format, x, y, dither, invert);
};

bool Image::drawImage(const char *path, const Format &format, const int x, const int y, const bool dither,
                      const bool invert)
{
    if (strncmp(path, "http://", 7) == 0 || strncmp(path, "https://", 8) == 0)
    {
        if (format == BMP)
            return drawBitmapFromWeb(path, x, y, dither, invert);
        if (format == JPG)
            return drawJpegFromWeb(path, x, y, dither, invert);
        if (format == PNG)
            return drawPngFromWeb(path, x, y, dither, invert);
    }
    else
    {
        if (format == BMP)
            return drawBitmapFromSd(path, x, y, dither, invert);
        if (format == JPG)
            return drawJpegFromSd(path, x, y, dither, invert);
        if (format == PNG)
            return drawPngFromSd(path, x, y, dither, invert);
    }
    return 0;
}

bool Image::drawImage(const char *path, const Format &format, const Position &position, const bool dither,
                      const bool invert)
{
    if (strncmp(path, "http://", 7) == 0 || strncmp(path, "https://", 8) == 0)
    {
        if (format == JPG)
            return drawJpegFromWebAtPosition(path, position, dither, invert);
        else if (format == PNG)
            return drawPngFromWebAtPosition(path, position, dither, invert);
        else if (format == BMP)
            return drawBmpFromWebAtPosition(path, position, dither, invert);
        return false;
    }
    else
    {
        if (format == JPG)
            return drawJpegFromSdAtPosition(path, position, dither, invert);
        else if (format == PNG)
            return drawPngFromSdAtPosition(path, position, dither, invert);
        else if (format == BMP)
            return drawBmpFromSdAtPosition(path, position, dither, invert);
        return false;
    }
    return false;
}


void Image::drawBitmap3Bit(int16_t _x, int16_t _y, const unsigned char *_p, int16_t _w, int16_t _h)
{

#ifdef ARDUINO_INKPLATECOLOR
    // TODO: implement
#else

    if (getDisplayMode() != INKPLATE_3BIT)
        return;
    uint8_t _rem = _w & 1;
    int i, j;
    int xSize = (_w >> 1) + _rem;

    startWrite();
    for (i = 0; i < _h; i++)
    {
        for (j = 0; j < xSize - 1; j++)
        {
            writePixel((j * 2) + _x, i + _y, (*(_p + xSize * (i) + j) >> 4) >> 1);
            writePixel((j * 2) + 1 + _x, i + _y, (*(_p + xSize * (i) + j) & 0xff) >> 1);
        }
        writePixel((j * 2) + _x, i + _y, (*(_p + xSize * (i) + j) >> 4) >> 1);
        if (_rem == 0)
            writePixel((j * 2) + 1 + _x, i + _y, (*(_p + xSize * (i) + j) & 0xff) >> 1);
    }
    endWrite();
#endif
}
