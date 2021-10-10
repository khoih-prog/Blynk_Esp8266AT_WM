/****************************************************************************************************************************
  BlynkDetectDevice.h
  For ESP8266 AT-command shields

  Blynk_Esp8266AT_WM is a library for the Mega, Teensy, SAM DUE and SAMD boards (https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
  to enable easy configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk

  Based on and Modified from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
  Licensed under MIT license
  Blynk_Esp8266AT_WM is a library for the Mega, Teensy, SAM DUE and SAMD boards (https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
  to enable easy configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk

  Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
  Licensed under MIT license

  Original Blynk Library author:
  @file       BlynkSimpleShieldEsp8266.h
  @author     Volodymyr Shymanskyy
  @license    This project is released under the MIT License (MIT)
  @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
  @date       Jun 2015
  @brief

  Version: 1.3.1

  Version Modified By   Date        Comments
  ------- -----------  ----------   -----------
  1.0.0   K Hoang      16/02/2020  Initial coding
  1.0.1   K Hoang      17/02/2020  Add checksum, fix bug
  1.0.2   K Hoang      22/02/2020  Add support to SAMD boards
  1.0.3   K Hoang      03/03/2020  Add support to STM32 boards, except STM32F0
  1.0.4   K Hoang      13/03/2020  Add SAM DUE support. Enhance GUI.
  1.0.5   K Hoang      23/06/2020  Add Adafruit SAMD21/SAMD51 and nRF52 support, DRD, MultiWiFi features.
                                   WPA2 SSID PW to 63 chars. Permit special chars such as !,@,#,$,%,^,&,* into data fields.
  1.0.6   K Hoang      27/06/2020  Add ESP32-AT support and use ESP_AT_Lib. Enhance MultiWiFi connection logic.
  1.0.7   K Hoang      27/07/2020  Add support to all STM32F/L/H/G/WB/MP1 and Seeeduino SAMD21/SAMD51 boards.
  1.1.0   K Hoang      15/01/2021  Restore support to Teensy to be used only with Teensy core v1.51.
  1.1.1   K Hoang      24/01/2021  Add support to Teensy 3.x, to be used only with Teensy core v1.51.
  1.2.0   K Hoang      28/01/2021  Fix bug. Use more efficient FlashStorage_STM32 and FlashStorage_SAMD.
  1.3.0   K Hoang      17/05/2021  Add support to RP2040-based boards such as RASPBERRY_PI_PICO
  1.3.1   K Hoang      09/10/2021  Update `platform.ini` and `library.json` 
 *****************************************************************************************************************************/

#ifndef BlynkDetectDevice_h
#define BlynkDetectDevice_h

// General defines

#define BLYNK_NEWLINE "\r\n"

#define BLYNK_CONCAT(a, b) a ## b
#define BLYNK_CONCAT2(a, b) BLYNK_CONCAT(a, b)

#define BLYNK_STRINGIFY(x) #x
#define BLYNK_TOSTRING(x) BLYNK_STRINGIFY(x)

#define BLYNK_COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#define BLYNK_ATTR_PACKED __attribute__ ((__packed__))
#define BLYNK_NORETURN __attribute__ ((noreturn))
#define BLYNK_UNUSED __attribute__((__unused__))
#define BLYNK_DEPRECATED __attribute__ ((deprecated))
#define BLYNK_CONSTRUCTOR __attribute__((constructor))

// Causes problems on some platforms
#define BLYNK_FORCE_INLINE inline //__attribute__((always_inline))

#ifndef BLYNK_INFO_CPU

/******************************************
   ATmega
*/

#if   defined(__AVR_ATmega168__)
#define BLYNK_INFO_CPU      "ATmega168"
#elif defined(__AVR_ATmega328P__)
#define BLYNK_INFO_CPU      "ATmega328P"
#elif defined(__AVR_ATmega1280__)
#define BLYNK_INFO_CPU      "ATmega1280"
#elif defined(__AVR_ATmega1284__)
#define BLYNK_INFO_CPU      "ATmega1284"
#elif defined(__AVR_ATmega2560__)
#define BLYNK_INFO_CPU      "ATmega2560"
#elif defined(__AVR_ATmega32U4__)
#define BLYNK_INFO_CPU      "ATmega32U4"
#elif defined(__SAM3X8E__)
#define BLYNK_INFO_CPU      "AT91SAM3X8E"

/******************************************
   ATtiny
*/

#elif defined(__AVR_ATtiny25__)
#define BLYNK_INFO_CPU      "ATtiny25"
#elif defined(__AVR_ATtiny45__)
#define BLYNK_INFO_CPU      "ATtiny45"
#elif defined(__AVR_ATtiny85__)
#define BLYNK_INFO_CPU      "ATtiny85"
#elif defined(__AVR_ATtiny24__)
#define BLYNK_INFO_CPU      "ATtiny24"
#elif defined(__AVR_ATtiny44__)
#define BLYNK_INFO_CPU      "ATtiny44"
#elif defined(__AVR_ATtiny84__)
#define BLYNK_INFO_CPU      "ATtiny84"
#elif defined(__AVR_ATtiny2313__)
#define BLYNK_INFO_CPU      "ATtiny2313"
#elif defined(__AVR_ATtiny4313__)
#define BLYNK_INFO_CPU      "ATtiny4313"
#endif
#endif

#ifndef BLYNK_INFO_DEVICE

#if   defined(ENERGIA)

#define BLYNK_NO_YIELD
#define BLYNK_USE_128_VPINS
#define BLYNK_USE_INTERNAL_DTOSTRF

#if   defined(ENERGIA_ARCH_MSP430)
#define BLYNK_INFO_DEVICE  "LaunchPad MSP430"
#define BLYNK_INFO_CPU     "MSP430"
#define BLYNK_NO_FLOAT
#elif defined(ENERGIA_ARCH_MSP432)
#define BLYNK_INFO_DEVICE  "LaunchPad MSP432"
#define BLYNK_INFO_CPU     "MSP432"
#elif defined(ENERGIA_ARCH_TIVAC)
#define BLYNK_INFO_DEVICE  "LaunchPad"

#elif defined(ENERGIA_ARCH_CC3200EMT) || defined(ENERGIA_ARCH_CC3200)
#define BLYNK_INFO_CONNECTION  "CC3200"
#define BLYNK_SEND_CHUNK 64
#define BLYNK_BUFFERS_SIZE 1024

#if   defined(ENERGIA_CC3200_LAUNCHXL) //TODO: This is a bug in Energia IDE
#define BLYNK_INFO_DEVICE  "CC3200 LaunchXL"
#elif defined(ENERGIA_RedBearLab_CC3200)
#define BLYNK_INFO_DEVICE  "RBL CC3200"
#elif defined(ENERGIA_RedBearLab_WiFiMini)
#define BLYNK_INFO_DEVICE  "RBL WiFi Mini"
#elif defined(ENERGIA_RedBearLab_WiFiMicro)
#define BLYNK_INFO_DEVICE  "RBL WiFi Micro"
#endif
#elif defined(ENERGIA_ARCH_CC3220EMT) || defined(ENERGIA_ARCH_CC3220)
#define BLYNK_INFO_CONNECTION  "CC3220"
#define BLYNK_SEND_CHUNK 64
#define BLYNK_BUFFERS_SIZE 1024

#define BLYNK_INFO_DEVICE  "CC3220"
#define BLYNK_INFO_CPU     "CC3220"
#endif

#if !defined(BLYNK_INFO_DEVICE)
#define BLYNK_INFO_DEVICE  "Energia"
#endif

#elif defined(LINUX)

#define BLYNK_INFO_DEVICE  "Linux"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 4096

#elif defined(SPARK) || defined(PARTICLE)

#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024

#if PLATFORM_ID==0
#define BLYNK_INFO_DEVICE  "Particle Core"
#undef BLYNK_BUFFERS_SIZE // Use default on Core
#elif PLATFORM_ID==6
#define BLYNK_INFO_DEVICE  "Particle Photon"
#elif PLATFORM_ID==8
#define BLYNK_INFO_DEVICE  "Particle P1"
#elif PLATFORM_ID==9
#define BLYNK_INFO_DEVICE  "Particle Ethernet"
#elif PLATFORM_ID==10
#define BLYNK_INFO_DEVICE  "Particle Electron"
#elif PLATFORM_ID==31
#define BLYNK_INFO_DEVICE  "Particle RPi"
#elif PLATFORM_ID==82
#define BLYNK_INFO_DEVICE  "Digistump Oak"
#elif PLATFORM_ID==88
#define BLYNK_INFO_DEVICE  "RedBear Duo"
#elif PLATFORM_ID==103
#define BLYNK_INFO_DEVICE  "Bluz"
#else
#if defined(BLYNK_DEBUG_ALL)
#warning "Cannot detect board type"
#endif
#define BLYNK_INFO_DEVICE  "Particle"
#endif

#elif defined(__MBED__)

#define BLYNK_INFO_DEVICE  "MBED"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 512
#define noInterrupts() __disable_irq()
#define interrupts()   __enable_irq()

#elif defined(ARDUINO) && defined(MPIDE)
#define BLYNK_NO_YIELD

#if   defined(_BOARD_UNO_)
#define BLYNK_INFO_DEVICE  "chipKIT Uno32"
#else
#define BLYNK_INFO_DEVICE  "chipKIT"
#endif

#elif defined(ARDUINO) && defined(ARDUINO_AMEBA)
#if defined(BOARD_RTL8710)
#define BLYNK_INFO_DEVICE  "RTL8710"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#elif defined(BOARD_RTL8711AM)
#define BLYNK_INFO_DEVICE  "RTL8711AM"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#elif defined(BOARD_RTL8195A)
#define BLYNK_INFO_DEVICE  "RTL8195A"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#else
#define BLYNK_INFO_DEVICE  "Ameba"
#endif

#elif defined(ARDUINO) && defined(TEENSYDUINO)

// KH
#if defined(__IMXRT1062__)
#define BLYNK_INFO_DEVICE  "Teensy 4.1/4.0"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 2048
#elif   defined(__MK66FX1M0__)
#define BLYNK_INFO_DEVICE  "Teensy 3.6"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#elif defined(__MK64FX512__)
#define BLYNK_INFO_DEVICE  "Teensy 3.5"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#elif defined(__MK20DX256__)
#define BLYNK_INFO_DEVICE  "Teensy 3.2/3.1"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#elif   defined(__MK20DX128__)
#define BLYNK_INFO_DEVICE  "Teensy 3.0"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#elif   defined(__MKL26Z64__)
#define BLYNK_INFO_DEVICE  "Teensy LC"
#define BLYNK_BUFFERS_SIZE 512
#elif   defined(ARDUINO_ARCH_AVR)
#define BLYNK_INFO_DEVICE  "Teensy 2.0"
#else
#define BLYNK_INFO_DEVICE  "Teensy"
#endif

#elif defined(ARDUINO)

#if defined(ARDUINO_ARCH_SAMD) || defined(ESP32) || defined(ESP8266)
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#endif

/* Arduino AVR */
#if   defined(ARDUINO_AVR_NANO)
#define BLYNK_INFO_DEVICE  "Arduino Nano"
#elif defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_DUEMILANOVE)
#define BLYNK_INFO_DEVICE  "Arduino Uno"
#elif defined(ARDUINO_AVR_YUN)
#define BLYNK_INFO_DEVICE  "Arduino Yun"
#elif defined(ARDUINO_AVR_MINI)
#define BLYNK_INFO_DEVICE  "Arduino Mini"
#elif defined(ARDUINO_AVR_ETHERNET)
#define BLYNK_INFO_DEVICE  "Arduino Ethernet"
#elif defined(ARDUINO_AVR_FIO)
#define BLYNK_INFO_DEVICE  "Arduino Fio"
#elif defined(ARDUINO_AVR_BT)
#define BLYNK_INFO_DEVICE  "Arduino BT"
#elif defined(ARDUINO_AVR_PRO)
#define BLYNK_INFO_DEVICE  "Arduino Pro"
#elif defined(ARDUINO_AVR_NG)
#define BLYNK_INFO_DEVICE  "Arduino NG"
#elif defined(ARDUINO_AVR_GEMMA)
#define BLYNK_INFO_DEVICE  "Arduino Gemma"
#elif defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560)
#define BLYNK_INFO_DEVICE  "Arduino Mega"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#elif defined(ARDUINO_AVR_ADK)
#define BLYNK_INFO_DEVICE  "Arduino Mega ADK"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#elif defined(ARDUINO_AVR_LEONARDO)
#define BLYNK_INFO_DEVICE  "Arduino Leonardo"
#elif defined(ARDUINO_AVR_MICRO)
#define BLYNK_INFO_DEVICE  "Arduino Micro"
#elif defined(ARDUINO_AVR_ESPLORA)
#define BLYNK_INFO_DEVICE  "Arduino Esplora"
#elif defined(ARDUINO_AVR_LILYPAD)
#define BLYNK_INFO_DEVICE  "Lilypad"
#elif defined(ARDUINO_AVR_LILYPAD_USB)
#define BLYNK_INFO_DEVICE  "Lilypad USB"
#elif defined(ARDUINO_AVR_ROBOT_MOTOR)
#define BLYNK_INFO_DEVICE  "Robot Motor"
#elif defined(ARDUINO_AVR_ROBOT_CONTROL)
#define BLYNK_INFO_DEVICE  "Robot Control"

/* Arduino megaAVR */
#elif defined(ARDUINO_AVR_UNO_WIFI_REV2)
#define BLYNK_INFO_DEVICE  "Arduino UNO WiFi Rev2"

/* Arduino SAM */
#elif defined(ARDUINO_SAM_DUE)
#define BLYNK_INFO_DEVICE  "Arduino Due"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024

/* Arduino SAMD */
// KH
////////////////////////////////////
#elif    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )

#define BLYNK_USE_128_VPINS

#if defined(BLYNK_BUFFERS_SIZE)
  #undef BLYNK_BUFFERS_SIZE
#endif
#define BLYNK_BUFFERS_SIZE 4096

#if ( defined(ARDUINO_SAMD_ZERO) && !defined(SEEED_XIAO_M0) && !defined(SEEEDUINO_ZERO) )
  #define BLYNK_INFO_DEVICE  "Arduino Zero"
  #elif defined(ARDUINO_SAMD_MKR1000)
  #define BLYNK_INFO_DEVICE  "MKR1000"
  #elif defined(ARDUINO_SAMD_MKRZERO)
  #define BLYNK_INFO_DEVICE  "MKRZERO"
  #elif defined(ARDUINO_SAMD_MKRNB1500)
  #define BLYNK_INFO_DEVICE  "MKR NB 1500"
  #elif defined(ARDUINO_SAMD_MKRGSM1400)
  #define BLYNK_INFO_DEVICE  "MKR GSM 1400"
  #elif defined(ARDUINO_SAMD_MKRWAN1300)
  #define BLYNK_INFO_DEVICE  "MKR WAN 1300"
  #elif defined(ARDUINO_SAMD_MKRFox1200)
  #define BLYNK_INFO_DEVICE  "MKR FOX 1200"
  #elif defined(ARDUINO_SAMD_MKRWIFI1010)
  #define BLYNK_INFO_DEVICE  "MKR WiFi 1010"
  #elif defined(ARDUINO_SAMD_MKRVIDOR4000)
  #define BLYNK_INFO_DEVICE  "MKR Vidor 4000"
  //KH
  #elif defined(ARDUINO_SAMD_NANO_33_IOT)
  #define BLYNK_INFO_DEVICE  "NANO_33_IOT"
  #elif defined(ARDUINO_SAMD_MKRWAN1310)
  #define BLYNK_INFO_DEVICE  "MKR WAN 1310"
  #elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
  #define BLYNK_INFO_DEVICE  "ADAFRUIT CP EXPRESS"
  #elif defined(ADAFRUIT_FEATHER_M0_EXPRESS)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_FEATHER_M0_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M0_EXPRESS)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_METRO_M0_EXPRESS"
  #elif defined(ADAFRUIT_CIRCUITPLAYGROUND_M0)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_CIRCUITPLAYGROUND_M0"
  #elif defined(ADAFRUIT_GEMMA_M0)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_GEMMA_M0"
  #elif defined(ADAFRUIT_TRINKET_M0)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_TRINKET_M0"
  #elif defined(ADAFRUIT_ITSYBITSY_M0)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_ITSYBITSY_M0"
  #elif defined(ARDUINO_SAMD_HALLOWING_M0)
  #define BLYNK_INFO_DEVICE      "ARDUINO_SAMD_HALLOWING_M0"
  #elif defined(ADAFRUIT_METRO_M4_EXPRESS)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_METRO_M4_EXPRESS"
  #elif defined(ADAFRUIT_GRAND_CENTRAL_M4)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_GRAND_CENTRAL_M4"
  #elif defined(ADAFRUIT_FEATHER_M4_EXPRESS)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_FEATHER_M4_EXPRESS"
  #elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_ITSYBITSY_M4_EXPRESS"
  #elif defined(ADAFRUIT_TRELLIS_M4_EXPRESS)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_TRELLIS_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYPORTAL)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_PYPORTAL"
  #elif defined(ADAFRUIT_PYPORTAL_M4_TITANO)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_PYPORTAL_M4_TITANO"
  #elif defined(ADAFRUIT_PYBADGE_M4_EXPRESS)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_PYBADGE_M4_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_METRO_M4_AIRLIFT_LITE"
  #elif defined(ADAFRUIT_PYGAMER_M4_EXPRESS)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_PYGAMER_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYBADGE_AIRLIFT_M4)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_PYBADGE_AIRLIFT_M4"
  #elif defined(ADAFRUIT_MONSTER_M4SK_EXPRESS)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_MONSTER_M4SK_EXPRESS"
  #elif defined(ADAFRUIT_HALLOWING_M4_EXPRESS)
  #define BLYNK_INFO_DEVICE      "ADAFRUIT_HALLOWING_M4_EXPRESS"
  #elif defined(SEEED_WIO_TERMINAL)
  #define BLYNK_INFO_DEVICE      "SAMD SEEED_WIO_TERMINAL"
  #elif defined(SEEED_FEMTO_M0)
  #define BLYNK_INFO_DEVICE      "SAMD SEEED_FEMTO_M0"
  #elif defined(SEEED_XIAO_M0)
  #define BLYNK_INFO_DEVICE      "SAMD SEEED_XIAO_M0"
  #elif defined(Wio_Lite_MG126)
  #define BLYNK_INFO_DEVICE      "SAMD SEEED Wio_Lite_MG126"
  #elif defined(WIO_GPS_BOARD)
  #define BLYNK_INFO_DEVICE      "SAMD SEEED WIO_GPS_BOARD"
  #elif defined(SEEEDUINO_ZERO)
  #define BLYNK_INFO_DEVICE      "SAMD SEEEDUINO_ZERO"
  #elif defined(SEEEDUINO_LORAWAN)
  #define BLYNK_INFO_DEVICE      "SAMD SEEEDUINO_LORAWAN"
  #elif defined(SEEED_GROVE_UI_WIRELESS)
  #define BLYNK_INFO_DEVICE      "SAMD SEEED_GROVE_UI_WIRELESS"
  #elif defined(__SAMD21E18A__)
  #define BLYNK_INFO_DEVICE      "SAMD21E18A"
  #elif defined(__SAMD21G18A__)
  #define BLYNK_INFO_DEVICE      "SAMD21G18A"
  #elif defined(__SAMD51G19A__)
  #define BLYNK_INFO_DEVICE      "SAMD51G19A"
  #elif defined(__SAMD51J19A__)
  #define BLYNK_INFO_DEVICE      "SAMD51J19A"
  #elif defined(__SAMD51J20A__)
  #define BLYNK_INFO_DEVICE      "SAMD51J20A"
  #elif defined(__SAM3X8E__)
  #define BLYNK_INFO_DEVICE      "SAM3X8E"
  #elif defined(__CPU_ARC__)
  #define BLYNK_INFO_DEVICE      "CPU_ARC"
  #elif defined(__SAMD51__)
  #define BLYNK_INFO_DEVICE      "SAMD51"
#endif
///////////////////////////////////////

/* Intel */
#elif defined(ARDUINO_GALILEO)
#define BLYNK_INFO_DEVICE  "Galileo"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 4096
#elif defined(ARDUINO_GALILEOGEN2)
#define BLYNK_INFO_DEVICE  "Galileo Gen2"
#define BLYNK_BUFFERS_SIZE 4096
#define BLYNK_USE_128_VPINS
#elif defined(ARDUINO_EDISON)
#define BLYNK_INFO_DEVICE  "Edison"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 4096
#elif defined(ARDUINO_ARCH_ARC32)
#define BLYNK_INFO_DEVICE  "Arduino 101"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024

/* Konekt */
#elif defined(ARDUINO_DASH)
#define BLYNK_INFO_DEVICE  "Dash"
#elif defined(ARDUINO_DASHPRO)
#define BLYNK_INFO_DEVICE  "Dash Pro"

/* Red Bear Lab */
#elif defined(ARDUINO_RedBear_Duo)
#define BLYNK_INFO_DEVICE  "RedBear Duo"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#elif defined(ARDUINO_BLEND)
#define BLYNK_INFO_DEVICE  "Blend"
#elif defined(ARDUINO_BLEND_MICRO_8MHZ) || defined(ARDUINO_BLEND_MICRO_16MHZ)
#define BLYNK_INFO_DEVICE  "Blend Micro"
#elif defined(ARDUINO_RBL_nRF51822)
#define BLYNK_INFO_DEVICE  "BLE Nano"

/* ESP8266 */
#elif defined(ARDUINO_ESP8266_NODEMCU)
#define BLYNK_INFO_DEVICE  "NodeMCU"
#elif defined(ARDUINO_ARCH_ESP8266)
#define BLYNK_INFO_DEVICE  "ESP8266"

/* ESP32 */
#elif defined(ARDUINO_ARCH_ESP32)
#define BLYNK_INFO_DEVICE  "ESP32"

// KH, Arduino_Core_STM32
/////////////////////////
#elif defined(STM32F0)
  #define BLYNK_INFO_DEVICE  "STM32F0"
  #define BLYNK_NO_YIELD
#elif defined(STM32F1)
  #define BLYNK_INFO_DEVICE  "STM32F1"
  #define BLYNK_NO_YIELD
#elif defined(STM32F2)
  #define BLYNK_INFO_DEVICE  "STM32F2"
  #define BLYNK_NO_YIELD
#elif defined(STM32F3)
  #define BLYNK_INFO_DEVICE  "STM32F3"
  #define BLYNK_NO_YIELD
#elif defined(STM32F4)

  #if defined(ARDUINO_NUCLEO_F429ZI)
    #define BLYNK_INFO_DEVICE  "STM32 NUCLEO_F429ZI"
  #elif defined(ARDUINO_NUCLEO_F401RE)
    #define BLYNK_INFO_DEVICE  "STM32 NUCLEO_F401RE"
  #elif defined(ARDUINO_NUCLEO_F411RE)
    #define BLYNK_INFO_DEVICE  "STM32 NUCLEO_F411RE"
  #elif defined(ARDUINO_NUCLEO_F446RE)
    #define BLYNK_INFO_DEVICE  "STM32 NUCLEO_F446RE"
  #elif defined(ARDUINO_DISCO_F407VG)
    #define BLYNK_INFO_DEVICE  "STM32 DISCO_F407VG"   
  #elif defined(ARDUINO_DISCO_F413ZH)
    #define BLYNK_INFO_DEVICE  "STM32 DISCO_F413ZH"  
  #elif defined(ARDUINO_BLACK_F407VE)
    #define BLYNK_INFO_DEVICE  "STM32 BLACK_F407VE"   
  #elif defined(ARDUINO_BLACK_F407VG)
    #define BLYNK_INFO_DEVICE  "STM32 BLACK_F407VG"
  #elif defined(ARDUINO_BLACK_F407ZE)
    #define BLYNK_INFO_DEVICE  "STM32 BLACK_F407ZE"
  #elif defined(ARDUINO_BLACK_F407ZG)
    #define BLYNK_INFO_DEVICE  "STM32 BLACK_F407ZG"
  #elif defined(ARDUINO_BLUE_F407VE_Mini)
    #define BLYNK_INFO_DEVICE  "STM32 BLUE_F407VE_Mini"   
  #elif defined(ARDUINO_DIYMORE_F407VGT)
    #define BLYNK_INFO_DEVICE  "STM32 DIYMORE_F407VGT"  
  #elif defined(ARDUINO_FK407M1)
    #define BLYNK_INFO_DEVICE  "STM32F407VET FK407M1"  
  #elif defined(ARDUINO_BLACKPILL_F401CC)
    #define BLYNK_INFO_DEVICE  "STM32 BLACKPILL_F401CC"
  #elif defined(ARDUINO_BLACKPILL_F411CE)
    #define BLYNK_INFO_DEVICE  "STM32 BLACKPILL_F411CE"
  #elif defined(ARDUINO_CoreBoard_F401RC)
    #define BLYNK_INFO_DEVICE  "STM32 CoreBoard_F401RC"
  #elif defined(ARDUINO_FEATHER_F405)
    #define BLYNK_INFO_DEVICE  "STM32 Adafruit_FEATHER_F405"   
  #elif defined(ARDUINO_THUNDERPACK_F411)
    #define BLYNK_INFO_DEVICE  "STM32 THUNDERPACK_F411"  
  #elif defined(ARDUINO_GENERIC_F446RE)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F446RE"
  #elif defined(ARDUINO_GENERIC_F446RC)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F446RC"
  #elif defined(ARDUINO_GENERIC_F423RH)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F423RH"
  #elif defined(ARDUINO_GENERIC_F423CH)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F423CH"
  #elif defined(ARDUINO_GENERIC_F417VG)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F417VG"   
  #elif defined(ARDUINO_GENERIC_F417VE)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F417VE"  
  #elif defined(ARDUINO_GENERIC_F415RG)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F415RG"  
  #elif defined(ARDUINO_GENERIC_F413RH)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F413RH"
  #elif defined(ARDUINO_GENERIC_F413RG)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F413RG"
  #elif defined(ARDUINO_GENERIC_F413CH)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F413CH"
  #elif defined(ARDUINO_GENERIC_F413CG)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F413CG"   
  #elif defined(ARDUINO_GENERIC_F412RG)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F412RG"  
  #elif defined(ARDUINO_GENERIC_F412RE)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F412RE"
  #elif defined(ARDUINO_GENERIC_F412CG)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F412CG"
  #elif defined(ARDUINO_GENERIC_F412CE)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F412CE"
  #elif defined(ARDUINO_GENERIC_F411RE)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F411RE"
  #elif defined(ARDUINO_GENERIC_F411RC)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F411RC"   
  #elif defined(ARDUINO_GENERIC_F411CE)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F411CE"  
  #elif defined(ARDUINO_GENERIC_F411CC)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F411CC" 
  #elif defined(ARDUINO_GENERIC_F410RB)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F410RB"
  #elif defined(ARDUINO_GENERIC_F410R8)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F410R8"
  #elif defined(ARDUINO_GENERIC_F410CB)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F410CB"
  #elif defined(ARDUINO_GENERIC_F410C8)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F410C8"   
  #elif defined(ARDUINO_GENERIC_F407VG)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F407VG"  
  #elif defined(ARDUINO_GENERIC_F407VE)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F407VE"
  #elif defined(ARDUINO_GENERIC_F405RG)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F405RG"
  #elif defined(ARDUINO_GENERIC_F401RE)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F401RE"
  #elif defined(ARDUINO_GENERIC_F401RD)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F401RD"
  #elif defined(ARDUINO_GENERIC_F401RC)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F401RC"   
  #elif defined(ARDUINO_GENERIC_F401RB)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F401RB"  
  #elif defined(ARDUINO_GENERIC_F401CE)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F401CE"
  #elif defined(ARDUINO_GENERIC_F401CD)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F401CD"
  #elif defined(ARDUINO_GENERIC_F401CC)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F401CC"
  #elif defined(ARDUINO_GENERIC_F401CB)
    #define BLYNK_INFO_DEVICE  "STM32 GENERIC_F401CB"  
  #elif defined(ARDUINO_ARMED_V1)
    #define BLYNK_INFO_DEVICE  "STM32 ARMED_V1"   
  #elif defined(ARDUINO_RUMBA32_F446VE)
    #define BLYNK_INFO_DEVICE  "STM32 RUMBA32_F446VE"  
  #elif defined(ARDUINO_ST3DP001_EVAL)
    #define BLYNK_INFO_DEVICE  "STM32 ST3DP001_EVAL"   
  #elif defined(ARDUINO_PRNTR_F407_V1)
    #define BLYNK_INFO_DEVICE  "STM32 PRNTR_F407_V1"   
  #elif defined(ARDUINO_PRNTR_V2)
    #define BLYNK_INFO_DEVICE  "STM32 PRNTR_V2"  
  #elif defined(ARDUINO_VAKE403)
    #define BLYNK_INFO_DEVICE  "STM32 VAKE403"
  #elif defined(ARDUINO_FYSETC_S6)
    #define BLYNK_INFO_DEVICE  "STM32 FYSETC_S6"   
  #elif defined(ARDUINO_PYBSTICK26_LITE)
    #define BLYNK_INFO_DEVICE  "STM32 PYBSTICK26_LITE"  
  #elif defined(ARDUINO_PYBSTICK26_STD)
    #define BLYNK_INFO_DEVICE  "STM32 PYBSTICK26_STD"
  #elif defined(ARDUINO_PYBSTICK26_PRO)
    #define BLYNK_INFO_DEVICE  "STM32 PYBSTICK26_PRO"        
  #else  
    #define BLYNK_INFO_DEVICE  "STM32F4"    
  #endif

  #define BLYNK_USE_128_VPINS
  #define BLYNK_BUFFERS_SIZE 1024
  #define BLYNK_NO_YIELD
  
#elif defined(STM32F7)

  #if defined(ARDUINO_NUCLEO_F767ZI)
    #define BLYNK_INFO_DEVICE  "STM32 NUCLEO_F767ZI"
  #elif defined(ARDUINO_NUCLEO_F746ZG)
    #define BLYNK_INFO_DEVICE  "STM32 NUCLEO_F746ZG"
  #elif defined(ARDUINO_NUCLEO_F756ZG)
    #define BLYNK_INFO_DEVICE  "STM32 NUCLEO_F756ZG"
  #elif defined(ARDUINO_NUCLEO_F743ZI)
    #define BLYNK_INFO_DEVICE  "STM32 NUCLEO_F743ZI"
  #elif defined(ARDUINO_NUCLEO_F743ZI2)
    #define BLYNK_INFO_DEVICE  "STM32 NUCLEO_F743ZI2"   
  #elif defined(ARDUINO_DISCO_F746NG)
    #define BLYNK_INFO_DEVICE  "STM32 DISCO_F746NG"  
  #elif defined(ARDUINO_REMRAM_V1)
    #define BLYNK_INFO_DEVICE  "STM32 REMRAM_V1"
  #else  
    #define BLYNK_INFO_DEVICE  "STM32F7"    
  #endif
  
  #define BLYNK_USE_128_VPINS
  #define BLYNK_BUFFERS_SIZE 4096
  #define BLYNK_NO_YIELD

#elif defined(STM32L0)

  #if defined(ARDUINO_NUCLEO_L053R8)
    #define BLYNK_INFO_DEVICE  "STM32 NUCLEO_L053R8"
  #elif defined(ARDUINO_NUCLEO_L073RZ)
    #define BLYNK_INFO_DEVICE  "STM32 NUCLEO_L073RZ"  
  #elif defined(ARDUINO_NUCLEO_L031K6)
    #define BLYNK_INFO_DEVICE  "STM32 NUCLEO_L031K6"  
  #elif defined(ARDUINO_DISCO_L072CZ_LRWAN1)
    #define BLYNK_INFO_DEVICE  "STM32 DISCO_L072CZ_LRWAN1"  
  #elif defined(ARDUINO_RHF76_052)
    #define BLYNK_INFO_DEVICE  "STM32 RHF76_052"  
  #elif defined(ARDUINO_THUNDERPACK_L072)
    #define BLYNK_INFO_DEVICE  "STM32 THUNDERPACK_L072"    
  #else  
    #define BLYNK_INFO_DEVICE  "STM32L0"
  #endif 
    
  #define BLYNK_USE_128_VPINS
  #define BLYNK_BUFFERS_SIZE 1024
  #define BLYNK_NO_YIELD
  
#elif defined(STM32L1)

    #define BLYNK_INFO_DEVICE  "STM32L1"
    
  #define BLYNK_USE_128_VPINS
  #define BLYNK_BUFFERS_SIZE 1024
  #define BLYNK_NO_YIELD
  
#elif defined(STM32L4)

    #define BLYNK_INFO_DEVICE  "STM32L4"
    
  #define BLYNK_USE_128_VPINS
  #define BLYNK_BUFFERS_SIZE 1024
  #define BLYNK_NO_YIELD
#elif defined(STM32H7)

    #define BLYNK_INFO_DEVICE  "STM32H7"
  #define BLYNK_USE_128_VPINS
  #define BLYNK_BUFFERS_SIZE 1024
  #define BLYNK_NO_YIELD
  
#elif defined(STM32G0)

    #define BLYNK_INFO_DEVICE  "STM32G0"
    #define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#define BLYNK_NO_YIELD
#elif defined(STM32G4)

    #define BLYNK_INFO_DEVICE  "STM32G4"
    
  #define BLYNK_USE_128_VPINS
  #define BLYNK_BUFFERS_SIZE 1024
  #define BLYNK_NO_YIELD
#elif defined(STM32WB)

    #define BLYNK_INFO_DEVICE  "STM32WB"
    
  #define BLYNK_USE_128_VPINS
  #define BLYNK_BUFFERS_SIZE 1024
  #define BLYNK_NO_YIELD
  
#elif defined(STM32MP1)

    #define BLYNK_INFO_DEVICE  "STM32MP1"
    
  #define BLYNK_USE_128_VPINS
  #define BLYNK_BUFFERS_SIZE 1024
  #define BLYNK_NO_YIELD



////////////////////////////

/* STM32 */
#elif defined(ARDUINO_ARCH_STM32F1)
#define BLYNK_INFO_DEVICE  "STM32F1"
#define BLYNK_NO_YIELD
#elif defined(ARDUINO_ARCH_STM32F3)
#define BLYNK_INFO_DEVICE  "STM32F3"
#define BLYNK_NO_YIELD
#elif defined(ARDUINO_ARCH_STM32F4)
#define BLYNK_INFO_DEVICE  "STM32F4"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#define BLYNK_NO_YIELD


/* Digistump */
#elif defined(ARDUINO_ESP8266_OAK)
#define BLYNK_INFO_DEVICE  "Oak"
#define BLYNK_USE_128_VPINS
#elif defined(ARDUINO_AVR_DIGISPARK)
#define BLYNK_INFO_DEVICE  "Digispark"
#define BLYNK_NO_YIELD
#elif defined(ARDUINO_AVR_DIGISPARKPRO)
#define BLYNK_INFO_DEVICE  "Digispark Pro"
#define BLYNK_NO_YIELD

/* Microduino */
#elif defined(ARDUINO_AVR_USB)
#define BLYNK_INFO_DEVICE  "CoreUSB"
#elif defined(ARDUINO_AVR_PLUS)
#define BLYNK_INFO_DEVICE  "Core+"
#elif defined(ARDUINO_AVR_RF)
#define BLYNK_INFO_DEVICE  "CoreRF"

/* Wildfire */
#elif defined(ARDUINO_WILDFIRE_V2)
#define BLYNK_INFO_DEVICE  "Wildfire V2"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#elif defined(ARDUINO_WILDFIRE_V3)
#define BLYNK_INFO_DEVICE  "Wildfire V3"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024
#elif defined(ARDUINO_WILDFIRE_V4)
#define BLYNK_INFO_DEVICE  "Wildfire V4"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024

/* Simblee */
#elif defined(__Simblee__)
#define BLYNK_INFO_DEVICE  "Simblee"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 512

/* RFduino */
#elif defined(__RFduino__)
#define BLYNK_INFO_DEVICE  "RFduino"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 512

/* Nordic nRF2 */
// KH
/////////////////////////////////////
#elif ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
      defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
      
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 4096
#warning Use nRF52 boards in BlynkDetectDevice.h

#if defined(NRF52840_FEATHER)
#define BLYNK_INFO_DEVICE      "NRF52840_FEATHER_EXPRESS"
#elif defined(NRF52832_FEATHER)
#define BLYNK_INFO_DEVICE      "NRF52832_FEATHER"
#elif defined(NRF52840_FEATHER_SENSE)
#define BLYNK_INFO_DEVICE      "NRF52840_FEATHER_SENSE"
#elif defined(NRF52840_ITSYBITSY)
#define BLYNK_INFO_DEVICE      "NRF52840_ITSYBITSY_EXPRESS"
#elif defined(NRF52840_CIRCUITPLAY)
#define BLYNK_INFO_DEVICE      "NRF52840_CIRCUIT_PLAYGROUND"
#elif defined(NRF52840_CLUE)
#define BLYNK_INFO_DEVICE      "NRF52840_CLUE"
#elif defined(NRF52840_METRO)
#define BLYNK_INFO_DEVICE      "NRF52840_METRO_EXPRESS"
#elif defined(NRF52840_PCA10056)
#define BLYNK_INFO_DEVICE      "NORDIC_NRF52840DK"
#elif defined(NINA_B302_ublox)
#define BLYNK_INFO_DEVICE      "NINA_B302_ublox"
#elif defined(NINA_B112_ublox)
#define BLYNK_INFO_DEVICE      "NINA_B112_ublox"
#elif defined(PARTICLE_XENON)
#define BLYNK_INFO_DEVICE      "PARTICLE_XENON"
#elif defined(MDBT50Q_RX)
#define BLYNK_INFO_DEVICE      "RAYTAC_MDBT50Q_RX"
#elif defined(ARDUINO_NRF52_ADAFRUIT)
#define BLYNK_INFO_DEVICE      "ARDUINO_NRF52_ADAFRUIT"
#else
#define BLYNK_INFO_DEVICE      "nRF52 Unknown"
#endif      
      
/////////////////////////////////////

/* Nordic NRF5x */
#elif defined(ARDUINO_ARCH_NRF5)
#define BLYNK_INFO_DEVICE  "nRF5"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 512

#else
#if defined(BLYNK_DEBUG_ALL)
#warning "Cannot detect board type"
#endif
#define BLYNK_INFO_DEVICE  "Arduino"
#endif

#elif defined(TI_CC3220)
#define BLYNK_INFO_DEVICE  "TI CC3220"
#define BLYNK_USE_128_VPINS
#define BLYNK_BUFFERS_SIZE 1024

#define BLYNK_USE_INTERNAL_DTOSTRF

#else

#define BLYNK_INFO_DEVICE  "Custom platform"

#endif

#if !defined(BLYNK_MAX_READBYTES) && defined(BLYNK_BUFFERS_SIZE)
#define BLYNK_MAX_READBYTES  BLYNK_BUFFERS_SIZE
#endif

#if !defined(BLYNK_MAX_SENDBYTES) && defined(BLYNK_BUFFERS_SIZE)
#define BLYNK_MAX_SENDBYTES  BLYNK_BUFFERS_SIZE
#endif

// Print diagnostics

#if defined(BLYNK_DEBUG_ALL)
#if defined(BLYNK_INFO_DEVICE)
#pragma message ("BLYNK_INFO_DEVICE=" BLYNK_TOSTRING(BLYNK_INFO_DEVICE))
#endif

#if defined(BLYNK_INFO_CPU)
#pragma message ("BLYNK_INFO_CPU="    BLYNK_TOSTRING(BLYNK_INFO_CPU))
#endif

#if defined(BLYNK_BUFFERS_SIZE)
#pragma message ("BLYNK_BUFFERS_SIZE=" BLYNK_TOSTRING(BLYNK_BUFFERS_SIZE))
#endif
#endif

#endif

#endif
