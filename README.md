## Blynk_Esp8266AT_WM

[![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_Esp8266AT_WM.svg?)](https://www.ardu-badge.com/Blynk_Esp8266AT_WM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Blynk_Esp8266AT_WM.svg)](https://github.com/khoih-prog/Blynk_Esp8266AT_WM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Blynk_Esp8266AT_WM/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Blynk_Esp8266AT_WM.svg)](http://github.com/khoih-prog/Blynk_Esp8266AT_WM/issues)

---

New recent features:

- ***MultiWiFi*** feature for configuring/auto(re)connecting ***ESP8266-AT*** shields to the available MultiWiFi APs at runtime.
- ***DoubleDetectDetector*** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- Configurable ***Config Portal Title*** to be either BoardName or default undistinguishable names.
- Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device

### Major Releases v1.0.5

1. Add support to ***nRF52 (AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B30_ublox, NINA_B112_ublox, etc.)**. Dynamic custom parameters to be saved ***automatically in LittleFS***.
2. Add support to ***Adafruit SAMD21/SAM51 (Itsy-Bitsy M0/M4, Metro M0/M4, Grand Central M4, Feather M0/M4 Express, etc.)**. Dynamic custom parameters to be saved ***automatically in FlashStorage***.
3. Add ***MultiWiFi*** features for WiFi
4. Add ***DoubleResetDetector*** (DRD) feature.
5. Increase WPA2 SSID and PW to 63 chars. Permit special chars such as !,@,#,$,%,^,&,* into data fields.
6. Restructure examples separate Credentials / Defines / Dynamic Params / Code.
7. Drop support to Teensy boards.

### New Releases v1.0.4

1. Add support to SAM DUE
2. Reduce html and code size for faster Config Portal response. 
3. Enhance GUI.
4. Config Portal AP SSID and Password will use 4 bytes of hardware unique macAddress, only for Teensy.

### New Version v1.0.3

1. Add support to STM32 (STM32F1, F2, F3, F4, F7, etc) boards. STM32F0 boards are not supported.
2. Add clearConfigData() function.

### New Version v1.0.2

1. Add support to SAMD (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.) boards

To help you to eliminate `hardcoding` your Wifi and Blynk credentials for Mega/Teensy boards running ESP8266 AT shields, and updating/reflashing every time when you need to change them. Configuration data are saved in configurable locatioon in EEPROM.

With version `v1.0.0` or later, you now can configure:

1. `Config Portal Static IP address, Name and Password.`
2. `Static IP address, Gateway, Subnet Mask and 2 DNS Servers IP addresses.`

## Prerequisite
 1. [`Arduino IDE 1.8.12 or later` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino Core for STM32 v1.8.0 or later`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 3. [`Adafruit nRF52 v0.20.1 or later`](www.adafruit.com) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, ***NINA_B302_ublox***, etc.
 4. [`Arduino SAM DUE core 1.6.12 or later`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 5. [`Arduino SAMD core 1.8.5 or later`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards
 6. [`Adafruit SAMD core 1.5.11 or later`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.)
 7. [`ESP8266_AT_WebServer library v1.0.6 or later`](https://github.com/khoih-prog/ESP8266_AT_WebServer). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP8266_AT_WebServer.svg?)](https://www.ardu-badge.com/ESP8266_AT_WebServer)
 8. [`FlashStorage_SAMD library v1.0.0`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.) and SAMD51 boards (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)
 9. [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE
10. [`Ai-Thinker AT Firmare v1.5.4`](AT_Firmwares/At_firmware_bin1.54.zip)  for ESP8266-AT shields
11. [`Adafruit's LittleFS/InternalFS`](www.adafruit.com) for nRF52
12. [`DoubleResetDetector_Generic v1.0.2 or later`](https://github.com/khoih-prog/DoubleResetDetector_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic)


### Important Notes

1. Tested OK with for ESP8266-AT shields:
  - [`Ai-Thinker AT Firmare v1.5.4`](AT_Firmwares/At_firmware_bin1.54.zip) 
  
2. ***Don't use*** [`AT Firmare v1.7.4.0`](https://github.com/espressif/ESP8266_NONOS_SDK/tree/master/bin/at) for ESP8266-AT shields. System will hangs while connecting to Blynk. Will search and fix bugs in Blynk's BlynkESP8266_Lib later.

3. Test before using different AT-Firmware Version at your own risks. Just use any simple Blynk sketch to verify if the AT-firmware is OK.
4. Compatible AT-Firmare version will be updated.
5. Support to ESP32-AT-command shields will be added later with new library replacing Blynk's BlynkESP8266_Lib.

---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `Blynk_Esp8266AT_WM`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_Esp8266AT_WM.svg?)](https://www.ardu-badge.com/Blynk_Esp8266AT_WM) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [Blynk_Esp8266AT_WM](https://github.com/khoih-prog/Blynk_Esp8266AT_WM) page.
2. Download the latest release `Blynk_Esp8266AT_WM-master.zip`.
3. Extract the zip file to `Blynk_Esp8266AT_WM-master` directory 
4. Copy whole `Blynk_Esp8266AT_WM-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### How to use

In your code, to use WiFiManager Blynk features, replace
1. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_WM.h` for Mega boards.
2. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_nRF52_WM.h`  for nRF52 boards.
3. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_SAMD_WM.h`  for SAMD boards.
4. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_DUE_WM.h`  for SAM DUE boards.
5. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_STM32_WM.h`  for STM32 boards.

to use Blynk only, with hardcoded Credentials, replace
1. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_nRF52.h`  for nRF52 boards.
2. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_SAMD.h`  for SAMD boards.
3. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_DUE.h`  for SAMD boards.
4. `BlynkSimpleShieldEsp8266.h` with `BlynkSimpleShieldEsp8266_STM32.h`  for STM32 boards.
5. Keep the same`BlynkSimpleShieldEsp8266.h` for Mega boards

- For Mega, STM32 boards, Config Data is stored in EEPROM ( 156 bytes for Mega, 308 bytes for STM32 boards from address EEPROM_START ) to save your configuration data. EEPROM_SIZE can be specified from 512 to 4096 bytes.
- For nRF52 boards, Config Data is stored in LittleFS.
- For SAMD boards, Config Data is stored in FlashStorage using 256-byte block.
- For SAM DUE boards, Config Data is stored in DueFlashStorage.

- Include in your sketch (example for nRF52 boards)

```cpp

// Select depending on board
#define EspSerial Serial1

#endif    //ESP8266_AT_USE_NRF528XX

#include <ESP8266_Lib.h>

#define USE_BLYNK_WM      true
//#define USE_BLYNK_WM      false

#if USE_BLYNK_WM
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
```

### How to add dynamic parameters from sketch

- To add custom parameters, just modify from the example below

```
#if USE_BLYNK_WM

#define USE_DYNAMIC_PARAMETERS      true

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

```

- If you don't need to add dynamic parameters, use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS      false

```


See examples 

1. [Mega_ESP8266Shield](examples/Mega_ESP8266Shield)
2. [nRF52_ESP8266Shield](examples/nRF52_ESP8266Shield)
3. [SAMD_ESP8266Shield](examples/SAMD_ESP8266Shield)
4. [SAM_DUE_ESP8266Shield](examples/SAM_DUE_ESP8266Shield)
5. [STM32_ESP8266Shield](examples/STM32_ESP8266Shield)


```
// Force some params in Blynk, only valid for library version 1.0.0 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

```

Then replace `Blynk.begin(...)` with :

1. `Blynk.begin(wifi);`

in your code. Keep `Blynk.run()` intact.

That's it.

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

### How to use default Credentials and have them pre-loaded onto Config Portal

See this example and modify as necessary

1. To load [Default Credentials](examples/nRF52_ESP8266Shield/Credentials.h)
```
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

2. To use system default to load "blank" when there is no valid Credentials
```
bool LOAD_DEFAULT_CONFIG_DATA = false;
```

3. Example of [Default Credentials](examples/nRF52_ESP8266Shield/Credentials.h)

```cpp
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
  int  blynk_port;
  char blynk_token    [36];
  char board_name     [24];
  int  checkSum;
} Blynk_WF_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      true

#if TO_LOAD_DEFAULT_CONFIG_DATA

bool LOAD_DEFAULT_CONFIG_DATA = true;

Blynk_WF_Configuration defaultConfig =
{
  //char header[16], dummy, not used
  "nRF52_ESP_AT",
  // WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  // WiFi_Credentials.wifi_ssid and WiFi_Credentials.wifi_pw
  "SSID1",  "password1",
  "SSID2",  "password2",
  // Blynk_Creds : blynk_server and blynk_token
  "account.ddns.net",     "token",
  //int  blynk_port;
  8080,
  //char board_name     [24];
  "nRF52-ESP_AT",
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

```

## Example [nRF52_ESP8266Shield](examples/nRF52_ESP8266Shield)

Please take a look at other examples, as well.

1. File [nRF52_ESP8266Shield.ino](examples/nRF52_ESP8266Shield/nRF52_ESP8266Shield.ino)

```
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
  
  Serial.println("\nStart nRF52_ESP8266Shield on " + String(BOARD_TYPE));

  // initialize serial for ESP module
  EspSerial.begin(ESP8266_BAUD);
  
#if USE_BLYNK_WM
  Serial.println(F("Start Blynk_ESP8266AT_WM"));

  // Optional to change default AP IP(192.168.4.1) and channel(10)
  Blynk.setConfigPortalIP(IPAddress(192, 168, 120, 1));
  // Personalized portal_ssid and password
  Blynk.setConfigPortal(portal_ssid, portal_password);
  //Blynk.setConfigPortal("nRF52_WM", "MynRF52_PW");
  Blynk.setConfigPortalChannel(0);
  
  Blynk.begin(wifi);
#else
  SSerial.print(F("Start Blynk no WM with BlynkServer = "));
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
```

2. File [defines.h](examples/nRF52_ESP8266Shield/defines.h)

```cpp
#ifndef defines_h
#define defines_h

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

// Uncomment to use ESP32-AT commands
//#define USE_ESP32_AT      true

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

#include <ESP8266_Lib.h>

#define USE_BLYNK_WM      true
//#define USE_BLYNK_WM      false

#if USE_BLYNK_WM
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

3. File [Credentials.h](examples/nRF52_ESP8266Shield/Credentials.h)

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
  int  blynk_port;
  char blynk_token    [36];
  char board_name     [24];
  int  checkSum;
} Blynk_WF_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      true

#if TO_LOAD_DEFAULT_CONFIG_DATA

bool LOAD_DEFAULT_CONFIG_DATA = true;

Blynk_WF_Configuration defaultConfig =
{
  //char header[16], dummy, not used
  "nRF52_ESP_AT",
  // WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  // WiFi_Credentials.wifi_ssid and WiFi_Credentials.wifi_pw
  "SSID1",  "password1",
  "SSID2",  "password2",
  // Blynk_Creds : blynk_server and blynk_token
  "account.ddns.net",     "token",
  //int  blynk_port;
  8080,
  //char board_name     [24];
  "nRF52-ESP_AT",
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

4. File [dynamicParams.h](examples/nRF52_ESP8266Shield/dynamicParams.h)

```cpp
#ifndef dynamicParams_h
#define dynamicParams_h

#if USE_BLYNK_WM

#define USE_DYNAMIC_PARAMETERS      true

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
---
The following is the sample terminal output when running example [nRF52_ESP8266Shield](examples/nRF52_ESP8266Shield)

1. No Config Data or DRD  => Config Portal

```
Start nRF52_ESP8266Shield on NRF52840_ITSYBITSY_EXPRESS
Start Blynk_ESP8266AT_WM
[30412] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK
LittleFS Flag read = 0xd0d01234
Flag read = 0xd0d01234
doubleResetDetected
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
[32077] DRD. Run ConfigPortal
[32078] ======= Start Default Config Data =======
[32078] Hdr=nRF52_ESP_AT,SSID=SSID1,PW=password1
[32078] SSID1=SSID2,PW1=password2
[32078] Svr=account.ddns.net,Prt=8080,Tok=token
[32078] BName=nRF52-ESP_AT
[32080] LoadCredFile 
[32080] OK
[32080] CrCCsum=0x6d5,CrRCsum=0x6d5
[32081] Load valid Stored Dynamic Data
[32082] LoadCredFile 
[32082] OK
[32082] CrCCsum=0x6d5,CrRCsum=0x6d5
[32082] LoadCfgFile 
[32083] OK
[32083] ======= Start Stored Config Data =======
[32083] Hdr=SHD_ESP8266,SSID=HueNet1,PW=****
[32083] SSID1=HueNet1,PW1=****
[32083] Svr=account.duckdns.org,Prt=8080,Tok=****
[32083] BName=nRF52-ESP_AT
[32084] CCSum=0x23f4,RCSum=0x23f4
[32084] Hdr=SHD_ESP8266,SSID=HueNet1,PW=****
[32084] SSID1=HueNet1,PW1=****
[32084] Svr=account.duckdns.org,Prt=8080,Tok=****
[32084] BName=nRF52-ESP_AT
[32085] b:DRD or Nodat.Stay
[ESP_AT] Use ES8266-AT Command
[36532] stConf:SSID=CfgPrtl-SSID,PW=CfgPrtl-PW,IP=192.168.120.1
[36532] SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
[36532] IP=192.168.120.1,CH=5
F
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883

```

2. Config Data Ready => Run


```
Start nRF52_ESP8266Shield on NRF52840_ITSYBITSY_EXPRESS
Start Blynk_ESP8266AT_WM
[7896] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubleResetDetected
Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0xd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
[8558] ======= Start Default Config Data =======
[8558] Hdr=nRF52_ESP_AT,SSID=SSID1,PW=password1
[8558] SSID1=SSID2,PW1=password2
[8559] Svr=account.ddns.net,Prt=8080,Tok=token
[8559] BName=nRF52-ESP_AT
[8561] LoadCredFile 
[8561] OK
[8562] CrCCsum=0x6d5,CrRCsum=0x6d5
[8562] Load valid Stored Dynamic Data
[8564] LoadCredFile 
[8564] OK
[8564] CrCCsum=0x6d5,CrRCsum=0x6d5
[8564] LoadCfgFile 
[8565] OK
[8566] ======= Start Stored Config Data =======
[8566] Hdr=SHD_Eqs
[8566] Svr=account.duckdns.org,Prt=8080,Tok=****
[8566] BName=nRF52-ESP_AT
[8567] CCSum=0x23f4,RCSum=0x23f4
[8567] Hdr=SHD_ESP8266,SSID=HueNet1,PW=****
[8567] SSID1=HueNet1,PW1=****
[8567] Svr=account.duckdns.org,Prt=8080,Tok=****
[8567] BName=nRF52-ESP_AT
[8567] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on Arduino

[8568] ConMultiWifi
[8568] con2WF:SSID=HueNet1,PW=****
[8568] Con2:HueNet1
[15139] AT version:1.1.0.0(May 11 2016 18:09:56)
SDK version:1.5.4(baaeaebb)
Ai-Thinker Technology Co. Ltd.
Jun 13 2016 11:29:20
OK
[15678] Mac=68:c6:3a:a4:6a:15
[22694] IP=192.168.2.89

[22710] WOK
[22711] con2WF:OK
[22711] IP=192.168.2.89

[22728] b:WOK.TryB
[32890] Ready (ping: 12ms).
[33119] b:WBOK
Stop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
B
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
BBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBB

```

This `Blynk.begin()` is not a blocking call, so you can use it for critical functions requiring in loop(). 
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

#### Debug
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

## Troubleshooting
If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `ESP8266 AT shield` AT-command or this library version.

Sometimes, the library will only work if you update the `ESP8266 AT shield` core to the newer or older version because some function compatibility.

---

### Major Releases v1.0.5

1. Add support to ***nRF52 (AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B30_ublox, NINA_B112_ublox, etc.)**. Dynamic custom parameters to be saved ***automatically in LittleFS***.
2. Add support to ***Adafruit SAMD21/SAM51 (Itsy-Bitsy M0/M4, Metro M0/M4, Grand Central M4, Feather M0/M4 Express, etc.)**. Dynamic custom parameters to be saved ***automatically in FlashStorage***.
3. Add ***MultiWiFi*** features for WiFi
4. Add ***DoubleResetDetector*** (DRD) feature.
5. Increase WPA2 SSID and PW to 63 chars. Permit special chars such as !,@,#,$,%,^,&,* into data fields.
6. Restructure examples separate Credentials / Defines / Dynamic Params / Code.
7. Drop support to Teensy boards.

### New Releases v1.0.4

1. Add support to SAM DUE
2. Reduce html and code size for faster Config Portal response. 
3. Enhance GUI.
4. Config Portal AP SSID and Password will use 4 bytes of hardware unique macAddress, only for Teensy.

### New Version v1.0.3

1. Add support to STM32 (STM32F1, F2, F3, F4, F7, etc) boards
2. Add clearConfigData() function.

### New Release v1.0.2

1. Add support to SAMD (DUE, ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.) boards

### Release v1.0.1

1. Add ESP8266_AT_WebServer dependency for autoinstall via Library Manager
2. Add prerequisite to README.md
3. Add checksum, fix bug

### Release v1.0.0

***Features***

1. This release of very-easy-to-use will help you to eliminate hardcoding your Wifi and Blynk credentials for Mega/Teensy boards running ESP8266 AT shields, and updating/reflashing every time when you need to change them.
2. Configuration data are stored in configurable location in EEPROM.
3. When WiFi and/or Blynk connection is lost, the WM will try auto-reconnect.
4. `Config Portal Static IP address, Name and Password.`
5. `Static IP address, Gateway, Subnet Mask.`

---

## TO DO

1. Same features for more boards ESP8266 AT-command WiFi shields.
2. To fix the ***EEPROM not working*** in some STM32 boards
3. Add support to ESP32-AT shields.

## DONE

 1. Permit EEPROM size and location configurable to avoid conflict with others.
 2. More flexible to configure reconnection timeout.
 3. For fresh config data, don't need to wait for connecting timeout before entering config portal.
 4. If the config data not entered completely (SSID, password, Server and Blynk token), entering config portal
 5. Add configurable Config Portal IP, SSID and Password
 6. Add configurable Static IP, GW, Subnet Mask and 2 DNS Servers' IP Addresses.

---

### Contributions and thanks

1. Thanks to good work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. Without that, support to nRF52, especially ***U-Box B302, B112 running as nRF52840 / nRF52832***, has never been started and finished.

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

## Copyright

Copyright 2020- Khoi Hoang

