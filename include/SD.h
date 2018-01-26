#ifndef _SD_H_
#define _SD_H_

#include <stdint.h>
#include <stdio.h>

// This example can use SDMMC and SPI peripherals to communicate with SD card.
// By default, SDMMC peripheral is used.
// To enable SPI mode, uncomment the following line:

// #define USE_SPI_MODE
//
// // When testing SD and SPI modes, keep in mind that once the card has been
// // initialized in SPI mode, it can not be reinitialized in SD mode without
// // toggling power to the card.
//
// #ifdef USE_SPI_MODE
// // Pin mapping when using SPI mode.
// // With this mapping, SD card can be used both in SPI and 1-line SD mode.
// // Note that a pull-up on CS line is required in SD mode.
// #define PIN_NUM_MISO 19
// #define PIN_NUM_MOSI 18
// #define PIN_NUM_CLK  5
// #define PIN_NUM_CS   14
// #define MAX_BUFSIZE 16384
// #endif //USE_SPI_MODE

class SD
{
public:
    SD();
    // int init();
    int init(int pin_num_miso, int pin_num_mosi, int pin_num_clk, int pin_num_cs);
    int readFile(const char *filename, uint8_t** buf);
    FILE* openFile(const char *filename, const char *mode);
    void closeFile(FILE* f);
    int read(FILE* f, uint8_t* buf, size_t toRead);
    // int write(const char *filename);
    void listFiles();
    void close();
};

#endif
