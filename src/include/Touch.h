/*
Touch.cpp
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

#ifndef __TOUCH_H__
#define __TOUCH_H__

#ifdef ARDUINO_INKPLATE6PLUS

#include "Arduino.h"
#include "Graphics.h"
#include "Mcp.h"
#include "Wire.h"
#include "defines.h"

class Touch : virtual public Mcp
{
  public:
    bool inRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

    bool tsInit(uint8_t _pwrState);
    void tsShutdown();
    bool tsAvailable();
    void tsSetPowerState(uint8_t _s);
    uint8_t tsGetPowerState();
    uint8_t tsGetData(uint16_t *xPos, uint16_t *yPos);

    virtual int getRotation() = 0;

  private:
    const char hello_packet[4] = {0x55, 0x55, 0x55, 0x55};
    uint16_t _tsXResolution;
    uint16_t _tsYResolution;

    uint8_t tsWriteRegs(uint8_t _addr, const uint8_t *_buff, uint8_t _size);
    void tsReadRegs(uint8_t _addr, uint8_t *_buff, uint8_t _size);
    void tsHardwareReset();
    bool tsSoftwareReset();
    void tsGetRawData(uint8_t *b);
    void tsGetXY(uint8_t *_d, uint16_t *x, uint16_t *y);
    void tsGetResolution(uint16_t *xRes, uint16_t *yRes);

    int32_t touchT = 0;
    uint16_t touchX[2], touchY[2], touchN;
};

#endif

#endif