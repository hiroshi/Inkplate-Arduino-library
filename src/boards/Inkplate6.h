#ifndef INKPLATE6_H
#define INKPLATE6_H

#define E_INK_WIDTH  800
#define E_INK_HEIGHT 600

#define MCP23017_IODIRA 0x00
#define MCP23017_GPPUA  0x0C
#define MCP23017_ADDR   0x20

#define MCP23017_GPIOA    0x12
#define MCP23017_IOCONA   0x0A
#define MCP23017_INTCONA  0x08
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA  0x06
#define MCP23017_INTFA    0x0E
#define MCP23017_INTCAPA  0x10
#define MCP23017_INTFB    0x0F
#define MCP23017_INTCAPB  0x11
#define MCP23017_GPIOB    0x13

#define MCP23017_INT_ADDR 0x20
#define MCP23017_EXT_ADDR 0x20

#define WAVEFORM3BIT                                                                                                   \
    {{0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 2, 1, 1, 2, 1, 0}, {1, 1, 1, 2, 2, 1, 0, 0}, {0, 0, 0, 1, 1, 1, 2, 0},           \
     {2, 1, 1, 1, 2, 1, 2, 0}, {2, 2, 1, 1, 2, 1, 2, 0}, {1, 1, 1, 2, 1, 2, 2, 0}, {0, 0, 0, 0, 0, 0, 2, 0}};

#endif