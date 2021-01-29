/****************************************************************************************************************************
  Mega_ESP8266Shield.ino
  For AVR Mega using ESP8266 WiFi Shield
  
  Blynk_Esp8266AT_WM is a library for the Mega, Teensy, SAM DUE and SAMD boards (https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
  to enable easy configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
  
  Based on and Modified from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_Esp8266AT_WM
  Licensed under MIT license
  Version: 1.2.0

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
 *****************************************************************************************************************************/
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

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT                   Serial

// Debug level, 0-3
#define BLYNK_WM_DEBUG                1

#define USE_NEW_WEBSERVER_VERSION     true  //false
#define _ESP_AT_LOGLEVEL_             0
#define _ESP_AT_LIB_LOGLEVEL_         0

/* Comment this out to disable prints and save space */
#define ESP_AT_DEBUG_OUTPUT       Serial
//#define ESP_AT_LIB_DEBUG_OUTPUT   Serial

#define ESP_AT_DEBUG              true
#define ESP_AT_LIB_DEBUG          true

/* Comment this out to disable prints and save space */
#define DRD_GENERIC_DEBUG         true 

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

#if !( defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560) )
  #error This code is intended to run only on the Arduino Mega 1280/2560 boards ! Please check your Tools->Board setting.
#endif

// For Mega, use Serial1 or Serial3
#define EspSerial Serial3

#if defined(ARDUINO_AVR_MEGA2560)
  #define BOARD_TYPE      "AVR Mega2560"
#else
  #define BOARD_TYPE      "AVR Mega"
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes)
#define EEPROM_START     0

#define USE_BLYNK_WM      true
//#define USE_BLYNK_WM      false

#if USE_BLYNK_WM
  #include <BlynkSimpleShieldEsp8266_WM.h>
#else
  #include <BlynkSimpleShieldEsp8266.h>
  
  #define USE_LOCAL_SERVER      true
  
  #if USE_LOCAL_SERVER
    char auth[] = "****";
    char BlynkServer[] = "account.duckdns.org";
    //char BlynkServer[] = "192.168.2.112";
  #else
    char auth[] = "****";
    char BlynkServer[] = "blynk-cloud.com";
  #endif
  
  #define BLYNK_SERVER_HARDWARE_PORT    8080

  // Your WiFi credentials.
  char ssid[] = "****";
  char pass[] = "****";

#endif

// SSID and PW for Config Portal
char portal_ssid[]      = "CfgPrtl-SSID";
char portal_password[]  = "CfgPrtl-PW";

// Your Mega <-> ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

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

  delay(500);

  Serial.print(F("\nStart Mega_ESP8266Shield on ")); Serial.println(BOARD_NAME);
  Serial.println(BLYNK_ESP8266AT_WM_VERSION);

  // initialize serial for ESP module
  EspSerial.begin(ESP8266_BAUD);

#if USE_BLYNK_WM
  Serial.println(F("Start Blynk_ESP8266AT_WM"));

  // Optional to change default AP IP(192.168.4.1) and channel(10)
  //Blynk.setConfigPortalIP(IPAddress(192, 168, 120, 1));
  // Personalized portal_ssid and password
  Blynk.setConfigPortal(portal_ssid, portal_password);
  //Blynk.setConfigPortal("Mega_WM", "MyMega_PW");
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

void loop()
{
  Blynk.run();
  check_status();
}
