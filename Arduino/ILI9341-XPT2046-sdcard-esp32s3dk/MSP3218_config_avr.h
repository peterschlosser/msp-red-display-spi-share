// GPIO Pin Configuration for the Arduino Uno R3 (ATmega328P)
// this configuration places all three systems (display, touch, sd-card) on
// the same SPI bus and uses 9 GPIO pins.  compare to the pin configuration
// suggested by the MSP3218 module documentation using up to 16 GPIO pins.
// Ver 1 initial testing and release
#ifndef _MSP3218_CONFIG_H
#define _MSP3218_CONFIG_H

// ILI9341 SPI TFT LCD Controller
#define TFT_CLK 13  // standard SPI SCK (MCU PB5)
#define TFT_MISO 12 // standard SPI MISO (MCU PB4)
#define TFT_MOSI 11 // standard SPI MOSI (MCU PB3)
#define TFT_CS 10   // standard config (MCU PB2)
#define TFT_DC 8    // data/command
#define TFT_RST 7   // MSP3218 needs reset
#define TFT_LED 9   // LED backlight (PWM capable)
#define TFT_SPI_SPD (4L * 1024 * 1024)

// XPT2046 SPI Touch Panel Controller
#define TS_CLK 13  // shared with TFT
#define TS_MISO 12 // shared with TFT
#define TS_MOSI 11 // shared with TFT
#define TS_CS 6    // chip/slave select
#define TS_IRQ -1  // unimplemented
#define TS_SPI_SPD (2L * 1024 * 1024)

// SPI Standard-SD (SDHC) Card Connector
#define SD_CLK 13  // shared with TFT
#define SD_MISO 12 // shared with TFT
#define SD_MOSI 11 // shared with TFT
#define SD_CS 5    // chip/slave select
#define SD_SPI_SPD (4L * 1024 * 1024)

// other MCU-specific systems
#define I2C_SDA A4 // default Arduino Uno R3 I2C_DATA
#define I2C_SCL A5 // default Arduino Uno R3 I2C_CLK
#define UART0_RX 0 // Serial.print() default Arduino Uno R3 USB interface
#define UART0_TX 1 // Serial.print() default Arduino Uno R3 USB interface

#endif