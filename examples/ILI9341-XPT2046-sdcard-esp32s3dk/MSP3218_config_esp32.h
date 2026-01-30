// GPIO Pin Configuration for the ESP32-S3-DevKitC-1 (ESP32-S3-N16R8)
// this configuration places all three systems (display, touch, sd-card) on
// the same SPI bus and uses 9 GPIO pins.  compare to the pin configuration
// suggested by the MSP3218 module documentation using up to 16 GPIO pins.
// Ver 1 initial testing and release
// ver 2 adds I2C and UART pins for reference
// Ver 3 improved comments, intuitive GPIO allocation
#ifndef _MSP3218_CONFIG_H
#define _MSP3218_CONFIG_H

// ILI9341 SPI TFT LCD Controller
#define TFT_CLK 12  // standard ESP32-S3 FSPI (SPI2) SCK
#define TFT_MISO 13 // standard ESP32-S3 FSPI (SPI2) MISO
#define TFT_MOSI 11 // standard ESP32-S3 FSPI (SPI2) MOSI
#define TFT_CS 10   // standard ESP32-S3 FSPI (SPI2) SS (chip/slave select)
#define TFT_DC 7    // data/command
#define TFT_RST 6   // (TFT_eSPI and LvGL won't tolerate -1) + MSP3218 needs reset.
#define TFT_LED 5   // LED backlight (PWM capable)
// when the SPI bus of the TFT is shared with the TP, it must be slowed slightly.
// tests show the added capacitance of connecting the display + touch + sd-card
// to the shared SPI pins limits the top speed of the SPI data.
// #define TFT_SPI_SPD (40 * 1024 * 1024) // solo on SPI and/or wired PCB
#define TFT_SPI_SPD (35 * 1024 * 1024) // shared SPI and/or wired breadboard

// XPT2046 SPI Touch Panel Controller
#define TS_CLK 12  // shared with TFT
#define TS_MISO 13 // shared with TFT
#define TS_MOSI 11 // shared with TFT
#define TS_CS 4    // chip/slave select
#define TS_IRQ -1  // unimplemented
#define TS_SPI_SPD (2 * 1024 * 1024)

// SPI Standard-SD (SDHC) Card Connector
#define SD_CLK 12  // shared with TFT
#define SD_MISO 13 // shared with TFT
#define SD_MOSI 11 // shared with TFT
#define SD_CS 2    // chip/slave select
#define SD_SPI_SPD (40 * 1024 * 1024)

// other MCU-specific systems
#define I2C_SDA 8   // default ESP32-S3 I2C_DATA
#define I2C_SCL 9   // default ESP32-S3 I2C_CLK
#define UART0_RX 20 // Serial.print() default ESP32-S3 USB interface
#define UART0_TX 19 // Serial.print() default ESP32-S3 USB interface

#endif