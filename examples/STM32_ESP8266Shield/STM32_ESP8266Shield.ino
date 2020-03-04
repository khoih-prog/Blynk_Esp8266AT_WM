/****************************************************************************************************************************
 * STM32_ESP8266Shield.ino
 * For STM32 using ESP8266 WiFi Shield
 *
 * Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/Blynk_Esp8266AT_WM
 * Licensed under MIT license
 * Version: 1.0.3
 *
 * Original Blynk Library author:
 * @file       BlynkSimpleShieldEsp8266.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jun 2015
 * @brief
 *
 * Version Modified By   Date        Comments
 * ------- -----------  ----------   -----------
 *  1.0.0   K Hoang      16/02/2020  Initial coding
 *  1.0.1   K Hoang      17/02/2019  Add checksum, fix bug
 *  1.0.2   K Hoang      22/02/2019  Add support to SAMD boards
 *  1.0.3   K Hoang      03/03/2019  Add support to STM32 boards, except STM32F0
 *****************************************************************************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) )
  #if defined(ESP8266_AT_USE_STM32)
    #undef ESP8266_AT_USE_STM32
  #endif
  #define ESP8266_AT_USE_STM32      true
#endif

#if ( defined(ESP8266) || defined(ESP32) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560) || defined(CORE_TEENSY) || !(ESP8266_AT_USE_STM32) )
//#error This code is intended to run on STM32 platform! Please check your Tools->Board setting.
#endif

#if ESP8266_AT_USE_STM32
  // For STM32, you have to declare and enable coreresponding Serial Port somewhere else before using it
  #define EspSerial Serial1
 
  #if defined(STM32F0)
    #define BOARD_TYPE  "STM32F0"
    #error Board STM32F0 not supported
  #elif defined(STM32F1)
    #define BOARD_TYPE  "STM32F1"
  #elif defined(STM32F2)
    #define BOARD_TYPE  "STM32F2"
  #elif defined(STM32F3)
    #define BOARD_TYPE  "STM32F3"
  #elif defined(STM32F4)
    #define BOARD_TYPE  "STM32F4"
  #elif defined(STM32F7)
    #define BOARD_TYPE  "STM32F7"  
  #else
    #warning STM32 unknown board selected
    #define BOARD_TYPE  "STM32 Unknown"  
  #endif
#else
// For Mega
#define EspSerial Serial3
#define BOARD_TYPE      "AVR Mega"
#endif

#include <ESP8266_Lib.h>

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes)
#define EEPROM_START     0

#define USE_BLYNK_WM      true
//#define USE_BLYNK_WM      false

#if USE_BLYNK_WM
  #if ESP8266_AT_USE_STM32
    #include <BlynkSimpleShieldEsp8266_STM32_WM.h>
  #else
    #include <BlynkSimpleShieldEsp8266_WM.h>
  #endif
#else
  #include <BlynkSimpleShieldEsp8266_STM32.h>

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

// Your Teensy <-> ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

void heartBeatPrint(void)
{
  static int num = 1;

  if (Blynk.connected())
  {
    Serial.print("B");
  }
  else
  {
    Serial.print("F");
  }
  
  if (num == 80) 
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0) 
  {
    Serial.print(" ");
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
  delay(1000);
 
  // initialize serial for ESP module
  EspSerial.begin(ESP8266_BAUD);
  Serial.println("\nStart Blynk WiFiManager using ESP8266_AT_Shield on " + String(BOARD_TYPE));

  #if USE_BLYNK_WM
    Serial.println("Start Blynk_WM");
    Blynk.setConfigPortalIP(IPAddress(192, 168, 100, 1));
    //Blynk.setConfigPortal("Teensy4", "MyTeensy4");  
    Blynk.begin(wifi);
  #else
    Serial.println("Start Blynk");
    Blynk.begin(auth, wifi, ssid, pass, BlynkServer.c_str(), BLYNK_SERVER_HARDWARE_PORT);
  #endif
}

void loop()
{
  Blynk.run();
  check_status();
}
