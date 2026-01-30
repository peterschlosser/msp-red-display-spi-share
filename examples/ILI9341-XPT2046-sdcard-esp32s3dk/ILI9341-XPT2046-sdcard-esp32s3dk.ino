//
// author: pschlosser707@gmail.com
// a simple project for TFT 240x320 "Red Display" on the ESP32 platform.
// demonstrates function of MSP3218 module containing integrated display,
// resistive touch and sd-card.
// Uses same SPI bus for display + touch + sd-card.
//
// optimized for:
// - the ESP32-S3-DevKitC-1.
// - the MSP3218 TFT SPI "Red Display" using the ILI9341 and XPT2046.
//
// a hybrid project one can build in either Arduino IDE or PlatformIO.
// - ArduinoIDE target: ESP32S3 Dev Module
// - PlatformIO target: esp32-s3-devkitc-1 (espressif32)
//
// theory of operation:
//  sets up display, touch and sd-card.
//  prints startup messages to display & serial.
//  prints run messages in loop() to serial.
//  when display is touched, prints coordinates to serial.
//  after startup (10 seconds) loop() will access sd-card one time to demo access.
//  every 1000 ms (1 second) in loop(), prints a serial message to demo operation.
//  sd-card must be installed and formatted (FAT16 <= 2GB, FAT32 <= 32GB) to
//  perform sd-card function.
//
// software dependencies:
//  adafruit/Adafruit ILI9341 library and its 6+ dependencies
//  arduino-libraries/SD
//  paulstoffregen/XPT2046_Touchscreen
//
// hardware test config:
//  ESP32-S3-DevKitC-1 N16R8 (ESP32-S3-WROOM-1)
//  Freenove Breakout for ESP32-S3 FNK0091
//  MSP3218 TFT LCD 3.2-inch SPI Module ILI9341 "Red Display" (TFT)
//  - integrated SPI XPT2046 Resistive Touch Panel (RTP)
//  - integrated SPI MicroSD Card (SD)
//    when powering the display VCC with 3V3, it's best to close solder
//    jumper J1, bypassing the U1 (XC6202) 3V3 voltage regulator.

#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>
#include "MSP3218_config_esp32.h"
#include "SPI.h"
#include "SD.h"

#define TFT_ROTATION 1

Adafruit_ILI9341 *tft = nullptr;
XPT2046_Touchscreen *ts = nullptr;
enum sdcard_state_t
{
  OFFLINE = 0,
  STARTED,
  READY
} sd_state;

void demo_sdcard()
{
  if (sd_state == OFFLINE)
    return; // nothing to do

  uint8_t card_type = SD.cardType();
  if (SD.cardType() == CARD_NONE)
  {
    tft->println(F("warning: no SD card detected."));
    Serial.println(F("warning: no SD card detected."));
    sd_state = STARTED;
    return;
  }
  sd_state = READY; // sdcard installed

  tft->print(F("sd-card Type: "));
  switch (card_type)
  {
  default:
    tft->println(F("UNKNOWN"));
    return;
  case CARD_MMC:
    tft->println(F("MMC"));
    break;
  case CARD_SD:
    tft->println(F("SD"));
    break;
  case CARD_SDHC:
    tft->println(F("SDHC"));
    break;
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  tft->print(F("sd-card Size: "));
  tft->print(cardSize);
  tft->println(F("MB"));
}
void demo_touch()
{
  if (ts == nullptr)
    return;

  if (ts->touched())
  {
    TS_Point p = ts->getPoint();
    Serial.print(p.x);
    Serial.print(F(","));
    Serial.print(p.y);
    Serial.print(F(","));
    Serial.println(p.z);
  }
}

bool setup_display()
{
  // Adafruit_ILI9341 treats the ILI9341 as write-only.
  // begin() never fails, even when device is not present.
  tft = new Adafruit_ILI9341(&SPI, TFT_DC, TFT_CS, TFT_RST);
  tft->begin(TFT_SPI_SPD);
#if defined(TFT_ROTATION)
  tft->setRotation(TFT_ROTATION);
#endif
  tft->fillScreen(0x0000);
  tft->setCursor(0, 0);
  tft->setTextSize(1); // 6x8
  tft->setTextColor(0xFFFF, 0x0000);
  digitalWrite(TFT_LED, HIGH);
  pinMode(TFT_LED, OUTPUT);
  return true;
}
bool setup_sdcard(void)
{
  sd_state = OFFLINE;
  if (!SD.begin(SD_CS, SPI, SD_SPI_SPD))
  {
    return false;
  }
  sd_state = STARTED;
  return true;
}
bool setup_touch()
{
  // XPT2046_Touchscreen uses hard-coded SPI speed of 2MHz
  ts = new XPT2046_Touchscreen(TS_CS);
  if (!ts->begin())
  {
    return false;
  }
#if defined(TFT_ROTATION)
  ts->setRotation(TFT_ROTATION);
#endif
  // ts->setThresholds(500);
  return true;
}

void setup(void)
{
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  // deselect all SPI devices on shared SPI (CS active LOW) prior to setup.
  digitalWrite(TFT_CS, HIGH);
  pinMode(TFT_CS, OUTPUT);
  digitalWrite(TS_CS, HIGH);
  pinMode(TS_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  pinMode(SD_CS, OUTPUT);
  SPI.begin();

  setup_display();
  tft->println(F("display started"));
  Serial.println(F("display started"));

  if (!setup_touch())
  {
    tft->println(F("touch failure, halted"));
    Serial.println(F("touch failure, halted"));
    while (1)
      ;
  }
  tft->println(F("touch started"));
  Serial.println(F("touch started"));

  if (!setup_sdcard())
  {
    tft->println(F("sd-card failure"));
    Serial.println(F("sd-card failure"));
  }
  else
  {
    tft->println(F("sd-card started"));
    Serial.println(F("sd-card started"));
  }
}

void loop()
{
  demo_touch();

  static unsigned long run_last = 0;
  if (millis() - run_last > 1000) // every 1 second
  {
    run_last = millis();
    Serial.print(millis());
    Serial.println(F(" ..."));
  }

  static bool run_once = true;
  if (run_once && millis() > 10000) // after 10 seconds
  {
    run_once = false;
    demo_sdcard();
  }
}
