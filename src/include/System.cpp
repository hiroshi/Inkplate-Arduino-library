/*
System.cpp
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

#include "System.h"

SPIClass spi2(HSPI);
SdFat sd(&spi2);

void System::setPanelState(uint8_t s)
{
    _panelOn = s;
}

uint8_t System::getPanelState()
{
    return _panelOn;
}

int8_t System::readTemperature()
{
    int8_t temp;
    if (getPanelState() == 0)
    {
        WAKEUP_SET;
        PWRUP_SET;
        delay(5);
    }
    Wire.beginTransmission(0x48);
    Wire.write(0x0D);
    Wire.write(B10000000);
    Wire.endTransmission();
    delay(5);

    Wire.beginTransmission(0x48);
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.requestFrom(0x48, 1);
    temp = Wire.read();
    if (getPanelState() == 0)
    {
        PWRUP_CLEAR;
        WAKEUP_CLEAR;
        delay(5);
    }
    return temp;
}

uint8_t System::readTouchpad(uint8_t _pad)
{
    return digitalReadInternal(MCP23017_INT_ADDR, mcpRegsInt, _pad);
}

double System::readBattery()
{
#ifdef ARDUINO_ESP32_DEV
    digitalWriteInternal(MCP23017_INT_ADDR, mcpRegsInt, 9, LOW);
#else
    digitalWriteInternal(MCP23017_INT_ADDR, mcpRegsInt, 9, HIGH);
#endif
    delay(1);
    int adc = analogRead(35);
#ifdef ARDUINO_ESP32_DEV
    digitalWriteInternal(MCP23017_INT_ADDR, mcpRegsInt, 9, HIGH);
#else
    digitalWriteInternal(MCP23017_INT_ADDR, mcpRegsInt, 9, LOW);
#endif
    // Calculate the voltage using the following formula
    // 1.1V is internal ADC reference of ESP32, 3.548133892 is 11dB in linear scale (Analog signal is attenuated by 11dB
    // before ESP32 ADC input)
    return (double(adc) / 4095 * 1.1 * 3.548133892 * 2);
}

int16_t System::sdCardInit()
{
    spi2.begin(14, 12, 13, 15);
    setSdCardOk(sd.begin(15, SD_SCK_MHZ(25)));
    return getSdCardOk();
}

SdFat System::getSdFat()
{
    return sd;
}

SPIClass System::getSPI()
{
    return spi2;
}

void System::setSdCardOk(int16_t s)
{
    _sdCardOk = s;
}

int16_t System::getSdCardOk()
{
    return _sdCardOk;
}