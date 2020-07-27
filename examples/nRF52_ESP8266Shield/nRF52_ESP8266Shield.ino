/****************************************************************************************************************************
   nRF52_ESP8266Shield.ino
   For nRF52 boards using ESP8266 WiFi Shield

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
#endif

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
  while (!Serial);
  
  Serial.println("\nStart nRF52_ESP8266Shield on " + String(BOARD_NAME));

  // initialize serial for ESP module
  EspSerial.begin(ESP8266_BAUD);
  
#if USE_BLYNK_WM
  Serial.println(F("Start Blynk_ESP8266AT_WM"));

  // Optional to change default AP IP(192.168.4.1) and channel(10)
  Blynk.setConfigPortalIP(IPAddress(192, 168, 152, 1));
  // Personalized portal_ssid and password
  Blynk.setConfigPortal(portal_ssid, portal_password);
  //Blynk.setConfigPortal("nRF52_WM", "MynRF52_PW");
  Blynk.setConfigPortalChannel(0);
  
  Blynk.begin(wifi);
#else
  Serial.print(F("Start Blynk no WM with BlynkServer = "));
  Serial.print(BlynkServer);
  Serial.print(F(" and Token = "));
  Blynk.begin(auth, wifi, ssid, pass, BlynkServer.c_str(), BLYNK_SERVER_HARDWARE_PORT);
#endif
}

#if USE_DYNAMIC_PARAMETERS
void displayCredentials(void)
{
  Serial.println("\nYour stored Credentials :");

  for (int i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
  }
}
#endif

void loop()
{
  Blynk.run();
  check_status();

#if USE_DYNAMIC_PARAMETERS
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
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
#endif  
}
