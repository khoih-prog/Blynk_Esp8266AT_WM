## Blynk_Esp8266AT_WM

[![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_Esp8266AT_WM.svg?)](https://www.ardu-badge.com/Blynk_Esp8266AT_WM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Blynk_Esp8266AT_WM.svg)](https://github.com/khoih-prog/Blynk_Esp8266AT_WM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Blynk_Esp8266AT_WM/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Blynk_Esp8266AT_WM.svg)](http://github.com/khoih-prog/Blynk_Esp8266AT_WM/issues)

---
---

## Table of Contents

* [Why do we need this Blynk_Esp8266AT_WM library](#why-do-we-need-this-blynk_esp8266at_wm-library)
  * [Features](#features)
  * [Currently Supported Boards](#currently-supported-boards)
  * [Currently Supported AT-command shields](#currently-supported-at-command-shields)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Important Notes about AT Firmwares](#important-notes-about-at-firmwares)
  * [1. Tested OK with ESP8266-AT shields](#1-tested-ok-with-esp8266-at-shields)
  * [2. Tested OK with ESP32-AT shields](#2-tested-ok-with-esp32-at-shields)
  * [3. Where to upload AT-Firmware](#3-where-to-upload-at-firmware)
  * [4. Important Notes](#4-important-notes)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
* [How to use](#how-to-use)
* [HOWTO use default Credentials and have them pre-loaded onto Config Portal](#howto-use-default-credentials-and-have-them-pre-loaded-onto-config-portal)
  * [ 1. To load Default Credentials](#1-to-load-default-credentials)
  * [ 2. To use system default to load "blank" when there is no valid Credentials](#2-to-use-system-default-to-load-blank-when-there-is-no-valid-credentials)
  * [ 3. Example of Default Credentials](#3-example-of-default-credentials)
  * [ 4. How to add dynamic parameters from sketch](#4-how-to-add-dynamic-parameters-from-sketch)
    * [ 4.1 In defines.h](#41-in-definesh)
    * [ 4.2 In dynamicParams.h](#42-in-dynamicparamsh)
  * [ 5. If you don't need to add dynamic parameters](#5-if-you-dont-need-to-add-dynamic-parameters)
* [Important Notes for using Dynamic Parameters' ids](#important-notes-for-using-dynamic-parameters-ids)
* [Important Notes](#important-notes)
* [Why using this Blynk_Esp8266AT_WM with MultiWiFi feature](#why-using-this-blynk_esp8266at_wm-with-multiwifi-feature)
* [Examples](#examples)
  * [ 1. Mega_ESP8266Shield](examples/Mega_ESP8266Shield)
  * [ 2. nRF52_ESP8266Shield](examples/nRF52_ESP8266Shield)
  * [ 3. SAMD_ESP8266Shield](examples/SAMD_ESP8266Shield)
  * [ 4. SAM_DUE_ESP8266Shield](examples/SAM_DUE_ESP8266Shield)
  * [ 5. STM32_ESP8266Shield](examples/STM32_ESP8266Shield)
  * [ 6. **Teensy40_ESP8266Shield**](examples/Teensy40_ESP8266Shield)
  * [ 7. **Teensy40_ESP8266Shield_Single**](examples/Teensy40_ESP8266Shield_Single)
  * [ 8. **RP2040_ESP8266Shield**](examples/RP2040_ESP8266Shield). **New**
* [So, how it works?](#so-how-it-works)
* [Example nRF52_ESP8266Shield](#example-nrf52_esp8266shield)
  * [1. File nRF52_ESP8266Shield.ino](#1-file-nrf52_esp8266shieldino)
  * [2. File defines.h](#2-file-definesh) 
  * [3. File Credentials.h](#3-file-credentialsh) 
  * [4. File dynamicParams.h](#4-file-dynamicparamsh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. nRF52_ESP8266Shield using LittleFS on NRF52840_ITSYBITSY_EXPRESS with ESP8266-AT shield](#1-nrf52_esp8266shield-using-littlefs-on-nrf52840_itsybitsy_express-with-esp8266-at-shield)
  * [2. STM32_ESP8266Shield using emulated-EEPROM on STM32F7 NUCLEO_F767ZI with ESP8266-AT shield](#2-stm32_esp8266shield-using-emulated-eeprom-on-stm32f7-nucleo_f767zi-with-esp8266-at-shield)
  * [3. SAM_DUE_ESP8266Shield using DueFlashStorage on SAM-DUE with ESP8266-AT shield](#3-sam_due_esp8266shield-using-dueflashstorage-on-sam-due-with-esp8266-at-shield)
  * [4. SAMD_ESP8266Shield using FlashStorage_SAMD on Adafruit ITSYBITSY_M4 with ESP8266-AT shield](#4-samd_esp8266shield-using-flashstorage_samd-on-adafruit-itsybitsy_m4-with-esp8266-at-shield)
  * [5. Teensy40_ESP8266Shield using EEPROM on TEENSY 4.0 with ESP8266-AT shield](#5-teensy40_esp8266shield-using-eeprom-on-teensy-40-with-esp8266-at-shield)
  * [6. RP2040_ESP8266Shield using LittleFS on RASPBERRY_PI_PICO with ESP8266-AT shield](#6-rp2040_esp8266shield-using-littlefs-on-raspberry_pi_pico-with-esp8266-at-shield)
    * [6.1. No ConfigDat or Forced Config Portal => Config Portal](#61-no-configdat-or-forced-config-portal--config-portal)
    * [6.2. Save => Exit Config Portal and run normally](#62-save--exit-config-portal-and-run-normally)
  * [7. RP2040_ESP8266Shield on MBED RASPBERRY_PI_PICO with ESP8266-AT shield](#7-rp2040_esp8266shield-on-mbed-raspberry_pi_pico-with-esp8266-at-shield)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)


---
---

### Why do we need this [Blynk_Esp8266AT_WM library](https://github.com/khoih-prog/Blynk_Esp8266AT_WM)

#### Features

This is a Blynk and WiFiManager Library for configuring/auto(re)connecting **ESP8266/ESP32-AT-command** shields/modules to the available MultiWiFi APs at runtime. Connection is without SSL. Configuration data to be saved in either EEPROM, nRF52/RP2040 LittleFS, SAMD EEPROM-emulated FlashStorage, SAM-DUE DueFlashStorage or STM32 emulated EEPROM. Default Credentials as well as Dynamic custom parameters can be added and modified easily without coding knowledge. DoubleResetDetector is used to force Config Portal opening even if the Credentials are still valid.
 
This library is designed to help you to eliminate `hardcoding` your Wifi and Blynk credentials for boards using ESP8266/ESP32-AT-command shields, and updating/reflashing every time you need to change them via Config Portalor or sketch.

The **RP2040-based boards, such as RASPBERRY_PI_PICO**, are currently supported using [**Earle Philhower's arduino-pico** core v1.4.0+](https://github.com/earlephilhower/arduino-pico) with Blynk/WiFiManager features thanks to LittleFS support. 

The support to [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) with Blynk/WiFiManager features will be added in the future using **simulated-EEPROM or LittleFS** if ready then. Now you can use this core without Blynk/WiFiManager features.

New recent features:

- ***MultiWiFi*** feature for configuring/auto(re)connecting ***ESP8266/ESP32-AT*** shields to the available MultiWiFi APs at runtime.
- ***DoubleDetectDetector*** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- Configurable ***Config Portal Title*** to be either BoardName or default undistinguishable names.
- Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device
- Add functions to control Config Portal from software or Virtual Switches.

#### Currently Supported Boards

 1. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 2. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 3. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 
 4. **SAM DUE**
 
 5. **STM32F/L/H/G/WB/MP1**
 
 6. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0)** using `Teensy core 1.51`
 
 7. **AVR Mega1280, 2560, ADK.**
 
 8. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core v1.3.1+](https://github.com/earlephilhower/arduino-pico).
 

#### Currently Supported AT-command shields

 1. ESP8266-AT-command shield
 2. ESP32-AT-command shield
 3. W600 and WIS600-01S AT-command shield
 
---
---

## Prerequisites

 1. [`Arduino IDE 1.8.16+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino AVR core 1.8.3+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) for AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 3. [`Arduino Core for STM32 v2.1.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.). [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
 4. [`Teensy core 1.51`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards. **Must use Teensy core v1.51, otherwise, the Config Portal can't run.**
 5. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 6. [`Arduino SAMD core 1.8.11+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 7. [`Adafruit SAMD core 1.7.5+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 8. [`Seeeduino SAMD core 1.8.1+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 9. [`Adafruit nRF52 v1.1.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
10. [`Earle Philhower's arduino-pico core v1.9.5+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
11. [`Arduino mbed_rp2040 core 2.5.2+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) RP2040-based boards, such as RASPBERRY_PI_PICO. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
12. [`ESP_AT_Lib v1.4.0+`](https://github.com/khoih-prog/ESP_AT_Lib) for ESP8266/ESP32-AT shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_Lib.svg?)](https://www.ardu-badge.com/ESP_AT_Lib).
13. [`ESP8266_AT_WebServer v1.4.0+`](https://github.com/khoih-prog/ESP8266_AT_WebServer). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP8266_AT_WebServer.svg?)](https://www.ardu-badge.com/ESP8266_AT_WebServer).
14. [`FlashStorage_SAMD library v1.2.0+`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.). [![GitHub release](https://img.shields.io/github/release/khoih-prog/FlashStorage_SAMD.svg)](https://github.com/khoih-prog/FlashStorage_SAMD/releases/latest)
15. [`FlashStorage_STM32 v1.1.0+`](https://github.com/khoih-prog/FlashStorage_STM32) for STM32F/L/H/G/WB/MP1 boards. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_STM32.svg?)](https://www.ardu-badge.com/FlashStorage_STM32).
16. [`DueFlashStorage library v1.0.0+`](https://github.com/sebnil/DueFlashStorage) for SAM DUE. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/DueFlashStorage.svg?)](https://www.ardu-badge.com/DueFlashStorage)
17. [`DoubleResetDetector_Generic v1.7.2+`](https://github.com/khoih-prog/DoubleResetDetector_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic).
18. [`Ai-Thinker AT Firmware v1.5.4`](AT_Firmwares/At_firmware_bin1.54.zip) or [`AT Firmware v1.7.4.0`](AT_Firmwares/AT_Firmware_bin_1.7.4.0.zip) for ESP8266-AT shields.
19. [`AT version_2.1.0.0_dev`](AT_Firmwares/AT_version_2.1.0.0_dev.zip) for ESP32-AT shields.
20. [`Adafruit's LittleFS/InternalFS`](https://www.adafruit.com) for nRF52



---
---

### Important Notes about AT Firmwares

#### 1. Tested OK with ESP8266-AT shields

  - [`Ai-Thinker AT Firmware v1.5.4`](https://github.com/khoih-prog/ESP8266_AT_WebServer/blob/master/AT_Firmwares/At_firmware_bin1.54.zip)
  
    ```
    AT version:1.1.0.0(May 11 2016 18:09:56)
    SDK version:1.5.4(baaeaebb)
    Ai-Thinker Technology Co. Ltd.
    Jun 13 2016 11:29:20
    ```
  - [`AT Firmware v1.7.4.0`](https://github.com/khoih-prog/ESP8266_AT_WebServer/blob/master/AT_Firmwares/AT_Firmware_bin_1.7.4.0.zip)
  
    ```
    AT version:1.7.4.0(May 11 2020 19:13:04)
    SDK version:3.0.4(9532ceb)
    compile time:May 27 2020 10:12:17
    Bin version(Wroom 02):1.7.4
    ```
    
  - [`WIS600-01S`](https://www.aliexpress.com/item/32956707239.html) and [`W600`](https://www.seeedstudio.com/w600.html) using either ESP8266 or ESP32-AT commands and stock firmware
  
    ```
    AT version:1.1.4(Dec 05 2018 11:06:45)
    SDK version:3.0.0
    Dec 05 2018 11:06:45
    ```
  
  
#### 2. Tested OK with ESP32-AT shields

  - [`AT version_2.1.0.0_dev`](https://github.com/khoih-prog/ESP8266_AT_WebServer/blob/master/AT_Firmwares/AT_version_2.1.0.0_dev.zip)
    
    ```
    AT version:2.1.0.0-dev(4f6b92c - Jun 10 2020 10:36:54)
    SDK version:v4.0.1-193-ge7ac221b4
    compile time(b85a8df):Jun 18 2020 14:00:59
    Bin version:2.0.0(WROOM-32)
    ```
    
    See instructions at [AT Command Core](https://github.com/espressif/esp-at) and [ESP_AT_Get_Started](https://github.com/espressif/esp-at/blob/master/docs/en/get-started/ESP_AT_Get_Started.md)
  
  
#### 3. Where to upload AT-Firmware
  
Upload [`AT Firmware v1.7.4.0`](https://github.com/khoih-prog/ESP8266_AT_WebServer/blob/master/AT_Firmwares/AT_Firmware_bin_1.7.4.0.zip) bin files to correct locations as follows:

```
# BOOT MODE

### Flash size 8Mbit: 512KB+512KB
    boot_v1.2+.bin              0x00000
    user1.1024.new.2.bin        0x01000
    esp_init_data_default.bin   0xfc000
    blank.bin                   0x7e000 & 0xfe000


### Flash size 16Mbit-C1: 1024KB+1024KB
    boot_v1.2+.bin              0x00000
    user1.2048.new.5.bin        0x01000
    esp_init_data_default.bin   0x1fc000
    blank.bin                   0xfe000 & 0x1fe000
```

#### 4. Important Notes

* Test before using different AT-Firmware Version at your own risks. Just use any simple example to verify if the AT-firmware is OK.

* Compatible AT-Firmare version will be updated. Check for all supported AT Firmwares and download them from [AT_Firmwares](https://github.com/khoih-prog/ESP8266_AT_WebServer/tree/master/AT_Firmwares).

* Support to ESP32-AT-command shields has been added to permit using new library [ESP_AT_Lib](https://github.com/khoih-prog/ESP_AT_Lib) to replace [Blynk's BlynkESP8266_Lib](https://github.com/blynkkk/blynk-library/releases/Blynk_Release_v0.6.1.zip). The same [ESP_AT_Lib](https://github.com/khoih-prog/ESP_AT_Lib) can also be use for ESP8266-AT shields.

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `Blynk_Esp8266AT_WM`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_Esp8266AT_WM.svg?)](https://www.ardu-badge.com/Blynk_Esp8266AT_WM) for more detailed instructions.

Then copy [BlynkDetectDevice.h](https://github.com/khoih-prog/Blynk_Esp8266AT_WM/blob/master/src/Blynk/BlynkDetectDevice.h) to folder ~/Arduino/libraries/Blynk/src/Blynk to overwrite the original file `BlynkDetectDevice.h`.

### Manual Install

Another way to install is to:

1. Navigate to [Blynk_Esp8266AT_WM](https://github.com/khoih-prog/Blynk_Esp8266AT_WM) page.
2. Download the latest release `Blynk_Esp8266AT_WM-master.zip`.
3. Extract the zip file to `Blynk_Esp8266AT_WM-master` directory 
4. Copy whole `Blynk_Esp8266AT_WM-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

Then copy [BlynkDetectDevice.h](https://github.com/khoih-prog/Blynk_Esp8266AT_WM/blob/master/src/Blynk/BlynkDetectDevice.h) to folder `~/Arduino/libraries/Blynk/src/Blynk` to overwrite the original file `BlynkDetectDevice.h`. By doing this, the correct board type can be displayed correctly along with Blynk logo as follows:

```
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on NRF52840_ITSYBITSY_EXPRESS
```

not just unknown Arduino board type:

```
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on Arduino
```

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Blynk_Esp8266AT_WM** library](https://platformio.org/lib/show/7061/Blynk_Esp8266AT_WM) by using [Library Manager](https://platformio.org/lib/show/7061/Blynk_Esp8266AT_WM/installation). Search for **Blynk_Esp8266AT_WM** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.1.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0). 

Supposing the Adafruit nRF52 version is 1.1.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.15/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.15. These files must be copied into the directory:

- `./arduino-1.8.15/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.15/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.15/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.15/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.11) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.11).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.11. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.11/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.5) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.5). 

Supposing the Adafruit SAMD core version is 1.7.5. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.5/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.5/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.5/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2). 

Supposing the Seeeduino SAMD core version is 1.8.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.1.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.1.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.1.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.1.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.1.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.1.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.1.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.1.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.1.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.1.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.1.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/2.5.2/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 2.5.2. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


---

### How to use

In your code, to use WiFiManager Blynk features, replace

1. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_WM.h` for Mega boards.
2. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_nRF52_WM.h`  for nRF52 boards.
3. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_SAMD_WM.h`  for SAMD boards.
4. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_DUE_WM.h`  for SAM DUE boards.
5. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_STM32_WM.h`  for STM32 boards.
6. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_Teensy_WM.h`  for Teensy boards using multiWiFi APs.
7. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_Teensy_WM_Single.h`  for Teensy boards using single WiFi AP.

to use Blynk only, with hardcoded Credentials, replace

1. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_nRF52.h`  for nRF52 boards.
2. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_SAMD.h`  for SAMD boards.
3. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_DUE.h`  for SAMD boards.
4. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_STM32.h`  for STM32 boards.
5. Keep the same`BlynkSimpleShieldEsp8266.h` for Mega boards
6. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_Teensy.h`  for Teensy boards.

- For Mega, Config Data is stored in EEPROM ( 184 bytes for Mega from address EEPROM_START ) to save your configuration data. EEPROM_SIZE can be specified from 512 to 4096 bytes.
- For STM32 boards, Config Data is stored in emulated-EEPROM ( 280 bytes for STM32 boards from address EEPROM_START ) to save your configuration data. EEPROM_SIZE can be up to 16K bytes. The STM32 Arduino core provides a buffered access API to the emulated-EEPROM.
- For nRF52 boards, Config Data is stored in LittleFS.
- For SAMD boards, Config Data is stored in FlashStorage using 256-byte block.
- For SAM DUE boards, Config Data is stored in DueFlashStorage.

To use personalized Config Portal AP SSID and Password, as well as IP Address, channel e.g. call :

```cpp

  ESP8266 wifi(&EspSerial);
  // initialize serial for ESP module
  EspSerial.begin(ESP8266_BAUD);
  
  ...
  
  // Optional to change default AP IP(192.168.4.1) and channel(10)
  //Blynk.setConfigPortalIP(IPAddress(192, 168, 132, 1));
  // Personalized portal_ssid and password
  Blynk.setConfigPortal(portal_ssid, portal_password);
  //Blynk.setConfigPortal("STM32_WM", "MySTM32_PW");
  Blynk.setConfigPortalChannel(0);

  Blynk.begin(wifi);
```

Then replace `Blynk.begin(...)` with `Blynk.begin(wifi);`


in your code. Keep `Blynk.run()` intact.

That's it.

---
---

### HOWTO Use default Credentials and have them pre-loaded onto Config Portal

See this example and modify as necessary

#### 1. To load [Default Credentials](examples/STM32_ESP8266Shield/Credentials.h)

```cpp
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

#### 2. To use system default to load "blank" when there is no valid Credentials

```cpp
bool LOAD_DEFAULT_CONFIG_DATA = false;
```

#### 3. Example of [Default Credentials](examples/STM32_ESP8266Shield/Credentials.h)

```cpp
#ifndef Credentials_h
#define Credentials_h

#include "defines.h"

/// Start Default Config Data //////////////////

/*
#define SSID_MAX_LEN      32
//From v1.0.3, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
}  WiFi_Credentials;

#define NUM_WIFI_CREDENTIALS      2

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 4 )
////////////////

typedef struct Configuration
{
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char blynk_server   [32];
  char blynk_token    [36];
  int  checkSum;
} Blynk_WF_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      false    //true

#if TO_LOAD_DEFAULT_CONFIG_DATA

// Use LOAD_DEFAULT_CONFIG_DATA = true in development stage to avoid repeatedly input config data
// Default Config Data will override Data input from Config Portal (CP)
// Use LOAD_DEFAULT_CONFIG_DATA = false in normal operation, and use dummy value here
// Data input from Config Portal (CP) will override Default Config Data
bool LOAD_DEFAULT_CONFIG_DATA = false;

Blynk_WF_Configuration defaultConfig =
{
  //char header[16], dummy, not used
  "STM32_ESP_AT",
  
  // WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  // WiFi_Credentials.wifi_ssid and WiFi_Credentials.wifi_pw
#if 1
  "realSSID",  "realPass",
  "realSSID1",  "realPass1",
  // Blynk_Creds : blynk_server and blynk_token
  "realServer.duckdns.org",     "realToken",
#else
  "SSID1",  "password1",
  "SSID2",  "password2",
  // Blynk_Creds : blynk_server and blynk_token
  "account.ddns.net",     "token",
#endif
  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

Blynk_WF_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////


#endif    //Credentials_h
```

### 4. How to add dynamic parameters from sketch

- To add custom parameters, just modify the example below


#### 4.1 In defines.h

```
#define USE_DYNAMIC_PARAMETERS                    true
```

#### 4.2 In dynamicParams.h

```cpp
#ifndef dynamicParams_h
#define dynamicParams_h

#if USE_BLYNK_WM

// USE_DYNAMIC_PARAMETERS defined in defined.h

/////////////// Start dynamic Credentials ///////////////

//Defined in <BlynkSimpleShieldEsp8266_STM32_WM.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "default-mqtt-server";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "1883";


MenuItem myMenuItems [] =
{
  { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
  { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
};

// Due to notorious 2K buffer limitation of ESO8266-AT shield, the NUM_MENU_ITEMS is limited to max 3
// to avoid WebServer not working due to HTML data larger than 2K can't be sent successfully
// The items with index larger than 3 will be ignored

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;

#endif    //USE_DYNAMIC_PARAMETERS

/////// // End dynamic Credentials ///////////

#endif      //USE_BLYNK_WM

#endif      //dynamicParams_h
```
#### 5. If you don't need to add dynamic parameters

Use the following code snippet in sketch

```cpp
#define USE_DYNAMIC_PARAMETERS     false
```

or

```cpp
/////////////// Start dynamic Credentials ///////////////

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
/////// // End dynamic Credentials ///////////

```

---
---

### Important Notes for using Dynamic Parameters' ids

1. These ids (such as "mqtt" in example) must be **unique**.

Please be noted that the following **reserved names are already used in library**:

```
"id"    for WiFi SSID
"pw"    for WiFi PW
"id1"   for WiFi1 SSID
"pw1"   for WiFi1 PW
"sv"    for Blynk Server
"tk"    for Blynk Token
```

---

### Important notes

1. Now you can use special chars such as **~, !, @, #, $, %, ^, &, _, -, space,etc.** thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix in v1.0.10 to permit input special chars such as **%** and **#** into data fields. See [Issue 3](https://github.com/khoih-prog/Blynk_WM/issues/3).
2. The SSIDs, Passwords, BlynkServers and Tokens must be input (or to make them different from **nothing**). Otherwise, the Config Portal will re-open until those fields have been changed. If you don't need any field, just input anything or use duplicated data from similar field.
3. WiFi password max length now is 63 chars according to WPA2 standard.
4. Sometimes, it's hard or not possible to connect to Config Portal WiFi AP, the majority cases are caused by WiFi channel conflict if there are too many WiFi APs running around. Please use **random ConfigPortal WiFi AP channel** in sketch (see code snippet below) and reset the board so that another channel is used. Repeat until connection is OK

```cpp
// Set config portal channel, default = 1. Use 0 => random channel from 1-13 to avoid conflict
  Blynk.setConfigPortalChannel(0);
```

---
---

### Why using this [Blynk_Esp8266AT_WM](https://github.com/khoih-prog/Blynk_Esp8266AT_WM) with MultiWiFi feature

You can see that the system **automatically detects and connects to the avaiable WiFi APs**, whenever interruption happens. This feature is very useful for systems requiring high degree of reliability.

Moreover, this `Blynk.begin()` is **not a blocking call**, so you can use it for critical functions requiring in loop().

Anyway, this is better for projects using Blynk just for GUI (graphical user interface).

In operation, if WiFi or Blynk connection is lost, `Blynk.run()` will try reconnecting automatically. Therefore, `Blynk.run()` must be called in the `loop()` function. Don't use:

```cpp
void loop()
{
  if (Blynk.connected())
     Blynk.run();
     
  ...
}
```
just

```cpp
void loop()
{
  Blynk.run();
  ...
}
```

---
---

## Examples

 1. [Mega_ESP8266Shield](examples/Mega_ESP8266Shield)
 2. [nRF52_ESP8266Shield](examples/nRF52_ESP8266Shield)
 3. [SAMD_ESP8266Shield](examples/SAMD_ESP8266Shield) 
 4. [SAM_DUE_ESP8266Shield](examples/SAM_DUE_ESP8266Shield) 
 5. [STM32_ESP8266Shield](examples/STM32_ESP8266Shield)
 6. [**Teensy40_ESP8266Shield**](examples/Teensy40_ESP8266Shield).
 7. [**Teensy40_ESP8266Shield_Single**](examples/Teensy40_ESP8266Shield_Single).
 8. [**RP2040_ESP8266Shield**](examples/RP2040_ESP8266Shield). **New**

---

## So, how it works?

If it cannot connect to the Blynk server in 30 seconds, it will switch to `Configuration Mode`. You will see your built-in LED turned ON. In `Configuration Mode`, it starts a configurable access point, default called `nRF52_XXXXXX`, `SAMD_XXXXXX`, `DUE_XXXXXX`,`Mega_XXXXXX` or `STM32_XXXXXX`. Connect to it using password `MynRF52_XXXXXX`, `MySAMD_XXXXXX`, `MyDUE_XXXXXX`, `MyMega_XXXXXX` or `MySTM32_XXXXXX`.

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_Esp8266AT_WM/blob/master/pics/AccessPoint.jpg">
</p>

After you connected, please, go to http://192.168.4.1 or the AP IP you specified.

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_Esp8266AT_WM/blob/master/pics/Main.png">
</p>

Enter your credentials : WiFi SSID/Password, Blynk Server, Port and Token, Board Name.

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_Esp8266AT_WM/blob/master/pics/Config_Portal.png">
</p>

Then click `Save`. After you restarted, you will see your built-in LED turned OFF. That means, it connected to your Blynk server successfully.

---
---

### Example [nRF52_ESP8266Shield](examples/nRF52_ESP8266Shield)

#### 1. File [nRF52_ESP8266Shield.ino](examples/nRF52_ESP8266Shield/nRF52_ESP8266Shield.ino)

```
/****************************************************************************************************************************
    Important notes:
    1) Tested OK with SAMD, Mega, nRF52, SAM DUE

    a) ESP8266-AT version:1.1.0.0(May 11 2016 18:09:56)
       SDK version:1.5.4(baaeaebb)
       Ai-Thinker Technology Co. Ltd.
       Jun 13 2016 11:29:20
    b) ESP8266-AT version:1.7.4.0(May 11 2020 19:13:04)
       SDK version:3.0.4(9532ceb)
       compile time:May 27 2020 10:12:22
       Bin version(Wroom 02):1.7.4     

    2) These versions don't work on SAMD,  but work on Mega (hanging when connect to Blynk, WiFi OK)
       To find bug and fix in Blynk ESP8266_Lib or Blynk library
 *****************************************************************************************************************************/
 
#include "defines.h"

#if USE_BLYNK_WM
  #include "Credentials.h"
  #include "dynamicParams.h"

  #define BLYNK_PIN_FORCED_CONFIG           V10
  #define BLYNK_PIN_FORCED_PERS_CONFIG      V20

// Use button V10 (BLYNK_PIN_FORCED_CONFIG) to forced Config Portal
BLYNK_WRITE(BLYNK_PIN_FORCED_CONFIG)
{
  if (param.asInt())
  {
    Serial.println( F("\nCP Button Hit. Rebooting") );

    // This will keep CP once, clear after reset, even you didn't enter CP at all.
    Blynk.resetAndEnterConfigPortal();
  }
}

// Use button V20 (BLYNK_PIN_FORCED_PERS_CONFIG) to forced Persistent Config Portal
BLYNK_WRITE(BLYNK_PIN_FORCED_PERS_CONFIG)
{
  if (param.asInt())
  {
    Serial.println( F("\nPersistent CP Button Hit. Rebooting") );

    // This will keep CP forever, until you successfully enter CP, and Save data to clear the flag.
    Blynk.resetAndEnterConfigPortalPersistent();
  }
}

#endif

ESP8266 wifi(&EspSerial);

void heartBeatPrint()
{
  static int num = 1;

  if (Blynk.connected())
  {
    Serial.print(F("B"));
  }
  else
  {
    Serial.print(F("F"));
  }

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     15000L

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    // report status to Blynk
    heartBeatPrint();

    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

void setup()
{
  // Debug console 
  Serial.begin(115200);
  while (!Serial);

  delay(200);
  
  Serial.print(F("\nStart nRF52_ESP8266Shield on ")); Serial.println(BOARD_NAME);
  Serial.println(BLYNK_ESP8266AT_WM_VERSION);
  Serial.println(ESP_AT_LIB_VERSION);

  // initialize serial for ESP module
  EspSerial.begin(ESP8266_BAUD);
  
#if USE_BLYNK_WM
  Serial.println(DOUBLERESETDETECTOR_GENERIC_VERSION);
  Serial.println(F("Start Blynk_ESP8266AT_WM"));

  // Optional to change default AP IP(192.168.4.1) and channel(10)
  //Blynk.setConfigPortalIP(IPAddress(192, 168, 152, 1));
  // Personalized portal_ssid and password
  Blynk.setConfigPortal(portal_ssid, portal_password);
  //Blynk.setConfigPortal("nRF52_WM", "MynRF52_PW");
  Blynk.setConfigPortalChannel(0);
  
  Blynk.begin(wifi);
#else
  Serial.print(F("Start Blynk no WM with BlynkServer = "));
  Serial.print(BlynkServer);
  Serial.print(F(" and Token = "));
  Serial.println(auth);
  
  Blynk.begin(auth, wifi, ssid, pass, BlynkServer.c_str(), BLYNK_SERVER_HARDWARE_PORT);
#endif
}

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
void displayCredentials()
{
  Serial.println("\nYour stored Credentials :");

  for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
  }
}

void displayCredentialsInLoop()
{
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
}
#endif

void loop()
{
  Blynk.run();
  check_status();

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
  displayCredentialsInLoop();
#endif 
}
```

#### 2. File [defines.h](examples/nRF52_ESP8266Shield/defines.h)

```cpp
#ifndef defines_h
#define defines_h

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT                   Serial

// Debug level, 0-3
#define BLYNK_WM_DEBUG                3

#define USE_NEW_WEBSERVER_VERSION     true  //false
#define _ESP_AT_LOGLEVEL_             0
#define _ESP_AT_LIB_LOGLEVEL_         0

/* Comment this out to disable prints and save space */
#define DRD_GENERIC_DEBUG         true

/* Comment this out to disable prints and save space */
#define ESP_AT_DEBUG_OUTPUT       Serial
//#define ESP_AT_LIB_DEBUG_OUTPUT   Serial

#define ESP_AT_DEBUG              true
#define ESP_AT_LIB_DEBUG          true

// Uncomment to use ESP32-AT commands
//#define USE_ESP32_AT      true

// USE_ESP_AT_LIB == true to use new ESP_AT_Lib, instead of ESP8266_Lib
// For ESP32-AT, must use ESP_AT_Lib
#if (defined(USE_ESP32_AT) && USE_ESP32_AT )
  #define USE_ESP_AT_LIB    true
#else
  #define USE_ESP_AT_LIB    true
  //#define USE_ESP_AT_LIB    false
#endif

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
      defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
  #if defined(ESP8266_AT_USE_NRF528XX)
    #undef ESP8266_AT_USE_NRF528XX
  #endif
  #define ESP8266_AT_USE_NRF528XX      true
#else
  #error This code is intended to run only on the nRF52 boards ! Please check your Tools->Board setting.
#endif

#if (ESP8266_AT_USE_NRF528XX)

  #if defined(NRF52840_FEATHER)
    #define BOARD_TYPE      "NRF52840_FEATHER_EXPRESS"
  #elif defined(NRF52832_FEATHER)
    #define BOARD_TYPE      "NRF52832_FEATHER"
  #elif defined(NRF52840_FEATHER_SENSE)
    #define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
  #elif defined(NRF52840_ITSYBITSY)
    #define BOARD_TYPE      "NRF52840_ITSYBITSY_EXPRESS"
  #elif defined(NRF52840_CIRCUITPLAY)
    #define BOARD_TYPE      "NRF52840_CIRCUIT_PLAYGROUND"
  #elif defined(NRF52840_CLUE)
    #define BOARD_TYPE      "NRF52840_CLUE"
  #elif defined(NRF52840_METRO)
    #define BOARD_TYPE      "NRF52840_METRO_EXPRESS"
  #elif defined(NRF52840_PCA10056)
    #define BOARD_TYPE      "NORDIC_NRF52840DK"
  #elif defined(NINA_B302_ublox)
    #define BOARD_TYPE      "NINA_B302_ublox"
  #elif defined(NINA_B112_ublox)
    #define BOARD_TYPE      "NINA_B112_ublox"
  #elif defined(PARTICLE_XENON)
    #define BOARD_TYPE      "PARTICLE_XENON"
  #elif defined(MDBT50Q_RX)
    #define BOARD_TYPE      "RAYTAC_MDBT50Q_RX"
  #elif defined(ARDUINO_NRF52_ADAFRUIT)
    #define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
  #else
    #define BOARD_TYPE      "nRF52 Unknown"
  #endif

#define EspSerial Serial1

#endif    //ESP8266_AT_USE_NRF528XX

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#define USE_BLYNK_WM      true
//#define USE_BLYNK_WM      false

#if USE_BLYNK_WM
  #define USE_DYNAMIC_PARAMETERS                    true
  
  #include <BlynkSimpleShieldEsp8266_nRF52_WM.h>
#else
  #include <BlynkSimpleShieldEsp8266_nRF52.h>
  
  #if defined(BLYNK_INFO_DEVICE)
    #undef BLYNK_INFO_DEVICE
  #endif
  
  #define BLYNK_INFO_DEVICE       BOARD_TYPE
  
  #define USE_LOCAL_SERVER      true
  
  #if USE_LOCAL_SERVER
    char auth[] = "****";
    String BlynkServer = "account.duckdns.org";
    //String BlynkServer = "192.168.2.112";
  #else
    char auth[] = "****";
    String BlynkServer = "blynk-cloud.com";
  #endif
  
  #define BLYNK_SERVER_HARDWARE_PORT    8080
  
  // Your WiFi credentials.
  char ssid[] = "****";
  char pass[] = "****";

#endif

#define HOST_NAME   "nRF52_ESP_AT"

// SSID and PW for Config Portal
String portal_ssid      = "CfgPrtl-SSID";
String portal_password  = "CfgPrtl-PW";

// Your nRF52 <-> ESP8266 baud rate:
#define ESP8266_BAUD 115200

#endif      //defines_h
```

#### 3. File [Credentials.h](examples/nRF52_ESP8266Shield/Credentials.h)

```cpp
#ifndef Credentials_h
#define Credentials_h

#include "defines.h"

/// Start Default Config Data //////////////////

/*
#define SSID_MAX_LEN      32
//From v1.0.3, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
}  WiFi_Credentials;

#define NUM_WIFI_CREDENTIALS      2

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 4 )
////////////////

typedef struct Configuration
{
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char blynk_server   [32];
  char blynk_token    [36];
  int  checkSum;
} Blynk_WF_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      true

#if TO_LOAD_DEFAULT_CONFIG_DATA

// Use LOAD_DEFAULT_CONFIG_DATA = true in development stage to avoid repeatedly input config data
// Default Config Data will override Data input from Config Portal (CP)
// Use LOAD_DEFAULT_CONFIG_DATA = false in normal operation, and use dummy value here
// Data input from Config Portal (CP) will override Default Config Data
bool LOAD_DEFAULT_CONFIG_DATA = false;    //true;

Blynk_WF_Configuration defaultConfig =
{
  //char header[16], dummy, not used
  "nRF52_ESP_AT",
  
  // WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  // WiFi_Credentials.wifi_ssid and WiFi_Credentials.wifi_pw
#if 1
  "realSSID",  "realPass",
  "realSSID1",  "realPass1",
  // Blynk_Creds : blynk_server and blynk_token
  "realServer.duckdns.org",     "realToken",
#else
  "SSID1",  "password1",
  "SSID2",  "password2",
  // Blynk_Creds : blynk_server and blynk_token
  "account.ddns.net",     "token",
#endif
  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

Blynk_WF_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////


#endif    //Credentials_h
```

#### 4. File [dynamicParams.h](examples/nRF52_ESP8266Shield/dynamicParams.h)

```cpp
#ifndef dynamicParams_h
#define dynamicParams_h

#if USE_BLYNK_WM

// USE_DYNAMIC_PARAMETERS defined in defined.h

/////////////// Start dynamic Credentials ///////////////

//Defined in <BlynkSimpleShieldEsp8266_nRF52_WM.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "mqtt-server";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "1883";


MenuItem myMenuItems [] =
{
  { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
  { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
};

// Due to notorious 2K buffer limitation of ESO8266-AT shield, the NUM_MENU_ITEMS is limited to max 3
// to avoid WebServer not working due to HTML data larger than 2K can't be sent successfully
// The items with index larger than 3 will be ignored

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;

#endif    //USE_DYNAMIC_PARAMETERS

/////// // End dynamic Credentials ///////////

#endif      //USE_BLYNK_WM

#endif      //dynamicParams_h
```
---
---

### Debug Terminal Output Samples

### 1. nRF52_ESP8266Shield using LittleFS on NRF52840_ITSYBITSY_EXPRESS with ESP8266-AT shield


#### 1.1. No ConfigDat or Forced Config Portal => Config Portal

```
Start nRF52_ESP8266Shield on NRF52840_ITSYBITSY
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[7691] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubleResetDetected
Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0xd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
[8354] LoadCfgFile 
[8355] OK
[8356] CCSum=0x1fed,RCSum=0x1fed
[8358] LoadCredFile 
[8358] OK
t-server,len=34
[8359] ChkCrR:pdata=1883,len=6
[8359] CrCCsum=0x55e,CrRCsum=0x55e
[8359] Buffer freed
[8362] LoadCredFile 
[8362] OK
[8362] CrR:pdata=mqtt-serRCsum=0x55e
[8362] Valid Stored Dynamic Data
[8362] ======= Stet1,PW=12345678
[8363] SSID1=HueNet2,PW1=12345678
[8363] Svr=account.duckdns.org,Prt=8080,Tok=token
[8363] i=0,id=mqtt,data=mqtt-server
[8363] i=1,id=mqpt,data=1883
[8363] Check if isForcedCP
[8367] LoadCPFile 
[8367] OK
[8367] bg: isForcedConfigPortal = true
[8367] bg:Stay forever in CP:Forced-Persistent
[ESP_AT] Use ES8266-AT Command
[16807] stConf:SSID=CfgPrtl-SSID,PW=CfgPrtl-PW,IP=192.168.4.1
[16807] SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
[16807] IP=192.168.4.1,CH=11
Stop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
F
Your stored Credentials :
MQTT Server = mqtt-server
Port = 1883
FFFFFFF
```

---

#### 1.2. Enter Config Portal and Save Config Data => Connect to Blynk


```
[245736] h:repl
[245744] h1:myMenuItems[0]=mqtt-server
[245745] h1:myMenuItems[1]=1883
[245745] h:HTML page size:1724
[258383] h:repl id
[258383] h:items updated =1
[258383] h:key =id, value =HueNet1
[258457] h:repl pw
[258457] h:items updated =2
[258457] h:key =pw, value =12345678
[258528] h:repl id1
[258528] h:items updated =3
[258528] h:key =id1, value =HueNet2
[258609] h:repl pw1
[258609] h:items updated =4
[258609] h:key =pw1, value =12345678
[258691] h:repl sv
[258691] h:items updated =5
[258691] h:key =sv, value =account.duckdns.org
[258777] h:repl tk
[258777] h:items updated =6
[258777] h:key =tk, value =token
[258859] h:mqtt=mqtt-server
[258859] h:items updated =7
[258859] h:key =mqtt, value =mqtt-server
[258943] h:mqpt=1883
[258943] h:items updated =8
[258943] h:key =mqpt, value =1883
[258964] h:UpdLittleFS
[258965] SaveCfgFile 
[258965] WCSum=0x1fed
[259096] OK
[259096] SaveBkUpCfgFile 
[259483] OK
[259485] SaveCredFile 
[259485] CW1:pdata=mqtt-server,len=34
[259486] CW1:pdata=1883,len=6
[259746] OK
[259746] CrWCSum=0x55e
[259749] SaveBkUpCredFile 
[259749] CW2:pdata=mqtt-server,len=34
[259750] CW2:pdata=1883,len=6
[260008] OK
[260008] clearForcedCP
[260011] SaveCPFile 
[260267] OK
[260270] SaveBkUpCPFile 
[260526] OK
[260526] h:Rst

Start nRF52_ESP8266Shield on NRF52840_ITSYBITSY
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[7919] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubleResetDetected
Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0xd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
[8583] LoadCfgFile 
[8583] OK
[8583] CCSum=0x1fed,RCSum=0x1fed
[8585] LoadCredFile 
[8585] OK
[8585] ChkCrR: Buffer allocated, Sz=35
[8585] ChkCrR:pdata=mqtt-server,len=34
[8586] ChkCrR:pdata=1883,len=6
[8586] CrCCsum=0x55e,CrRCsum=0x55e
[8586] Buffer freed
en=34
[8588] CrR:pdata=1883,len=6
[8588] CrCCsum=0x55e,CrRCsum=0x55e
[8588] Valid Stored Dynamic Data
[8588] ======= Start Stored Config Data =======
[8588] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[8589] SSID1=HueNet2,PW1=12345678
[8589] Svr=account.duckdns.orgtt,data=mqtt-server
[8589] i=1,id=mqpt,data=1883
[8589] Check if isForcedCP
[8591] LoadCPFile 
[8592] OK
[8592] bg: noConfigPortal = true
[8592] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on NRF52840_ITSYBITSY

[8592] ConMultiWifi
[8592] con2WF:SSID=HueNet1,PW=12345678
[8592] Remaining retry_time=3
[8592] Con2:HueNet1
[15159] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
[15697] Mac=5c:cf:7f:66:05:d2
[21714] IP=192.168.2.106

[21731] WOK
[21732] WOK, lastConnectedIndex=0
[21732] con2WF:OK
[21732] IP=192.168.2.106

[21749] b:WOK.TryB
[32008] Ready (ping: 13ms).
[32355] b:WBOK
Stop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
B
Your stored Credentials :
MQTT Server = mqtt-server
Port = 1883
BBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
```

---

#### 1.3. Non-persistent CP Button pressed => Config Portal

```
CP Button Hit. Rebooting
[175725] setForcedCP non-Persistent
[175727] SaveCPFile 
[175856] OK
[175858] SaveBkUpCPFile 
[175987] OK

Start nRF52_ESP8266Shield on NRF52840_ITSYBITSY
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[7466] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubleResetDetected
Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0xd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
[8129] LoadCfgFile 
[8130] OK
[8130] CCSum=0x1fed,RCSum=0x1fed
[8132] LoadCredFile 
[8132] OK
[8132] ChkCrR: Buffer allocated, Sz=35
[8132] ChkCrR:pdata=mqtt-server,len=34
[8133] ChkCrR:pdata=1883,len=6
[8133] CrCCsum=0x55e,CrRCsum=0x5 CrR:pdata=mqtt-server,len=34
[8135] CrR:pdata=1883,len=6
[813
[8135] ======= Start Stored Config Data =======
[8135] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[8136] SSID1=HueNet2,PW1=12345678
[8136] Svr=account.duckdns.org,Prt=8080,Tok=token
[8136] Check if isForcedCP
[8138] LoadCPFile 
[8138] OK
[8138] bg: isForcedConfigPortal = true
[8139] bg:Stay forever in CP:Forced-non-Persistent
[8139] clearForcedCP
[8141] SaveCPFile 
[8270] OK
[8272] SaveBkUpCPFile 
[8400] OK
[ESP_AT] Use ES8266-AT Command
[16842] stConf:SSID=CfgPrtl-SSID,PW=CfgPrtl-PW,IP=192.168.4.1
[16842] SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
[16842] IP=192.168.4.1,CH=2
Stop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
F
Your stored Credentials :
MQTT Server = mqtt-server
Port = 1883
FFFF
```

---

#### 1.4. Persistent CP Button pressed => Config Portal

```
Persistent CP Button Hit. Rebooting
[43170] setForcedCP Persistent
[43172] SaveCPFile 
[43301] OK
[43303] SaveBkUpCPFile 
[43432] OK

Start nRF52_ESP8266Shield on NRF52840_ITSYBITSY
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[7441] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubxd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
[8105] LoadCfgFile 
[8106] OK
[8106] CCSum=0x1fed,RCSum=0x1fed
[8108] LoadCredFile 
[8108] OK
[8108] ChkCrR: Buffer allocated, Sz=35
[8108] ChkCrR:pdata=mqtt-server,len=34
[8109] ChkCrR:pdata=1883,len=6
[8109] CrCCsum=0x55e,CrRCsum=0x55CrR:pdata=mqtt-server,len=34
[8111] CrR:pdata=1883,len=6
[8111] CrCCsum=0x55e,CrRCsum=0x55e
[8111] Valid Stored Dynamic Data
[8111] ======= Start Stored Config Data =======
[8111] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[8112] SSID1=HueNet2,PW1=12345678
[8112] Svr=account.duckdns.org,Prt=8080,Tok=token
[8112] i=0,id=mqtt,data=mqtt-server
[8112] i=1,id=mqpt,data=1883
[8112] Check if isForcedCP
[8115] LoadCPFile 
[8115] OK
[8115] bg: isForcedConfigPortal = true
[8115] bg:Stay forever in CP:Forced-Persistent
[ESP_AT] Use ES8266-AT Command
[16556] stConf:SSID=CfgPrtl-SSID,PW=CfgPrtl-PW,IP=192.168.4.1
[16556] SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
[16556] IP=192.168.4.1,CH=2
Stop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
F
Your stored Credentials :
MQTT Server = mqtt-server
Port = 1883
```

---
---

### 2. STM32_ESP8266Shield using emulated-EEPROM on STM32F7 NUCLEO_F767ZI with ESP8266-AT shield

#### 2.1. No ConfigDat or Forced Config Portal => Config Portal

```
Start STM32_ESP8266Shield on NUCLEO_F767ZI
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[6769] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[10646] EEPROMsz:4096
[10646] EEPROM Length():16384
[10648] CCSum=0x1fed,RCSum=0x1fed
[10651] ======= Start Stored Config Data =======
[10655] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[10660] SSID1=HueNet2,PW1=12345678
[10663] Svr=account.duckdns.org,Prt=8080,Tok=token
[10670] bg: isForcedConfigPortal = true
[10673] bg:Stay forever in CP:Forced-Persistent
[ESP_AT] Use ES8266-AT Command
[19115] stConf:SSID=CfgPrtl-SSID,PW=CfgPrtl-PW,IP=192.168.4.1
[19115] SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
[19118] IP=192.168.4.1,CH=9
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
FFF[60707] h:repl
[60707] h:HTML page size:1466
[64490] h:repl id
[64490] h:items updated =1
[64490] h:key =id, value =HueNet1
[64553] h:repl pw
[64553] h:items updated =2
[64553] h:key =pw, value =12345678
[64620] h:repl id1
[64620] h:items updated =3
[64620] h:key =id1, value =HueNet2
[64690] h:repl pw1
[64690] h:items updated =4
[64690] h:key =pw1, value =12345678
[64755] h:repl sv
[64755] h:items updated =5
[64755] h:key =sv, value =account.duckdns.org
[64819] h:repl tk
[64819] h:items updated =6
[64819] h:key =tk, value =token
[64842] h:UpdEEPROM
[64842] SaveEEPROM,Sz=16384,DataSz=0,WCSum=0x1fed
[66078] h:Rst
```

---

#### 2.2. Enter Config Portal and Save Config Data => Connect to Blynk

```
Start STM32_ESP8266Shield on NUCLEO_F767ZI
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[6768] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[9534] EEPROMsz:4096
[9534] EEPROM Length():16384
[9536] CCSum=0x1fed,RCSum=0x1fed
[9539] ======= Start Stored Config Data =======
[9543] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[9547] SSID1=HueNet2,PW1=12345678
[9550] Svr=account.duckdns.org,Prt=8080,Tok=token
[9557] bg: noConfigPortal = true
[9560] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on STM32 NUCLEO_F767ZI

[9574] ConMultiWifi
[9576] con2WF:SSID=HueNet1,PW=12345678
[9580] Remaining retry_time=3
[9583] Con2:HueNet1
[16150] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK
[16694] Mac=68:c6:3a:a4:6a:97
[23742] IP=192.168.2.96

[23759] WOK
[23759] WOK, lastConnectedIndex=0
[23759] con2WF:OK
[23761] IP=192.168.2.96

[23779] b:WOK.TryB
[33941] Ready (ping: 13ms).
[34178] b:WBOK
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
BBBBBBBBBB B
```

---

#### 2.3. Non-persistent CP Button pressed => Config Portal

```
CP Button Hit. Rebooting
[49650] setForcedCP non-Persistent

Start STM32_ESP8266Shield on NUCLEO_F767ZI
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[6769] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[9531] EEPROMsz:4096
[9531] EEPROM Length():16384
[9533] CCSum=0x1fed,RCSum=0x1fed
[9536] ======= Start Stored Config Data =======
[9540] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[9544] SSID1=HueNet2,PW1=12345678
[9547] Svr=account.duckdns.org,Prt=8080,Tok=token
[9554] bg: isForcedConfigPortal = true
[9558] bg:Stay forever in CP:Forced-non-Persistent
[ESP_AT] Use ES8266-AT Command
[19171] stConf:SSID=CfgPrtl-SSID,PW=CfgPrtl-PW,IP=192.168.4.1
[19171] SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
[19174] IP=192.168.4.1,CH=10
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
FFF
```

---

#### 2.4. Persistent CP Button pressed => Config Portal

```
Persistent CP Button Hit. Rebooting
[38325] setForcedCP Persistent

Start STM32_ESP8266Shield on NUCLEO_F767ZI
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[6769] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[10646] EEPROMsz:4096
[10646] EEPROM Length():16384
[10648] CCSum=0x1fed,RCSum=0x1fed
[10651] ======= Start Stored Config Data =======
[10655] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[10660] SSID1=HueNet2,PW1=12345678
[10663] Svr=account.duckdns.org,Prt=8080,Tok=token
[10670] bg: isForcedConfigPortal = true
[10673] bg:Stay forever in CP:Forced-Persistent
[ESP_AT] Use ES8266-AT Command
[19115] stConf:SSID=CfgPrtl-SSID,PW=CfgPrtl-PW,IP=192.168.4.1
[19115] SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
[19118] IP=192.168.4.1,CH=9
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
FFFFFF
```


---
---

### 3. SAM_DUE_ESP8266Shield using DueFlashStorage on SAM-DUE with ESP8266-AT shield

#### 3.1. No ConfigDat or Forced Config Portal => Config Portal

```
Start SAM_DUE_ESP8266Shield on SAM DUE
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[6779] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK
Flag read = 0xffffffff
No doubleResetDetected
SetFlag write = 0xd0d01234
[8311] Simulate EEPROM,Sz=1024
[8311] CCSum=0x10bf3,RCSum=0xffffffff
[8311] ChkCrR:CrCCsum=0x21de,CrRCsum=0xffffffff
[8312] Invalid Stored Dynamic Data. Load default from Sketch
[8318] SaveData,Sz=0,chkSum=0x2fc
[8333] pdata=default-mqtt-server,len=34
[8342] CrCCSum=0x79c,byteCount=38
[8342] ======= Start Loaded Config Data =======
[8342] Hdr=SHD_ESP8266,SSID=,PW=
[8342] SSID1=,PW1=
[8343] Svr=,Prt=8080,Tok=
[8345] i=0,id=mqtt,data=default-mqtt-server
[8349] bg: isForcedConfigPortal = false
[8353] bg:Stay forever in CP:No ConfigDat
[8356] clearForcedCP
[ESP_AT] Use ES8266-AT Command
[16804] stConf:SSID=CfgPrtl-SSID,PW=CfgPrtl-PW,IP=192.168.4.1
[16804] SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
[16804] IP=192.168.4.1,CH=8
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
F
Your stored Credentials :
MQTT Server = default-mqtt-server
FFF[76553] h:repl
[76566] h1:myMenuItems[0]=default-mqtt-server
[76566] h:HTML page size:1532
FFFF[126459] h:repl id
[126459] h:items updated =1
[126459] h:key =id, value =HueNet1
[126520] h:repl pw
[126520] h:items updated =2
[126520] h:key =pw, value =12345678
[126581] h:repl id1
[126581] h:items updated =3
[126581] h:key =id1, value =HueNet2
[126648] h:repl pw1
[126648] h:items updated =4
[126648] h:key =pw1, value =12345678
[126710] h:repl sv
[126710] h:items updated =5
[126710] h:key =sv, value =account.duckdns.org
[126773] h:repl tk
[126773] h:items updated =6
[126773] h:key =tk, value =token
[126836] h:mqtt=default-mqtt-server
[126836] h:items updated =7
[126836] h:key =mqtt, value =default-mqtt-server
[126854] h:UpdFlash
[126854] SaveData,Sz=0,chkSum=0x1fed
[126867] pdata=default-mqtt-server,len=34
[126876] CrCCSum=0x79c,byteCount=38
[126876] h:Rst
```

---

#### 3.2. Enter Config Portal and Save Config Data => Connect to Blynk

```
Start SAM_DUE_ESP8266Shield on SAM DUE
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[6771] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[8305] Simulate EEPROM,Sz=1024
[8305] CCSum=0x1fed,RCSum=0x1fed
[8305] ChkCrR:CrCCsum=0x79c,CrRCsum=0x79c
[8305] CrCCsum=0x79c,CrRCsum=0x79c,TotalDataSz=318
[8310] Valid Stored Dynamic Data
[8313] ======= Start Stored Config Data =======
[8317] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[8321] SSID1=HueNet2,PW1=12345678
[8324] Svr=account.duckdns.org,Prt=8080,Tok=token
[8331] i=0,id=mqtt,data=default-mqtt-server
[8334] bg: noConfigPortal = true
[8337] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on Arduino Due

[8350] ConMultiWifi
[8352] con2WF:SSID=HueNet1,PW=12345678
[8356] Remaining retry_time=3
[8358] Con2:HueNet1
[14929] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK
[15467] Mac=68:c6:3a:a4:6a:97
[22482] IP=192.168.2.96

[22500] WOK
[22500] WOK, lastConnectedIndex=0
[22500] con2WF:OK
[22500] IP=192.168.2.96

[22517] b:WOK.TryB
[32700] Ready (ping: 13ms).
[32882] b:WBOK
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
B
Your stored Credentials :
MQTT Server = default-mqtt-server
BBBBBBBBB BBBBBB
```

---

#### 3.3. Non-persistent CP Button pressed => Config Portal

```
CP Button Hit. Rebooting
[272907] setForcedCP non-Persistent

Start SAM_DUE_ESP8266Shield on SAM DUE
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[6771] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[8305] Simulate EEPROM,Sz=1024
[8305] CCSum=0x1fed,RCSum=0x1fed
[8305] ChkCrR:CrCCsum=0x79c,CrRCsum=0x79c
[8305] CrCCsum=0x79c,CrRCsum=0x79c,TotalDataSz=318
[8310] Valid Stored Dynamic Data
[8313] ======= Start Stored Config Data =======
[8317] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[8321] SSID1=HueNet2,PW1=12345678
[8324] Svr=account.duckdns.org,Prt=8080,Tok=token
[8331] i=0,id=mqtt,data=default-mqtt-server
[8334] bg: isForcedConfigPortal = true
[8338] bg:Stay forever in CP:Forced-non-Persistent
[8342] clearForcedCP
[ESP_AT] Use ES8266-AT Command
[16790] stConf:SSID=CfgPrtl-SSID,PW=CfgPrtl-PW,IP=192.168.4.1
[16790] SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
[16790] IP=192.168.4.1,CH=5
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
F
Your stored Credentials :
MQTT Server = default-mqtt-server
```

---

#### 3.4. Persistent CP Button pressed => Config Portal

```
Persistent CP Button Hit. Rebooting
[83192] setForcedCP Persistent

Start SAM_DUE_ESP8266Shield on SAM DUE
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[6771] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[8305] Simulate EEPROM,Sz=1024
[8305] CCSum=0x1fed,RCSum=0x1fed
[8305] ChkCrR:CrCCsum=0x79c,CrRCsum=0x79c
[8305] CrCCsum=0x79c,CrRCsum=0x79c,TotalDataSz=318
[8310] Valid Stored Dynamic Data
[8313] ======= Start Stored Config Data =======
[8317] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[8321] SSID1=HueNet2,PW1=12345678
[8324] Svr=account.duckdns.org,Prt=8080,Tok=token
[8331] i=0,id=mqtt,data=default-mqtt-server
[8334] bg: isForcedConfigPortal = true
[8338] bg:Stay forever in CP:Forced-Persistent
[ESP_AT] Use ES8266-AT Command
[16779] stConf:SSID=CfgPrtl-SSID,PW=CfgPrtl-PW,IP=192.168.4.1
[16779] SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
[16779] IP=192.168.4.1,CH=5
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
F
Your stored Credentials :
MQTT Server = default-mqtt-server

```

---
---

### 4. SAMD_ESP8266Shield using FlashStorage_SAMD on Adafruit ITSYBITSY_M4 with ESP8266-AT shield

#### 4.1. No ConfigDat or Forced Config Portal => Config Portal

```
Start SAMD_ESP8266Shield on ITSYBITSY_M4
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[30676] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[32204] CCSum=0x1fed,RCSum=0x1fed
[32204] ChkCrR:CrCCsum=0x55e,CrRCsum=0x55e
[32205] CrCCSum=55e,CrRCSum=55e
[32205] Valid Stored Dynamic Data
[32205] ======= Start Stored Config Data =======
[32205] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[32205] SSID1=HueNet2,PW1=12345678
[32206] Svr=account.duckdns.org,Prt=8080,Tok=token
[32206] i=0,id=mqtt,data=mqtt-server
[32206] i=1,id=mqpt,data=1883
[32206] bg: isForcedConfigPortal = true
[32207] bg:Stay forever in CP:Forced-non-Persistent
[ESP_AT] Use ES8266-AT Command
[40652] stConf:SSID=SAMD-CfgPrtl-SSID,PW=SAMD-CfgPrtl-PW,IP=192.168.4.1
[40652] SSID=SAMD-CfgPrtl-SSID,PW=SAMD-CfgPrtl-PW
[40652] IP=192.168.4.1,CH=9
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
F
Your stored Credentials :
MQTT Server = mqtt-server
Port = 1883
F
```

---

#### 4.2. Enter Config Portal and Save Config Data => Connect to Blynk

```
Start SAMD_ESP8266Shield on ITSYBITSY_M4
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[35347] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[36875] CCSum=0x1fed,RCSum=0x1fed
[36875] ChkCrR:CrCCsum=0x55e,CrRCsum=0x55e
[36875] CrCCSum=55e,CrRCSum=55e
[36876] Valid Stored Dynamic Data
[36876] ======= Start Stored Config Data =======
[36876] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[36876] SSID1=HueNet2,PW1=12345678
[36876] Svr=account.duckdns.org,Prt=8080,Tok=token
[36877] i=0,id=mqtt,data=mqtt-server
[36877] i=1,id=mqpt,data=1883
[36877] bg: noConfigPortal = true
[36877] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ADAFRUIT_ITSYBITSY_M4_EXPRESS

[36878] ConMultiWifi
[36878] con2WF:SSID=HueNet1,PW=12345678
[36878] Remaining retry_time=3
[36878] Con2:HueNet1
[43453] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
[43992] Mac=68:c6:3a:a4:6a:15
[49998] IP=192.168.2.104


[50015] WOK
[50015] WOK, lastConnectedIndex=0
[50015] con2WF:OK
[50016] IP=192.168.2.104


[50033] b:WOK.TryB
[60148] Ready (ping: 13ms).
[60330] b:WBOK
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
B
Your stored Credentials :
MQTT Server = mqtt-server
Port = 1883
BBBBB
```

---

#### 4.3. Non-persistent CP Button pressed => Config Portal

```
CP Button Hit. Rebooting
[248188] setForcedCP non-Persistent


Start SAMD_ESP8266Shield on ITSYBITSY_M4
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[30676] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[32204] CCSum=0x1fed,RCSum=0x1fed
[32204] ChkCrR:CrCCsum=0x55e,CrRCsum=0x55e
[32205] CrCCSum=55e,CrRCSum=55e
[32205] Valid Stored Dynamic Data
[32205] ======= Start Stored Config Data =======
[32205] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[32205] SSID1=HueNet2,PW1=12345678
[32206] Svr=account.duckdns.org,Prt=8080,Tok=token
[32206] i=0,id=mqtt,data=mqtt-server
[32206] i=1,id=mqpt,data=1883
[32206] bg: isForcedConfigPortal = true
[32207] bg:Stay forever in CP:Forced-non-Persistent
[ESP_AT] Use ES8266-AT Command
[40652] stConf:SSID=SAMD-CfgPrtl-SSID,PW=SAMD-CfgPrtl-PW,IP=192.168.4.1
[40652] SSID=SAMD-CfgPrtl-SSID,PW=SAMD-CfgPrtl-PW
[40652] IP=192.168.4.1,CH=9
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
F
Your stored Credentials :
MQTT Server = mqtt-server
Port = 1883
F
```

---

#### 4.4. Persistent CP Button pressed => Config Portal

```
Persistent CP Button Hit. Rebooting
[40547] setForcedCP Persistent
Start SAMD_ESP8266Shield on ITSYBITSY_M4
Blynk_Esp8266AT_WM v1.2.0
Start Blynk_ESP8266AT_WM
[34937] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[36464] CCSum=0x1fed,RCSum=0x1fed
[36464] ChkCrR:CrCCsum=0x55e,CrRCsum=0x55e
[36464] CrCCSum=55e,CrRCSum=55e
[36465] Valid Stored Dynamic Data
[36465] ======= Start Stored Config Data =======
[36465] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[36465] SSID1=HueNet2,PW1=12345678
[36465] Svr=account.duckdns.org,Prt=8080,Tok=token
[36466] i=0,id=mqtt,data=mqtt-server
[36466] i=1,id=mqpt,data=1883
[36466] bg: isForcedConfigPortal = true
[36466] bg:Stay forever in CP:Forced-Persistent
[ESP_AT] Use ES8266-AT Command
[44909] stConf:SSID=SAMD-CfgPrtl-SSID,PW=SAMD-CfgPrtl-PW,IP=192.168.4.1
[44910] SSID=SAMD-CfgPrtl-SSID,PW=SAMD-CfgPrtl-PW
[44910] IP=192.168.4.1,CH=7
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
F
Your stored Credentials :
MQTT Server = mqtt-server
Port = 1883
FF
```
---
---

### 5. Teensy40_ESP8266Shield using EEPROM on TEENSY 4.0 with ESP8266-AT shield

#### 5.1. No ConfigDat or Forced Config Portal => Config Portal


```
Start Teensy_ESP8266Shield on TEENSY 4.1/4.0
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
[8878] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK

EEPROM size = 1080, start = 0
Flag read = 0xD0D01234
doubleResetDetected
ClearFlag write = 0xD0D04321
[10402] DRD. Run ConfigPortal
[10402] ======= Start Default Config Data =======
[10402] Hdr=,SSID=,PW=
[10402] SSID1=,PW1=
[10402] Svr=,Prt=8080,Tok=
[10402] BName=Teensy
[10402] i=0,id=mqtt,data=default-mqtt-server
[10402] i=1,id=mqpt,data=1883
[10402] InitEEPROM,sz=1080
[10402] EEPROMsz:1024
[10403] ChkCrR:pdata=default-mqtt-server,len=34
[10403] ChkCrR:pdata=1883,len=6
[10403] ChkCrR:CrCCsum=0x870,CrRCsum=0x870
[10403] CCSum=0x623,RCSum=0x623
[10403] CrCCsum=0x870,CrRCsum=0x870
[10403] Valid Stored Dynamic Data
[10403] ======= Start Stored Config Data =======
[10403] Hdr=SHD_ESP8266,SSID=,PW=
[10403] SSID1=,PW1=
[10403] Svr=,Prt=8080,Tok=
[10403] BName=Teensy
[10403] i=0,id=mqtt,data=default-mqtt-server
[10403] i=1,id=mqpt,data=1883
[10403] b:Stay in CfgPortal:DRD
[ESP_AT] Use ES8266-AT Command
[18846] stConf:SSID=CfgPrtl-SSID,PW=CfgPrtl-PW,IP=192.168.200.1
[18846] SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
[18846] IP=192.168.200.1,CH=1
F
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
FFFF[106580] h:repl id
[106580] h:items updated =1
[106580] h:key =id, value =HueNet1
[106652] h:repl pw
[106652] h:items updated =2
[106652] h:key =pw, value =12345678
[106720] h:repl id1
[106720] h:items updated =3
[106720] h:key =id1, value =HueNet2
[106785] h:repl pw1
[106785] h:items updated =4
[106785] h:key =pw1, value =12345678
[106854] h:repl sv
[106854] h:items updated =5
[106854] h:key =sv, value =account.duckdns.org
[106922] h:repl tk
[106922] h:items updated =6
[106922] h:key =tk, value =token
[106990] h:mqtt=default-mqtt-server
[106990] h:items updated =7
[106990] h:key =mqtt, value =default-mqtt-server
[107055] h:mqpt=1883
[107055] h:items updated =8
[107055] h:key =mqpt, value =1883
[107077] h:UpdEEPROM
[107077] SaveEEPROM,Sz=1080,DataSz=352,WCSum=0x205a
[107079] pdata=default-mqtt-server,len=34
[107079] pdata=1883,len=6
[107079] CrCCSum=0x870
[107079] h:Rst
```

#### 5.2. Save => Exit Config Portal and run normally

```
Start Teensy_ESP8266Shield on TEENSY 4.1/4.0
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[80347] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK

EEPROM size = 1080, start = 0
Flag read = 0xD0D04321
No doubleResetDetected
SetFlag write = 0xD0D01234
[81871] ======= Start Default Config Data =======
[81871] Hdr=,SSID=,PW=
[81871] SSID1=,PW1=
[81871] Svr=,Prt=8080,Tok=
[81871] BName=Teensy
[81871] i=0,id=mqtt,data=default-mqtt-server
[81871] i=1,id=mqpt,data=1883
[81871] InitEEPROM,sz=1080
[81871] EEPROMsz:1024
[81872] ChkCrR:pdata=default-mqtt-server,len=34
[81872] ChkCrR:pdata=1883,len=6
[81872] ChkCrR:CrCCsum=0x870,CrRCsum=0x870
[81872] CCSum=0x205a,RCSum=0x205a
[81872] CrCCsum=0x870,CrRCsum=0x870
[81872] Valid Stored Dynamic Data
[81872] ======= Start Stored Config Data =======
[81872] Hdr=SHD_ESP8266,SSID=HueNet1,PW=12345678
[81872] SSID1=HueNet2,PW1=12345678
[81872] Svr=account.duckdns.org,Prt=8080,Tok=token
[81872] BName=
[81872] i=0,id=mqtt,data=default-mqtt-server
[81872] i=1,id=mqpt,data=1883
[81872] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on Teensy 4.1/4.0

[81872] ConMultiWifi
[81872] con2WF:SSID=HueNet1,PW=12345678
[81872] Remaining retry_time=3
[81872] Con2:HueNet1
[88439] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
[88977] Mac=68:c6:3a:a6:f0:f1
[94994] IP=192.168.2.32
[95011] WOK
[95011] WOK, lastConnectedIndex=0
[95011] con2WF:OK
[95011] IP=192.168.2.32
[95028] b:WOK.TryB
[105202] Ready (ping: 12ms).
[105387] b:WBOK
Stop doubleResetDetecting
ClearFlag write = 0xD0D04321
B
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883

```

---
---


### 6. RP2040_ESP8266Shield using LittleFS on RASPBERRY_PI_PICO with ESP8266-AT shield

The following is the sample terminal output when running example [RP2040_ESP8266Shield](examples/RP2040_ESP8266Shield) on RASPBERRY_PI_PICO with ESP8266-AT shield, using [**Earle Philhower's arduino-pico core** v1.4.0+](https://github.com/earlephilhower/arduino-pico) with LittleFS and Blynk/WiFiManager features

#### 6.1. No ConfigDat or Forced Config Portal => Config Portal


```
Start RP2040_ESP8266Shield on RASPBERRY_PI_PICO
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[7447] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubleResetDetected
Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0xd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
[8002] LoadCfgFile 
[8007] OK
[8007] CCSum=0x2627,RCSum=0x0
[8012] LoadCredFile 
[8013] OK
[8013] ChkCrR: Buffer allocated, Sz=35
[8013] ChkCrR:pdata=mqtt_server,len=34
[8013] ChkCrR:pdata=1883,len=6
[8013] CrCCsum=0x590,CrRCsum=0x7474716d
[8014] Buffer freed
[8014] InitCfgFile,Sz=0
[8014] g:myMenuItems[0]=blank
[8014] g:myMenuItems[1]=blank
[8014] SaveCfgFile 
[8015] WCSum=0xf2c
[8135] OK
[8136] SaveBkUpCfgFile 
[8181] OK
[8190] SaveCredFile 
[8190] CW1:pdata=blank,len=34
[8191] CW1:pdata=blank,len=6
[8197] OK
[8197] CrWCSum=0x410
[8207] SaveBkUpCredFile 
[8207] CW2:pdata=blank,len=34
[8208] CW2:pdata=blank,len=6
[8214] OK
[8214] Check if isForcedCP
[8220] LoadCPFile 
[8220] OK
[8220] bg: isForcedConfigPortal = false
[8220] bg:Stay forever in CP:No ConfigDat
[8220] clearForcedCP
[8291] SaveCPFile 
[8347] OK
[8354] SaveBkUpCPFile 
[8360] OK
[ESP_AT] Use ES8266-AT Command
[16803] stConf:SSID=CfgPrtl-SSID,PW=CfgPrtl-PW,IP=192.168.4.1
[16804] SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
[16804] IP=192.168.4.1,CH=8
Stop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
F
Your stored Credentials :
MQTT Server = blank
Port = blank
F[49922] h:repl
[49926] h1:myMenuItems[0]=blank
[49927] h1:myMenuItems[1]=blank
[49927] h:HTML page size:1663
FFFFF[111550] h: Init menuItemUpdated
[111550] h:repl id
[111550] h:items updated =1
[111550] h:key =id, value =HueNet1
[111619] h:repl pw
[111619] h:items updated =2
[111619] h:key =pw, value =password
[111685] h:repl id1
[111685] h:items updated =3
[111685] h:key =id1, value =HueNet2
[111753] h:repl pw1
[111753] h:items updated =4
[111753] h:key =pw1, value =password
[111820] h:repl sv
[111820] h:items updated =5
[111820] h:key =sv, value =account.duckdns.org
[111889] h:repl tk
[111889] h:items updated =6
[111889] h:key =tk, value =token
[111957] h:mqtt=mqtt_server
[111957] h:items updated =7
[111958] h:key =mqtt, value =mqtt_server
[112027] h:mqpt=1883
[112027] h:items updated =8
[112027] h:key =mqpt, value =1883
[112049] h:UpdLittleFS
[112049] SaveCfgFile 
[112049] WCSum=0x1fed
[112091] OK
[112092] SaveBkUpCfgFile 
[112195] OK
[112202] SaveCredFile 
[112202] CW1:pdata=mqtt_server,len=34
[112203] CW1:pdata=1883,len=6
[112208] OK
[112208] CrWCSum=0x590
[112215] SaveBkUpCredFile 
[112215] CW2:pdata=mqtt_server,len=34
[112216] CW2:pdata=1883,len=6
[112221] OK
[112222] h:Rst
```

#### 6.2. Save => Exit Config Portal and run normally

```
Start RP2040_ESP8266Shield on RASPBERRY_PI_PICO
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
DoubleResetDetector_Generic v1.7.2
Start Blynk_ESP8266AT_WM
[120835] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubleResetDetected
Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0xd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
[121384] LoadCfgFile 
[121388] OK
[121389] CCSum=0x1fed,RCSum=0x1fed
[121392] LoadCredFile 
[121393] OK
[121393] ChkCrR: Buffer allocated, Sz=35
[121393] ChkCrR:pdata=mqtt_server,len=34
[121393] ChkCrR:pdata=1883,len=6
[121394] CrCCsum=0x590,CrRCsum=0x590
[121394] Buffer freed
[121398] LoadCredFile 
[121398] OK
[121398] CrR:pdata=mqtt_server,len=34
[121398] CrR:pdata=1883,len=6
[121398] CrCCsum=0x590,CrRCsum=0x590
[121399] Valid Stored Dynamic Data
[121399] ======= Start Stored Config Data =======
[121399] Hdr=SHD_ESP8266,SSID=HueNet1,PW=password
[121399] SSID1=HueNet2,PW1=password
[121399] Svr=account.duckdns.org,Prt=8080,Tok=token
[121400] i=0,id=mqtt,data=mqtt_server
[121400] i=1,id=mqpt,data=1883
[121400] Check if isForcedCP
[121404] LoadCPFile 
[121404] OK
[121404] bg: noConfigPortal = true
[121405] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on RASPBERRY_PI_PICO

[121405] ConMultiWifi
[121405] con2WF:SSID=HueNet1,PW=password
[121405] Remaining retry_time=3
[121405] Con2:HueNet1
[127972] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
[128510] Mac=68:c6:3a:a6:f0:f1
[135496] IP=192.168.2.76

[135513] WOK
[135513] WOK, lastConnectedIndex=0
[135513] con2WF:OK
[135514] IP=192.168.2.76

[135531] b:WOK.TryB
[145798] Ready (ping: 19ms).
[145983] b:WBOK
Stop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
B
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
BBBB
```

---
---

### 7. RP2040_ESP8266Shield on MBED RASPBERRY_PI_PICO with ESP8266-AT shield

The following is the sample terminal output when running example [RP2040_ESP8266Shield](examples/RP2040_ESP8266Shield) on MBED RASPBERRY_PI_PICO with ESP8266-AT shield, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) without Blynk/WiFiManager features.


```
Start RP2040_ESP8266Shield on MBED RASPBERRY_PI_PICO
Blynk_Esp8266AT_WM v1.3.1
ESP_AT_Lib v1.2.0
Start Blynk no WM with BlynkServer = account.duckdns.org and Token = token
[1173] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on MBED RASPBERRY_PI_PICO

[1173] Con2:HueNet1
[7507] AT version:1.7.4.0(May 11 2020 19:13:04)
SDK version:3.0.4(9532ceb)
compile time:May 27 2020 10:12:17
Bin version(Wroom 02):1.7.4
OK
[14050] IP = +CIPSTA:ip:"192.168.2.76"
+CIPSTA:gateway:"192.168.2.1"
+CIPSTA:netmask:"255.255.255.0"
[14051] WOK
[24152] Ready (ping: 19ms).
BBBBB
```

---
---

### Debug

Debug is enabled by default on Serial. To disable, add at the beginning of sketch

```cpp
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT                   Serial

// Debug level, 0-3
#define BLYNK_WM_DEBUG                0

#define USE_NEW_WEBSERVER_VERSION     true  //false
#define _ESP_AT_LOGLEVEL_             0

/* Comment this out to disable prints and save space */
#define DRD_GENERIC_DEBUG         true

/* Comment this out to disable prints and save space */
#define ESP_AT_DEBUG_OUTPUT Serial

#define ESP_AT_DEBUG    true
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `ESP8266 AT shield` AT-command or this library version.

Sometimes, the library will only work if you update the `ESP8266 AT shield` core to the newer or older version because some function compatibility.


---
---

### Issues

Submit issues to: [Blynk_Esp8266AT_WM issues](https://github.com/khoih-prog/Blynk_Esp8266AT_WM/issues)

---
---

## TO DO

1. Same features for more boards using ESP8266 AT-command WiFi shields.
2. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) to use with Blynk/WiFiManager features.
3. Enable scan of WiFi networks for selection in Configuration Portal. Check [PR for v1.3.0 - Enable scan of WiFi networks #10](https://github.com/khoih-prog/WiFiManager_NINA_Lite/pull/10).

---

## DONE

 1. Permit EEPROM size and location configurable to avoid conflict with others.
 2. More flexible to configure reconnection timeout.
 3. For fresh config data, don't need to wait for connecting timeout before entering config portal.
 4. If the config data not entered completely (SSID, password, Server and Blynk token), entering config portal
 5. Add configurable Config Portal IP, SSID and Password
 6. Add configurable Static IP, GW, Subnet Mask and 2 DNS Servers' IP Addresses.
 7. Add support to **nRF52, SAMD21/SAMD51, STM32F/L/H/G/WB/MP1, SAM-DUE**
 8. Add support to **ESP32-AT** shields.
 9. Add MultiWiFi features with auto(re)connect
10. Add DRD
11. Add Dynamic Parameters
12. Add Default Config Data
13. Fix the ***EEPROM not working*** in some STM32 boards  by using emulated or integrated EEPROM
14. Add support to all **STM32F/L/H/G/WB/MP1** boards, using emulated or integrated EEPROM
15. Add support to **Teensy** boards using Teensy core v1.51 for Config Portal
16. Add Table-of-Contents
17. Use more efficient [FlashStorage_STM32](https://github.com/khoih-prog/FlashStorage_STM32) and [FlashStorage_SAMD](https://github.com/khoih-prog/FlashStorage_SAMD) library versions.
18. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico core**](https://github.com/earlephilhower/arduino-pico) to use with or without Blynk/WiFiManager features.
19. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) to use without Blynk/WiFiManager features.

---
---

### Contributions and Thanks

1. Thanks to good work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. Without that, support to nRF52, especially ***NINA_B302_ublox, NINA_B112_ublox running as nRF52840 / nRF52832***, has never been started and finished.

<table>
  <tr>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>⭐️ tcpipchip</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/Blynk_Esp8266AT_WM/blob/master/LICENSE)

---

### Copyright

Copyright 2020- Khoi Hoang

