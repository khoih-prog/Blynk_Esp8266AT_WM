## Blynk_Esp8266AT_WM

[![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_Esp8266AT_WM.svg?)](https://www.ardu-badge.com/Blynk_Esp8266AT_WM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Blynk_Esp8266AT_WM.svg)](https://github.com/khoih-prog/Blynk_Esp8266AT_WM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Blynk_Esp8266AT_WM/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Blynk_Esp8266AT_WM.svg)](http://github.com/khoih-prog/Blynk_Esp8266AT_WM/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Major Releases v1.3.0](#major-releases-v130)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.1](#releases-v111)
  * [Major Releases v1.1.0](#major-releases-v110)
  * [Releases v1.0.7](#releases-v107)
  * [Releases v1.0.6](#releases-v106)
  * [Major Releases v1.0.5](#major-releases-v105)
  * [Releases v1.0.4](#releases-v104)
  * [Releases v1.0.3](#releases-v103)
  * [Releases v1.0.2](#releases-v102)

---
---


## Changelog

### Major Releases v1.3.0

1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico core** v1.4.0+](https://github.com/earlephilhower/arduino-pico) to use with or without Blynk/WiFiManager features.
2. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) to use without Blynk/WiFiManager features.
3. Fix bug
4. Optimize code
5. Update examples with new features

### Releases v1.2.0

1. Use new and more efficient [FlashStorage_STM32](https://github.com/khoih-prog/FlashStorage_STM32) and [FlashStorage_SAMD](https://github.com/khoih-prog/FlashStorage_SAMD) library versions.
2. Fix Config Portal bug

### Releases v1.1.1

1. Add support to **Teensy 3.x boards**, using only Teensy core v1.51 if Config Portal is needed.

### Major Releases v1.1.0

1. Restore support to **Teensy 4.x boards**, using only Teensy core v1.51 if Config Portal is needed.
2. Add STM32 emulated-EEPROM feature so that saving to EEPROM is usable and much faster.
3. Add functions to control Config Portal from software or Virtual Switches. Check [How to trigger a Config Portal from code #25](https://github.com/khoih-prog/Blynk_WM/issues/25)
4. Renew all examples to demo the new Virtual ConfigPortal SW feature
5. Optimize code and fix many bugs.

### Releases v1.0.7

1. Add support to all **STM32F/L/H/G/WB/MP1** (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.)
2. Add support to **Seeeduino SAMD21/SAMD51 boards** (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)
3. Sync with latest [**ESP8266_AT_WebServer Library v1.0.12**](https://github.com/khoih-prog/ESP8266_AT_WebServer/releases/tag/v1.0.12)

### Releases v1.0.6

1. Add support to **ESP32-AT**
2. Use new [**ESP_AT_Lib**](https://github.com/khoih-prog/ESP_AT_Lib) to support ESP8266/ESP32-AT
3. Enhance MultiWiFi connection logic.
4. New logic for `USE_DEFAULT_CONFIG_DATA` to autoload Config / Dynamic Data in developing stage.

### Major Releases v1.0.5

1. Add support to ***nRF52 (AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.)***. Dynamic custom parameters to be saved ***automatically in LittleFS***.
2. Add support to ***Adafruit SAMD21/SAM51 (Itsy-Bitsy M0/M4, Metro M0/M4, Grand Central M4, Feather M0/M4 Express, etc.)***. Dynamic custom parameters to be saved ***automatically in FlashStorage***.
3. Add ***MultiWiFi*** features for WiFi
4. Add ***DoubleResetDetector*** (DRD) feature.
5. Increase WPA2 SSID and PW to 63 chars. Permit special chars such as !,@,#,$,%,^,&,* into data fields.
6. Restructure examples separate Credentials / Defines / Dynamic Params / Code.
7. Drop support to **Teensy** boards.

### Releases v1.0.4

1. Add support to **SAM DUE**
2. Reduce html and code size for faster Config Portal response. 
3. Enhance GUI.
4. Config Portal AP SSID and Password will use 4 bytes of hardware unique macAddress, only for Teensy.

### Releases v1.0.3

1. Add support to **STM32F/L/H/G/WB/MP1** boards. STM32F0 boards are not supported.
2. Add clearConfigData() function.

### Releases v1.0.2

1. Add support to **SAMD** (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.) boards

To help you to eliminate `hardcoding` your Wifi and Blynk credentials for Mega/Teensy boards running ESP8266 AT shields, and updating/reflashing every time when you need to change them. Configuration data are saved in configurable locatioon in EEPROM.

With version `v1.0.0` or later, you now can configure:

1. `Config Portal Static IP address, Name and Password.`
2. `Static IP address, Gateway, Subnet Mask and 2 DNS Servers IP addresses.`


