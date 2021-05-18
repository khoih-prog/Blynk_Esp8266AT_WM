/****************************************************************************************************************************
  Credentials.h for nRF52_ESP8266Shield.ino
   
  Blynk_Esp8266AT_WM is a library for the Mega, Teensy, SAM DUE and SAMD boards (https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
  to enable easy configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
  
  Based on and Modified from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_Esp8266AT_WM
  Licensed under MIT license
 *****************************************************************************************************************************/

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
