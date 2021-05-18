/****************************************************************************************************************************
  defines.h for RP2040_ESP8266Shield.ino

  Blynk_Esp8266AT_WM is a library for the Mega, Teensy, SAM DUE and SAMD boards (https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
  to enable easy configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
  
  Based on and Modified from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_Esp8266AT_WM
  Licensed under MIT license
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

#if ( defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || defined(ARDUINO_GENERIC_RP2040) )
  #if defined(ESP8266_AT_USE_RP2040)
    #undef ESP8266_AT_USE_RP2040
  #endif
  #define ESP8266_AT_USE_RP2040      true
#else
  #error This code is intended to run only on the RP2040-based boards ! Please check your Tools->Board setting.
#endif

#if (ESP8266_AT_USE_RP2040)

  #warning RASPBERRY_PI_PICO board selected
  
  #if defined(ARDUINO_ARCH_MBED)

    #if defined(BOARD_NAME)
      #undef BOARD_NAME
    #endif

    #if defined(ARDUINO_RASPBERRY_PI_PICO) 
      #define BOARD_TYPE      "MBED RASPBERRY_PI_PICO"
    #elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
      #define BOARD_TYPE      "MBED ADAFRUIT_FEATHER_RP2040"
    #elif defined(ARDUINO_GENERIC_RP2040)
      #define BOARD_TYPE      "MBED GENERIC_RP2040"
    #else
      #define BOARD_TYPE      "MBED Unknown RP2040"
    #endif
  #else  
    #define BOARD_TYPE  "RASPBERRY_PI_PICO"
  #endif
  
  #define EspSerial       Serial1  

  #define EspSerial Serial1

#endif    //ESP8266_AT_USE_RP2040

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

//#define USE_BLYNK_WM      true
#define USE_BLYNK_WM      false

#if USE_BLYNK_WM
  #if defined(ARDUINO_ARCH_MBED)
    #error ARDUINO_ARCH_MBED is not supported yet because of LittleFS or EEPROM not ready. Select USE_BLYNK_WM = false.
  #endif

  #define USE_DYNAMIC_PARAMETERS                    true
  
  #include <BlynkSimpleShieldEsp8266_RP2040_WM.h>
#else
  #include <BlynkSimpleShieldEsp8266_RP2040.h>
  
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

#define HOST_NAME   "RP2040_ESP_AT"

// SSID and PW for Config Portal
String portal_ssid      = "CfgPrtl-SSID";
String portal_password  = "CfgPrtl-PW";

// Your RP2040 <-> ESP8266 baud rate:
#define ESP8266_BAUD 115200

#endif      //defines_h
