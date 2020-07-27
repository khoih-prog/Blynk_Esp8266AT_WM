/****************************************************************************************************************************
   defines.h for STM32_ESP8266Shield.ino
   
   Blynk_Esp8266AT_WM is a library for the Mega, Teensy, SAM DUE and SAMD boards (https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
   to enable easy configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk

   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
   Licensed under MIT license
   Version: 1.0.7

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
 *****************************************************************************************************************************/

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

#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
  #if defined(ESP8266_AT_USE_STM32)
    #undef ESP8266_AT_USE_STM32
  #endif
  #define ESP8266_AT_USE_STM32      true
#else
  #error This code is intended to run on STM32F platform! Please check your Tools->Board setting.  
#endif

#if ESP8266_AT_USE_STM32
  // For STM32
  #warning EspSerial using SERIAL_PORT_HARDWARE, can be Serial or Serial1. See your board variant.h
  #define EspSerial     SERIAL_PORT_HARDWARE    //Serial1

  #if defined(STM32F0)
    #warning STM32F0 board selected
    #define BOARD_TYPE  "STM32F0"
  #elif defined(STM32F1)
    #warning STM32F1 board selected
    #define BOARD_TYPE  "STM32F1"
  #elif defined(STM32F2)
    #warning STM32F2 board selected
    #define BOARD_TYPE  "STM32F2"
  #elif defined(STM32F3)
    #warning STM32F3 board selected
    #define BOARD_TYPE  "STM32F3"
  #elif defined(STM32F4)
    #warning STM32F4 board selected
    #define BOARD_TYPE  "STM32F4"
  #elif defined(STM32F7)

    #if defined(ARDUINO_NUCLEO_F767ZI)
      #warning Nucleo-144 NUCLEO_F767ZI board selected, using HardwareSerial Serial1 @ pin D0/RX and D1/TX
      // RX TX
      HardwareSerial Serial1(D0, D1);
    #else
    
      #warning STM32F7 board selected
      #define BOARD_TYPE  "STM32F7"

    #endif
    
  #elif defined(STM32L0)
    #if defined(ARDUINO_NUCLEO_L053R8)
      #warning Nucleo-64 NUCLEO_L053R8 board selected, using HardwareSerial Serial1 @ pin D0/RX and D1/TX
      // RX TX
      HardwareSerial Serial1(D0, D1);   // (PA3, PA2);
    #else
    
      #warning STM32L0 board selected
      #define BOARD_TYPE  "STM32L0"

    #endif
    
  #elif defined(STM32L1)
    #warning STM32L1 board selected
    #define BOARD_TYPE  "STM32L1"
  #elif defined(STM32L4)
    #warning STM32L4 board selected
    #define BOARD_TYPE  "STM32L4"
  #elif defined(STM32H7)
    #warning STM32H7 board selected
    #define BOARD_TYPE  "STM32H7"
  #elif defined(STM32G0)
    #warning STM32G0 board selected
    #define BOARD_TYPE  "STM32G0"
  #elif defined(STM32G4)
    #warning STM32G4 board selected
    #define BOARD_TYPE  "STM32G4"
  #elif defined(STM32WB)
    #warning STM32WB board selected
    #define BOARD_TYPE  "STM32WB"
  #elif defined(STM32MP1)
    #warning STM32MP1 board selected
    #define BOARD_TYPE  "STM32MP1"
  #else
    #warning STM32 unknown board selected
    #define BOARD_TYPE  "STM32 Unknown"
  #endif

#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes)
#define EEPROM_START      0

#define USE_BLYNK_WM      true
//#define USE_BLYNK_WM      false

#if USE_BLYNK_WM
#include <BlynkSimpleShieldEsp8266_STM32_WM.h>
#else
#include <BlynkSimpleShieldEsp8266_STM32.h>

#define USE_LOCAL_SERVER      true

#if USE_LOCAL_SERVER
char auth[] = "****";
//String BlynkServer = "account.duckdns.org";
String BlynkServer = "192.168.2.112";
#else
char auth[] = "****";
String BlynkServer = "blynk-cloud.com";
#endif

#define BLYNK_SERVER_HARDWARE_PORT    8080

// Your WiFi credentials.
char ssid[] = "****";        // your network SSID (name)
char pass[] = "****";        // your network password

#endif

#define HOST_NAME   "STM32_ESP_AT"

// SSID and PW for Config Portal
String portal_ssid      = "CfgPrtl-SSID";
String portal_password  = "CfgPrtl-PW";

// Your SAMD <-> ESP8266 baud rate:
#define ESP8266_BAUD 115200

#endif      //defines_h
