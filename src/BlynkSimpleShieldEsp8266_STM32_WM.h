/****************************************************************************************************************************
  BlynkSimpleShieldEsp8266_STM32_WM.h
  For STM32 boards using ESP8266 WiFi Shields

  Blynk_Esp8266AT_WM is a library for the Mega, Teensy, SAM DUE and SAMD boards (https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
  to enable easy configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk

  Based on and Modified from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_Esp8266AT_WM
  Licensed under MIT license

  Original Blynk Library author:
  @file       BlynkSimpleShieldEsp8266.h
  @author     Volodymyr Shymanskyy
  @license    This project is released under the MIT License (MIT)
  @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
  @date       Jun 2015
  @brief

  Version: 1.1.0

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
 *****************************************************************************************************************************/

#ifndef BlynkSimpleShieldEsp8266_STM32_WM_h
#define BlynkSimpleShieldEsp8266_STM32_WM_h

#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
  #if defined(BLYNK_ESP8266_AT_USE_STM32)
    #undef BLYNK_ESP8266_AT_USE_STM32
  #endif
  #define BLYNK_ESP8266_AT_USE_STM32      true
#endif

#if ( defined(ESP8266) || defined(ESP32) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560) || defined(CORE_TEENSY) || !(BLYNK_ESP8266_AT_USE_STM32) )
  #error This code is intended to run on STM32 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_ESP8266AT_WM_VERSION    "Blynk_Esp8266AT_WM v1.1.0"

#ifndef BLYNK_INFO_CONNECTION
  #define BLYNK_INFO_CONNECTION  "ESP8266"
#endif

#ifndef BLYNK_ESP8266_MUX
  #define BLYNK_ESP8266_MUX  1
#endif

#define BLYNK_SEND_ATOMIC
#define BLYNK_SEND_CHUNK 40

#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <utility/BlynkFifo.h>

// From v1.0.6 to support ESP32-AT
#if USE_ESP_AT_LIB
  #include <ESP_AT_Lib.h>
#else
  #include <ESP8266_Lib.h>
#endif

#include <ESP8266_AT_WebServer.h>
#include <EEPROM.h>

#include <IWatchdog.h>

#define SIMPLE_SHIELD_ESP8266_DEBUG       0

#ifndef BLYNK_WM_DEBUG
  #define BLYNK_WM_DEBUG                    0
#endif

///////// NEW for DRD /////////////
// These defines must be put before #include <DoubleResetDetector_Generic.h>
// to select where to store DoubleResetDetector_Generic's variable.
// Otherwise, library will use default EEPROM storage
#define  DRD_FLAG_DATA_SIZE     4

#ifndef DOUBLERESETDETECTOR_DEBUG
#define DOUBLERESETDETECTOR_DEBUG     false
#endif

#include <DoubleResetDetector_Generic.h>      //https://github.com/khoih-prog/DoubleResetDetector_Generic

// Number of seconds after reset during which a
// subsequent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector_Generic to use
#define DRD_ADDRESS 0

DoubleResetDetector_Generic* drd;

///////// NEW for DRD /////////////

//NEW
#define MAX_ID_LEN                5
#define MAX_DISPLAY_NAME_LEN      16

typedef struct
{
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
} MenuItem;
//

#if USE_DYNAMIC_PARAMETERS
  #warning Using Dynamic Parameters
  ///NEW
  extern uint16_t NUM_MENU_ITEMS;
  extern MenuItem myMenuItems [];
  bool *menuItemUpdated = NULL;
#else
  #warning Not using Dynamic Parameters
#endif

// New in v1.0.5
#define SSID_MAX_LEN      32
//From v1.0.5, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
}  WiFi_Credentials;

#define NUM_WIFI_CREDENTIALS      2

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 2 )
////////////////

#define BLYNK_SERVER_HARDWARE_PORT    8080

#define HEADER_MAX_LEN      16
#define SERVER_MAX_LEN      32
#define TOKEN_MAX_LEN       36

typedef struct Configuration
{
  char header         [HEADER_MAX_LEN];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char blynk_server   [SERVER_MAX_LEN];
  char blynk_token    [TOKEN_MAX_LEN];
  int  checkSum;
} Blynk_WF_Configuration;

// Currently CONFIG_DATA_SIZE  =   280  = (16 + 96 * 2 + 32 + 36 + 4)
uint16_t CONFIG_DATA_SIZE = sizeof(Blynk_WF_Configuration);
///New from v1.0.5
extern bool LOAD_DEFAULT_CONFIG_DATA;
extern Blynk_WF_Configuration defaultConfig;

// -- HTML page fragments

const char ESP_AT_HTML_HEAD[]     /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>STM32_WM</title><style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style></head><div style=\"text-align:left;display:inline-block;min-width:260px;\">\
<fieldset><div><label>WiFi SSID</label><input value=\"[[id]]\"id=\"id\"><div></div></div>\
<div><label>PWD</label><input value=\"[[pw]]\"id=\"pw\"><div></div></div>\
<div><label>WiFi SSID1</label><input value=\"[[id1]]\"id=\"id1\"><div></div></div>\
<div><label>PWD1</label><input value=\"[[pw1]]\"id=\"pw1\"><div></div></div></fieldset>\
<fieldset><div><label>Server</label><input value=\"[[sv]]\"id=\"sv\"><div></div></div>\
<div><label>Token</label><input value=\"[[tk]]\"id=\"tk\"><div></div></div></fieldset>";

const char ESP_AT_FLDSET_START[]  /*PROGMEM*/ = "<fieldset>";
const char ESP_AT_FLDSET_END[]    /*PROGMEM*/ = "</fieldset>";
const char ESP_AT_HTML_PARAM[]    /*PROGMEM*/ = "<div><label>{b}</label><input value='[[{v}]]'id='{i}'><div></div></div>";
const char ESP_AT_HTML_BUTTON[]   /*PROGMEM*/ = "<button onclick=\"sv()\">Save</button></div>";

const char ESP_AT_HTML_SCRIPT[]   /*PROGMEM*/ = "<script id=\"jsbin-javascript\">\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+encodeURIComponent(val);\
request.open('GET',url,false);request.send(null);}\
function sv(){udVal('id',document.getElementById('id').value);udVal('pw',document.getElementById('pw').value);\
udVal('id1',document.getElementById('id1').value);udVal('pw1',document.getElementById('pw1').value);\
udVal('sv',document.getElementById('sv').value);udVal('tk',document.getElementById('tk').value);";

const char ESP_AT_HTML_SCRIPT_ITEM[]  /*PROGMEM*/ = "udVal('{d}',document.getElementById('{d}').value);";
const char ESP_AT_HTML_SCRIPT_END[]   /*PROGMEM*/ = "alert('Updated');}</script>";
const char ESP_AT_HTML_END[]          /*PROGMEM*/ = "</html>";
///

String IPAddressToString(IPAddress _address)
{
  String str = String(_address[0]);
  str += ".";
  str += String(_address[1]);
  str += ".";
  str += String(_address[2]);
  str += ".";
  str += String(_address[3]);
  return str;
}

class BlynkTransportShieldEsp8266
{
    static void onData(uint8_t mux_id, uint32_t len, void* ptr) {
      ((BlynkTransportShieldEsp8266*)ptr)->onData(mux_id, len);
    }

    void onData(uint8_t mux_id, uint32_t len) {
      if (mux_id != BLYNK_ESP8266_MUX) {
        return;
      }

      //KH
#if (SIMPLE_SHIELD_ESP8266_DEBUG > 1)
      BLYNK_LOG4("Got:", len, ",Free:", buffer.free());
#endif
      //

      if ( (uint32_t) buffer.free() < len)
      {
        //KH
#if (SIMPLE_SHIELD_ESP8266_DEBUG > 0)
        BLYNK_LOG4("OVF,Got:", len, ",Free:", buffer.free());
#endif

        return;
      }
      while (len) {
        if (client->getUart()->available()) {
          uint8_t b = client->getUart()->read();
          //KH
          // len got from +IPD data
          buffer.put(b);
          //
          len--;
        }
      }
      //KH
#if (SIMPLE_SHIELD_ESP8266_DEBUG > 1)
      BLYNK_LOG2(BLYNK_F("onData Buffer len"), len );
#endif
      //
    }

  public:
    BlynkTransportShieldEsp8266()
      : client(NULL)
      , status(false)
      , domain(NULL)
      , port(0)
    {}

    void setEsp8266(ESP8266* esp8266) {
      client = esp8266;
      client->setOnData(onData, this);
    }

    //TODO: IPAddress

    void begin(const char* d,  uint16_t p) {
      domain = d;
      port = p;
    }

    bool connect() {
      if (!domain || !port)
        return false;
      status = client->createTCP(BLYNK_ESP8266_MUX, domain, port);
      return status;
    }

    void disconnect() {
      status = false;
      buffer.clear();
      client->releaseTCP(BLYNK_ESP8266_MUX);
    }

    size_t read(void* buf, size_t len)
    {
      millis_time_t start = BlynkMillis();
      //KH
      //buffer.size() is number of bytes currently still in FIFO buffer
      //Check to see if all data are read or not

#if (SIMPLE_SHIELD_ESP8266_DEBUG > 1)
      BLYNK_LOG4("rd:len=", len, ",Buf=", buffer.size());
#endif

      while ((buffer.size() < len) && (BlynkMillis() - start < 1500))
      {
        // Actually call ESP8266 run/rx_empty (read and locate +IPD, know data len,
        // then call onData() to get len bytes of data to buffer => BlynkProtocol::ProcessInput()
        client->run();
      }
      //All data got in FIFO buffer, copy to destination buf and return len
      return buffer.get((uint8_t*)buf, len);
    }

    size_t write(const void* buf, size_t len) {
      if (client->send(BLYNK_ESP8266_MUX, (const uint8_t*)buf, len)) {
        return len;
      }
      return 0;
    }

    bool connected() {
      return status;
    }

    int available()
    {
      client->run();
#if (SIMPLE_SHIELD_ESP8266_DEBUG > 2)
      BLYNK_LOG2("Still:", buffer.size());
#endif
      return buffer.size();
    }

  private:
    ESP8266* client;
    bool status;

    //KH
#if BLYNK_ESP8266_AT_USE_STM32
  #if defined(STM32F0)
    // For STM32 F0
    BlynkFifo<uint8_t, 512> buffer;
    #error Board STM32F0 not supported
  #elif defined(STM32F1)
    // For STM32 F1
    BlynkFifo<uint8_t, 1024> buffer;
    #warning Board STM32F1 uses 1K FIFO buffer
  #elif defined(STM32F2)
    // For STM32 F2
    BlynkFifo<uint8_t, 1024> buffer;
    #warning Board STM32F2 uses 1K FIFO buffer
  #elif defined(STM32F3)
    // For STM32 F3
    BlynkFifo<uint8_t, 1024> buffer;
    #warning Board STM32F3 uses 1K FIFO buffer
  #elif defined(STM32F4)
    // For STM32 F4
    BlynkFifo<uint8_t, 2048> buffer;
    #warning Board STM32F4 uses 2K FIFO buffer
  #elif defined(STM32F7)
    // For STM32 F7
    BlynkFifo<uint8_t, 4096> buffer;
    #warning Board STM32F7 uses 4K FIFO buffer
  #elif defined(STM32L0)
    // For STM32 L0
    BlynkFifo<uint8_t, 1024> buffer;
    #warning Board STM32L0 uses 1K FIFO buffer
  #elif defined(STM32L1)
    // For STM32 L1
    BlynkFifo<uint8_t, 1024> buffer;
    #warning Board STM32L1 uses 1K FIFO buffer
  #elif defined(STM32L4)
    // For STM32 L4
    BlynkFifo<uint8_t, 2048> buffer;
    #warning Board STM32L4 uses 2K FIFO buffer
  #elif defined(STM32H7)
    // For STM32 H7
    BlynkFifo<uint8_t, 4096> buffer;
    #warning Board STM32H7 uses 4K FIFO buffer
  #elif defined(STM32G0)
    // For STM32 G0
    BlynkFifo<uint8_t, 1024> buffer;
    #warning Board STM32G0 uses 1K FIFO buffer
  #elif defined(STM32G4)
    // For STM32 G4
    BlynkFifo<uint8_t, 2048> buffer;
    #warning Board STM32G4 uses 2K FIFO buffer
  #elif defined(STM32WB)
    // For STM32WB
    BlynkFifo<uint8_t, 1024> buffer;
    #warning Board STM32WB uses 1K FIFO buffer
  #elif defined(STM32MP1)
    // For STM32MP1
    BlynkFifo<uint8_t, 1024> buffer;
    #warning Board STM32MP1 uses 1K FIFO buffer

  #else
    // For STM32 Unknow
    BlynkFifo<uint8_t, 512> buffer;
    #warning Board STM32 unknown uses 512bytes FIFO buffer
  #endif

#else
  // For other AVR Mega
  //BlynkFifo<uint8_t,256> buffer;
  // For MeGa 2560 or 1280
  BlynkFifo<uint8_t, 512> buffer;
  #warning Not STM32 board => uses 512bytes FIFO buffer
#endif

    const char* domain;
    uint16_t    port;
};

class BlynkWifi
  : public BlynkProtocol<BlynkTransportShieldEsp8266>
{
    typedef BlynkProtocol<BlynkTransportShieldEsp8266> Base;
  public:
    BlynkWifi(BlynkTransportShieldEsp8266& transp)
      : Base(transp)
      , wifi(NULL)
    {}

    bool WiFiInit()
    {
#if USE_ESP32_AT
      //wifi->restart();
      wifi->restore();
      wifi->kick();
      wifi->setEcho(0);
#else
      if (!wifi->restart()) 
      {
        BLYNK_LOG1(BLYNK_F("Fail2Rst"));
        return false;
      }  
      if (!wifi->kick())
      {
        BLYNK_LOG1(BLYNK_F("ESP no respond"));
        //TODO: BLYNK_LOG_TROUBLE(BLYNK_F("esp8266-not-responding"));
        return false;
      }
      
      if (!wifi->setEcho(0))
      {
        BLYNK_LOG1(BLYNK_F("FailEcho"));
        return false;
      }
#endif

      String ver = wifi->ESP8266::getVersion();
      BLYNK_LOG1(ver);

      // KH
      BlynkDelay(500);

      if (!wifi->enableMUX())
      {
        BLYNK_LOG1(BLYNK_F("FailMUX"));
        return false;
      }

      if (!wifi->setOprToStation())
      {
        BLYNK_LOG1(BLYNK_F("FailSTA"));
        return false;
      }

      return true;
    }

    bool connectWiFi(const char* ssid, const char* pass)
    {
      BLYNK_LOG2(BLYNK_F("Con2:"), ssid);

      WiFiInit();

      // In STA mode, get and store unique macAddress for later use
      if (macAddress.length() == 0)
      {
        macAddress = wifi->getStationMac();
        macAddress.replace("+CIPSTAMAC:\"", "");
        macAddress.replace("\"", "");
        BLYNK_LOG2(BLYNK_F("Mac="), macAddress);
      }

      if (wifi->joinAP(ssid, pass))
      {
        displayWiFiData();
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("FailW"));
        return false;
      }

      BLYNK_LOG1(BLYNK_F("WOK"));

      wifi_connected = true;

      return true;
    }

    void config(ESP8266&    esp8266,
                const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
      Base::begin(auth);
      wifi = &esp8266;
      this->conn.setEsp8266(wifi);
      this->conn.begin(domain, port);
    }

    void begin(const char* auth,
               ESP8266&    esp8266,
               const char* ssid,
               const char* pass,
               const char* domain = BLYNK_DEFAULT_DOMAIN,
               uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
      config(esp8266, auth, domain, port);
      BLYNK_LOG1(BLYNK_F("b:conW"));
      connectWiFi(ssid, pass);
      while (this->connect() != true) {}
    }


    void config(ESP8266& esp8266)
    {
      wifi = &esp8266;
      this->conn.setEsp8266(wifi);
      WiFiInit();
    }

    void begin(ESP8266& esp8266/*, const char *iHostname = ""*/)
    {
#define RETRY_TIMES_CONNECT_WIFI			3

#if USE_DYNAMIC_PARAMETERS
      // Enforce NUM_MENU_ITEMS <= 3
      // Due to notorious 2K buffer limitation of ESO8266-AT shield, the NUM_MENU_ITEMS is limited to max 3
      // to avoid WebServer not working due to HTML data larger than 2K can't be sent successfully
      // The items with index larger than 3 will be ignored
      if (NUM_MENU_ITEMS > 3)
        NUM_MENU_ITEMS = 3;
#endif

      config(esp8266);
      
      //// New DRD ////
      drd = new DoubleResetDetector_Generic(DRD_TIMEOUT, DRD_ADDRESS);  
      bool noConfigPortal = true;
   
      if (drd->detectDoubleReset())
      {
        BLYNK_LOG1(BLYNK_F("DRD. Run ConfigPortal"));
     
        noConfigPortal = false;
      }
      //// New DRD ////
      
#if ( BLYNK_WM_DEBUG > 2)    
      if (LOAD_DEFAULT_CONFIG_DATA) 
      {   
        BLYNK_LOG1(BLYNK_F("======= Start Default Config Data ======="));
        displayConfigData(defaultConfig);
      }
#endif
      
      hadConfigData = getConfigData();
      
      isForcedConfigPortal = isForcedCP();
      
      //// New DRD/MRD ////
      //  noConfigPortal when getConfigData() OK and no MRD/DRD'ed
      //if (getConfigData() && noConfigPortal)
      if (hadConfigData && noConfigPortal && (!isForcedConfigPortal) )
      {
        hadConfigData = true;
        
#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG1(noConfigPortal? BLYNK_F("bg: noConfigPortal = true") : BLYNK_F("bg: noConfigPortal = false"));
#endif 

        config(esp8266, Blynk8266_WF_config.blynk_token, Blynk8266_WF_config.blynk_server, BLYNK_SERVER_HARDWARE_PORT);

        if (connectMultiWiFi(RETRY_TIMES_CONNECT_WIFI))
        {
          BLYNK_LOG1(BLYNK_F("b:WOK.TryB"));

          int i = 0;
          while ( (i++ < 10) && !this->connect() )
          {
          }

          if  (connected())
          {
            BLYNK_LOG1(BLYNK_F("b:WBOK"));
          }
          else
          {
            BLYNK_LOG1(BLYNK_F("b:WOK,Bno"));
            // failed to connect to Blynk server, will start configuration mode
            startConfigurationMode();
          }
        }
        else
        {
          BLYNK_LOG1(BLYNK_F("b:FailW+B"));
          // failed to connect to Blynk server, will start configuration mode
          startConfigurationMode();
        }
      }
      else
      { 
#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG1(isForcedConfigPortal? BLYNK_F("bg: isForcedConfigPortal = true") : BLYNK_F("bg: isForcedConfigPortal = false"));
#endif
                                
        // If not persistent => clear the flag so that after reset. no more CP, even CP not entered and saved
        if (persForcedConfigPortal)
        {
          BLYNK_LOG2(BLYNK_F("bg:Stay forever in CP:"), isForcedConfigPortal ? BLYNK_F("Forced-Persistent") : (noConfigPortal ? BLYNK_F("No ConfigDat") : BLYNK_F("DRD/MRD")));
        }
        else
        {
          BLYNK_LOG2(BLYNK_F("bg:Stay forever in CP:"), isForcedConfigPortal ? BLYNK_F("Forced-non-Persistent") : (noConfigPortal ? BLYNK_F("No ConfigDat") : BLYNK_F("DRD/MRD")));
          clearForcedCP();
        }
          
        // failed to connect to Blynk server, will start configuration mode
        hadConfigData = false;
        startConfigurationMode();
      }
    }

#ifndef RETRY_TIMES_RECONNECT_WIFI
  #define RETRY_TIMES_RECONNECT_WIFI   2
#else
  // Force range of user-defined RETRY_TIMES_RECONNECT_WIFI between 2-5 times
  #if (RETRY_TIMES_RECONNECT_WIFI < 2)
    #warning RETRY_TIMES_RECONNECT_WIFI too low. Reseting to 2
    #undef RETRY_TIMES_RECONNECT_WIFI
    #define RETRY_TIMES_RECONNECT_WIFI   2
  #elif (RETRY_TIMES_RECONNECT_WIFI > 5)
    #warning RETRY_TIMES_RECONNECT_WIFI too high. Reseting to 5
    #undef RETRY_TIMES_RECONNECT_WIFI
    #define RETRY_TIMES_RECONNECT_WIFI   5
  #endif
#endif

#ifndef RESET_IF_CONFIG_TIMEOUT
  #define RESET_IF_CONFIG_TIMEOUT   true
#endif

#ifndef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
  #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET          10
#else
  // Force range of user-defined TIMES_BEFORE_RESET between 2-100
  #if (CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET < 2)
    #warning CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET too low. Reseting to 2
    #undef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
    #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET   2
  #elif (CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET > 100)
    #warning CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET too high. Resetting to 100
    #undef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
    #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET   100
  #endif
#endif

    void run()
    {
      static int retryTimes = 0;
      
      // Lost connection in running. Give chance to reconfig.
      // Check WiFi status every 2s and update status
      static unsigned long checkstatus_timeout = 0;
      #define WIFI_STATUS_CHECK_INTERVAL    2000L
      
      //// New DRD ////
      // Call the double reset detector loop method every so often,
      // so that it can recognise when the timeout expires.
      // You can also call drd.stop() when you wish to no longer
      // consider the next reset as a double reset.
      drd->loop();
      //// New DRD ////
 
      // Lost connection in running. Give chance to reconfig.
      if ( !wifi_connected || !connected() )
      {
        // If configTimeout but user hasn't connected to configWeb => try to reconnect WiFi / Blynk.
        // But if user has connected to configWeb, stay there until done, then reset hardware
        if ( configuration_mode && ( configTimeout == 0 ||  millis() < configTimeout ) )
        {
          retryTimes = 0;

          if (server)
            server->handleClient();

          return;
        }
        else
        {
#if RESET_IF_CONFIG_TIMEOUT
          // If we're here but still in configuration_mode, permit running TIMES_BEFORE_RESET times before reset hardware
          // to permit user another chance to config.
          if ( configuration_mode && (configTimeout != 0) )
          {
            if (++retryTimes <= CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET)
            {
              BLYNK_LOG2(BLYNK_F("r:Wlost&TOut.ConW+B.Retry#"), retryTimes);
            }
            else
            {
              resetFunc();  //call reset
            }
          }
#endif

          // Not in config mode, try reconnecting before forcing to config mode
          if ( !wifi_connected )
          {
            BLYNK_LOG1(BLYNK_F("r:Wlost.ReconW+B"));

            if (connectMultiWiFi(RETRY_TIMES_RECONNECT_WIFI))
            {
              BLYNK_LOG1(BLYNK_F("r:WOK.TryB"));

              if (connect())
              {
                BLYNK_LOG1(BLYNK_F("r:W+BOK"));
              }
            }
          }
          else
          {
            // Force to reconnect WiFi, then Blynk
            wifi_connected = false;  
          }

          //BLYNK_LOG1(BLYNK_F("run: Lost connection => configMode"));
          //startConfigurationMode();
        }
      }
      else if (configuration_mode)
      {
        configuration_mode = false;
        BLYNK_LOG1(BLYNK_F("r:gotW+Bback"));
      }

      if (connected())
      {
        Base::run();
      }
    }


    void setConfigPortalIP(IPAddress portalIP = IPAddress(192, 168, 4, 1))
    {
      portal_apIP = portalIP;
    }
    
    #define MIN_WIFI_CHANNEL      1
    #define MAX_WIFI_CHANNEL      11    // Channel 12, 13 is flaky, because of bad number 13 ;-)

    int setConfigPortalChannel(int channel = 1)
    {
      // If channel < MIN_WIFI_CHANNEL - 1 or channel > MAX_WIFI_CHANNEL => channel = 1
      // If channel == 0 => will use random channel from MIN_WIFI_CHANNEL to MAX_WIFI_CHANNEL
      // If (MIN_WIFI_CHANNEL <= channel <= MAX_WIFI_CHANNEL) => use it
      if ( (channel < MIN_WIFI_CHANNEL - 1) || (channel > MAX_WIFI_CHANNEL) )
        AP_channel = 1;
      else if ( (channel >= MIN_WIFI_CHANNEL - 1) && (channel <= MAX_WIFI_CHANNEL) )
        AP_channel = channel;

      return AP_channel;
    }

    void setConfigPortal(String ssid = "", String pass = "")
    {
      portal_ssid = ssid;
      portal_pass = pass;
    }

    void setSTAStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn = IPAddress(255, 255, 255, 0),
                              IPAddress dns_address_1 = IPAddress(0, 0, 0, 0),
                              IPAddress dns_address_2 = IPAddress(0, 0, 0, 0))
    {
      static_IP     = ip;
      static_GW     = gw;
      static_SN     = sn;

      // Default to local GW
      if (dns_address_1 == IPAddress(0, 0, 0, 0))
        static_DNS1   = gw;
      else
        static_DNS1   = dns_address_1;

      // Default to Google DNS (8, 8, 8, 8)
      if (dns_address_2 == IPAddress(0, 0, 0, 0))
        static_DNS2   = IPAddress(8, 8, 8, 8);
      else
        static_DNS2   = dns_address_2;
    }
    
    String getWiFiSSID(uint8_t index)
    { 
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WF_config.WiFi_Creds[index].wifi_ssid));
    }

    String getWiFiPW(uint8_t index)
    {
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WF_config.WiFi_Creds[index].wifi_pw));
    }

    String getServerName()
    {
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WF_config.blynk_server));
    }

    String getToken()
    {
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WF_config.blynk_token));
    }

    int getHWPort()
    {
      if (!hadConfigData)
        getConfigData();

      return (BLYNK_SERVER_HARDWARE_PORT);
    }

    Blynk_WF_Configuration* getFullConfigData(Blynk_WF_Configuration *configData)
    {
      if (!hadConfigData)
        getConfigData();

      // Check if NULL pointer
      if (configData)
        memcpy(configData, &Blynk8266_WF_config, sizeof(Blynk8266_WF_config));

      return (configData);
    }

    String getLocalIP()
    {
      uint16_t indexNextLine;

      ipAddress = wifi->getLocalIP();
      ipAddress.replace("+CIFSR:STAIP,\"", "");
      ipAddress.replace("\"", "");
      indexNextLine = ipAddress.indexOf("\n");
      ipAddress = ipAddress.substring(0, indexNextLine);
   
      return ipAddress;
    }

    void clearConfigData()
    {
      memset(&Blynk8266_WF_config, 0, sizeof(Blynk8266_WF_config));
      
#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
      }
#endif

      saveConfigData();
    }
        
    bool isConfigDataValid()
    {
      return hadConfigData;
    }
    
    // Forced CP => Flag = 0xBEEFBEEF. Else => No forced CP
    // Flag to be stored at (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE) 
    // to avoid corruption to current data
    //#define FORCED_CONFIG_PORTAL_FLAG_DATA              ( (uint32_t) 0xDEADBEEF)
    //#define FORCED_PERS_CONFIG_PORTAL_FLAG_DATA         ( (uint32_t) 0xBEEFDEAD)
    
    const uint32_t FORCED_CONFIG_PORTAL_FLAG_DATA       = 0xDEADBEEF;
    const uint32_t FORCED_PERS_CONFIG_PORTAL_FLAG_DATA  = 0xBEEFDEAD;
    
    #define FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE     4
    
    void resetAndEnterConfigPortal()
    {
      persForcedConfigPortal = false;
      
      setForcedCP(false);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }
    
    // This will keep CP forever, until you successfully enter CP, and Save data to clear the flag.
    void resetAndEnterConfigPortalPersistent()
    {
      persForcedConfigPortal = true;
      
      setForcedCP(true);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }

    void resetFunc()
    {
      // Initialize the IWDG with 2 seconds timeout.
      // This would cause a CPU reset if the IWDG timer
      // is not reloaded in approximately 2 seconds.
      IWatchdog.begin(2000000);
    }

  private:
    ESP8266* wifi;
    String ipAddress = "0.0.0.0";

    ESP8266_AT_WebServer* server;
    bool configuration_mode = false;

    unsigned long configTimeout;
    bool hadConfigData = false;
    
    bool isForcedConfigPortal   = false;
    bool persForcedConfigPortal = false;

    Blynk_WF_Configuration Blynk8266_WF_config;
    
    uint16_t totalDataSize = 0;

    String macAddress = "";
    bool wifi_connected = false;

    // For Config Portal, from Blynk_WM v1.0.5
    IPAddress portal_apIP = IPAddress(192, 168, 4, 1);
    int AP_channel = 10;

    String portal_ssid = "";
    String portal_pass = "";

    // For static IP, from Blynk_WM v1.0.5
    IPAddress static_IP   = IPAddress(0, 0, 0, 0);
    IPAddress static_GW   = IPAddress(0, 0, 0, 0);
    IPAddress static_SN   = IPAddress(255, 255, 255, 0);
    IPAddress static_DNS1 = IPAddress(0, 0, 0, 0);
    IPAddress static_DNS2 = IPAddress(0, 0, 0, 0);
    
    void displayConfigData(Blynk_WF_Configuration configData)
    {
      BLYNK_LOG6(BLYNK_F("Hdr="),   configData.header, BLYNK_F(",SSID="), configData.WiFi_Creds[0].wifi_ssid,
                BLYNK_F(",PW="),    configData.WiFi_Creds[0].wifi_pw);
      BLYNK_LOG4(BLYNK_F("SSID1="), configData.WiFi_Creds[1].wifi_ssid, BLYNK_F(",PW1="),  configData.WiFi_Creds[1].wifi_pw);   
      BLYNK_LOG6(BLYNK_F("Svr="),   configData.blynk_server, BLYNK_F(",Prt="), BLYNK_SERVER_HARDWARE_PORT,
                BLYNK_F(",Tok="),   configData.blynk_token);  
      
#if ( BLYNK_WM_DEBUG > 2 ) && USE_DYNAMIC_PARAMETERS
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        BLYNK_LOG6("i=", i, ",id=", myMenuItems[i].id, ",data=", myMenuItems[i].pdata);
      }      
#endif
    }

    void displayWiFiData()
    {
      BLYNK_LOG2(BLYNK_F("IP="), getLocalIP());
    }

#define BLYNK_BOARD_TYPE   "SHD_ESP8266"
#define WM_NO_CONFIG       "blank"

#ifndef EEPROM_SIZE
  #define EEPROM_SIZE     4096
#else
  #if (EEPROM_SIZE > 4096)
    #warning EEPROM_SIZE must be <= 4096. Reset to 4096
    #undef EEPROM_SIZE
    #define EEPROM_SIZE     4096
  #endif
  #if (EEPROM_SIZE < CONFIG_DATA_SIZE)
    #warning EEPROM_SIZE must be > CONFIG_DATA_SIZE. Reset to 512
    #undef EEPROM_SIZE
    #define EEPROM_SIZE     512
  #endif
#endif

#ifndef EEPROM_START
  #define EEPROM_START     0      //define 256 in DRD
  #warning EEPROM_START not defined. Set to 0
#else
  #if ( (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE) > (EEPROM_SIZE) )
    #error EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > EEPROM_SIZE. Please adjust.
  #endif
#endif

// Stating positon to store Blynk8266_WM_config
#define CONFIG_EEPROM_START    (EEPROM_START + DRD_FLAG_DATA_SIZE)

    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(Blynk8266_WF_config) - sizeof(Blynk8266_WF_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &Blynk8266_WF_config ) + index);
      }

      return checkSum;
    }
    
    //////////////////////////////////////////////
    
    void NULLTerminateConfig()
    {
      //#define HEADER_MAX_LEN      16
      //#define SERVER_MAX_LEN      32
      //#define TOKEN_MAX_LEN       36
      
      // NULL Terminating to be sure
      Blynk8266_WF_config.header[HEADER_MAX_LEN - 1] = 0;
      Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid[SSID_MAX_LEN - 1] = 0;
      Blynk8266_WF_config.WiFi_Creds[0].wifi_pw  [PASS_MAX_LEN - 1] = 0;
      Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid[SSID_MAX_LEN - 1] = 0;
      Blynk8266_WF_config.WiFi_Creds[1].wifi_pw  [PASS_MAX_LEN - 1] = 0;
      Blynk8266_WF_config.blynk_server[SERVER_MAX_LEN - 1]  = 0;
      Blynk8266_WF_config.blynk_token [TOKEN_MAX_LEN - 1]   = 0;
    }
    
    //////////////////////////////////////////////
    
#if defined(DATA_EEPROM_BASE)

    // For STM32 devices having integrated EEPROM.
    #warning "STM32 devices have integrated EEPROM. Not using buffered API."
    
    //////////////////////////////////////////////
    
    void setForcedCP(bool isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;

#if ( BLYNK_WM_DEBUG > 2)      
      BLYNK_LOG1(isPersistent ? BLYNK_F("setForcedCP Persistent") : BLYNK_F("setForcedCP non-Persistent"));
#endif
           
      EEPROM.put(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);
    }
    
    //////////////////////////////////////////////
    
    void clearForcedCP()
    {
      EEPROM.put(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, 0);
    }
    
    //////////////////////////////////////////////

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false
      EEPROM.get(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false     
      if (readForcedConfigPortalFlag == FORCED_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = false;
        return true;
      }
      else if (readForcedConfigPortalFlag == FORCED_PERS_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = true;
        return true;
      }
      else
      {       
        return false;
      }
    }
    
    //////////////////////////////////////////////

#if USE_DYNAMIC_PARAMETERS

    bool checkDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      
      #define BUFFER_LEN      128
      char readBuffer[BUFFER_LEN + 1];
      
      uint16_t offset = CONFIG_EEPROM_START + sizeof(Blynk8266_WF_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
                
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > BUFFER_LEN)
        {
          // Size too large, abort and flag false
          BLYNK_LOG1(BLYNK_F("ChkCrR: Error Small Buffer."));
          return false;
        }
      }
         
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = readBuffer;
        
        // Prepare buffer, more than enough
        memset(readBuffer, 0, sizeof(readBuffer));
        
        // Read more than necessary, but OK and easier to code
        EEPROM.get(offset, readBuffer);
        // NULL terminated
        readBuffer[myMenuItems[i].maxlen] = 0;

#if ( BLYNK_WM_DEBUG > 2) 
        BLYNK_LOG4(BLYNK_F("ChkCrR:pdata="), readBuffer, BLYNK_F(",len="), myMenuItems[i].maxlen);     
#endif
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }   
        
        offset += myMenuItems[i].maxlen;    
      }

      EEPROM.get(offset, readCheckSum);
           
      BLYNK_LOG4(BLYNK_F("ChkCrR:CrCCsum=0x"), String(checkSum, HEX), BLYNK_F(",CrRCsum=0x"), String(readCheckSum, HEX));
           
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }
    
    //////////////////////////////////////////////
    
    bool EEPROM_getDynamicData()
    {
      int readCheckSum;
      int checkSum = 0;
      uint16_t offset = CONFIG_EEPROM_START + sizeof(Blynk8266_WF_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
           
      totalDataSize = sizeof(Blynk8266_WF_config) + sizeof(readCheckSum);
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;
        
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          *_pointer = EEPROM.read(offset);
          
          checkSum += *_pointer;  
         }       
      }
      
      EEPROM.get(offset, readCheckSum);
      
      BLYNK_LOG4(BLYNK_F("CrCCsum=0x"), String(checkSum, HEX), BLYNK_F(",CrRCsum=0x"), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;
    }
    
    //////////////////////////////////////////////

    void EEPROM_putDynamicData()
    {
      int checkSum = 0;
      uint16_t offset = CONFIG_EEPROM_START + sizeof(Blynk8266_WF_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
                
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
 
#if ( BLYNK_WM_DEBUG > 2)         
        BLYNK_LOG4(BLYNK_F("pdata="), myMenuItems[i].pdata, BLYNK_F(",len="), myMenuItems[i].maxlen);
#endif                            
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          EEPROM.write(offset, *_pointer);
          
          checkSum += *_pointer;     
         }
      }
      
      EEPROM.put(offset, checkSum);
      
      BLYNK_LOG2(BLYNK_F("CrCCSum=0x"), String(checkSum, HEX));
    }
#endif    // #if USE_DYNAMIC_PARAMETERS

    

    //////////////////////////////////////////////
    
    bool EEPROM_get()
    {
      EEPROM.get(CONFIG_EEPROM_START, Blynk8266_WF_config);
      NULLTerminateConfig();
      
      return true;
    }
    
    //////////////////////////////////////////////
    
    void EEPROM_put()
    {
      EEPROM.put(CONFIG_EEPROM_START, Blynk8266_WF_config);
    }
    
    //////////////////////////////////////////////
    
#else   // #if defined(DATA_EEPROM_BASE)
    
    /**
     Most STM32 devices don't have an integrated EEPROM. To emulate a EEPROM, the STM32 Arduino core emulated
     the operation of an EEPROM with the help of the embedded flash.
     Writing to a flash is very expensive operation, since a whole flash page needs to be written, even if you only
     want to access the flash byte-wise.
     The STM32 Arduino core provides a buffered access API to the emulated EEPROM. The library has allocated the
     buffer even if you don't use the buffered API, so it's strongly suggested to use the buffered API anyhow.
     */

    #warning "STM32 devices don't have integrated EEPROM. Using buffered API."
    
    //////////////////////////////////////////////
    
    void setForcedCP(bool isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;

#if ( BLYNK_WM_DEBUG > 2)      
      BLYNK_LOG1(isPersistent ? BLYNK_F("setForcedCP Persistent") : BLYNK_F("setForcedCP non-Persistent"));
#endif
                
      // First, to copy the data from the flash to the buffer to protect previous data
      eeprom_buffer_fill();
      
      uint16_t offset = CONFIG_EEPROM_START + CONFIG_DATA_SIZE;
           
      uint8_t* _pointer = (uint8_t *) &readForcedConfigPortalFlag;
      
      for (uint16_t i = 0; i < sizeof(readForcedConfigPortalFlag); i++, _pointer++, offset++)
      {              
        eeprom_buffered_write_byte(offset, *_pointer);
      }
      
      // Save the data from the buffer to the flash
      eeprom_buffer_flush();
    }
    
    //////////////////////////////////////////////
    
    void clearForcedCP()
    {
      uint32_t readForcedConfigPortalFlag = 0;
      
      // First, to copy the data from the flash to the buffer to protect previous data
      eeprom_buffer_fill();
               
      uint16_t offset = CONFIG_EEPROM_START + CONFIG_DATA_SIZE;
           
      uint8_t* _pointer = (uint8_t *) &readForcedConfigPortalFlag;
      
      for (uint16_t i = 0; i < sizeof(readForcedConfigPortalFlag); i++, _pointer++, offset++)
      {              
        eeprom_buffered_write_byte(offset, *_pointer);
      }
      
      // Save the data from the buffer to the flash
      eeprom_buffer_flush();
    }
    
    //////////////////////////////////////////////

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false
     
      // First, to copy the data from the flash to the buffer to protect previous data
      eeprom_buffer_fill();
      
      uint16_t offset = CONFIG_EEPROM_START + CONFIG_DATA_SIZE;
                
      uint8_t* _pointer = (uint8_t *) &readForcedConfigPortalFlag;
      
      for (uint16_t i = 0; i < sizeof(readForcedConfigPortalFlag); i++, _pointer++, offset++)
      {              
        *_pointer = eeprom_buffered_read_byte(offset);
      }
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false     
      if (readForcedConfigPortalFlag == FORCED_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = false;
        return true;
      }
      else if (readForcedConfigPortalFlag == FORCED_PERS_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = true;
        return true;
      }
      else
      {       
        return false;
      }
    }
    
    //////////////////////////////////////////////

#if USE_DYNAMIC_PARAMETERS

    bool checkDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
           
      // First, to copy the data from the flash to the buffer to protect previous data
      eeprom_buffer_fill();
      
      uint16_t offset = CONFIG_EEPROM_START + sizeof(Blynk8266_WF_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
                
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {                             
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++, offset++)
        {       
          checkSum += eeprom_buffered_read_byte(offset);    
        }       
      }
      
      uint8_t* _pointer = (uint8_t *) &readCheckSum;
      
      for (uint16_t i = 0; i < sizeof(readCheckSum); i++, _pointer++, offset++)
      {                  
        *_pointer = eeprom_buffered_read_byte(offset);
      }  
                  
      BLYNK_LOG4(BLYNK_F("ChkCrR:CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
           
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }
    
    //////////////////////////////////////////////
    
    bool EEPROM_getDynamicData()
    {
      int readCheckSum;
      int checkSum = 0;
      
      // First, to copy the data from the flash to the buffer to protect previous data
      eeprom_buffer_fill();
      
      totalDataSize = sizeof(Blynk8266_WF_config) + sizeof(readCheckSum);
          
      // Using FORCED_CONFIG_PORTAL_FLAG_DATA
      uint16_t offset = CONFIG_EEPROM_START + sizeof(Blynk8266_WF_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
      uint8_t* _pointer;
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        _pointer = (uint8_t *) myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;
        
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++, _pointer++, offset++)
        {
          *_pointer = eeprom_buffered_read_byte(offset);          
          checkSum += *_pointer;  
         }       
      }
      
      _pointer = (uint8_t *) &readCheckSum;
      
      for (uint16_t i = 0; i < sizeof(readCheckSum); i++, _pointer++, offset++)
      {                  
        *_pointer = eeprom_buffered_read_byte(offset);
      }
         
      BLYNK_LOG4(BLYNK_F("CrCCSum="), String(checkSum, HEX), F(",CrRCSum="), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
     
      return true;
    }
    
    //////////////////////////////////////////////

    void EEPROM_putDynamicData()
    {    
      int checkSum = 0;
      
      // First, to copy the data from the flash to the buffer to protect previous data
      eeprom_buffer_fill();
      
      // Using FORCED_CONFIG_PORTAL_FLAG_DATA
      uint16_t offset = CONFIG_EEPROM_START + sizeof(Blynk8266_WF_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
      uint8_t* _pointer;
    
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        _pointer = (uint8_t *) myMenuItems[i].pdata;

#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG4(BLYNK_F("pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
#endif
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          eeprom_buffered_write_byte(offset, *_pointer);
          
          checkSum += *_pointer;     
         }
      }
      
      _pointer = (uint8_t *) &checkSum;
      
      for (uint16_t i = 0; i < sizeof(checkSum); i++, _pointer++, offset++)
      {              
        eeprom_buffered_write_byte(offset, *_pointer);
      }
      
      BLYNK_LOG2(BLYNK_F("CrCCSum=0x"), String(checkSum, HEX));
      
      // Save the data from the buffer to the flash
      eeprom_buffer_flush();
    }
#endif    // #if USE_DYNAMIC_PARAMETERS

    //////////////////////////////////////////////
    
    bool EEPROM_get()
    {           
      // Copy the data from the flash to the buffer
      eeprom_buffer_fill();
      
      uint16_t offset = CONFIG_EEPROM_START;
                
      uint8_t* _pointer = (uint8_t *) &Blynk8266_WF_config;
      
      for (uint16_t i = 0; i < sizeof(Blynk8266_WF_config); i++, _pointer++, offset++)
      {              
        *_pointer = eeprom_buffered_read_byte(offset);
      }
      
      NULLTerminateConfig();
      
      return true;
    }
    
    //////////////////////////////////////////////
    
    void EEPROM_put()
    {     
      // First, to copy the data from the flash to the buffer to protect previous data
      eeprom_buffer_fill();
      
      uint16_t offset = CONFIG_EEPROM_START;
           
      uint8_t* _pointer = (uint8_t *) &Blynk8266_WF_config;
      
      for (uint16_t i = 0; i < sizeof(Blynk8266_WF_config); i++, _pointer++, offset++)
      {              
        eeprom_buffered_write_byte(offset, *_pointer);
      }

      // Save the data from the buffer to the flash
      eeprom_buffer_flush();  
    }
    
#endif   // #if defined(DATA_EEPROM_BASE) 
    
    //////////////////////////////////////////////

    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      Blynk8266_WF_config.checkSum = calChecksum;
      
      BLYNK_LOG6(BLYNK_F("SaveEEPROM,Sz="), EEPROM.length(), BLYNK_F(",DataSz="), totalDataSize, BLYNK_F(",WCSum=0x"), String(calChecksum, HEX));
      
      EEPROM_put();
        
#if USE_DYNAMIC_PARAMETERS        
      EEPROM_putDynamicData();
#endif        
    }

    //////////////////////////////////////////////
    
    void loadAndSaveDefaultConfigData()
    {
      // Load Default Config Data from Sketch
      memcpy(&Blynk8266_WF_config, &defaultConfig, sizeof(Blynk8266_WF_config));
      strcpy(Blynk8266_WF_config.header, BLYNK_BOARD_TYPE);
      
      // Including config and dynamic data, and assume valid
      saveConfigData();
      
#if ( BLYNK_WM_DEBUG > 2)      
      BLYNK_LOG1(BLYNK_F("======= Start Loaded Config Data ======="));
      displayConfigData(Blynk8266_WF_config);
#endif      
    }
    
    
    //////////////////////////////////////////////
    
    bool getConfigData()
    {
      bool dynamicDataValid = true;
      int calChecksum;   
      
      hadConfigData = false; 
      
#if defined(DATA_EEPROM_BASE)      
      EEPROM.begin();
#endif
      
      // Use new LOAD_DEFAULT_CONFIG_DATA logic
      if (LOAD_DEFAULT_CONFIG_DATA)
      {     
        // Load Config Data from Sketch
        loadAndSaveDefaultConfigData();
        
        // Don't need Config Portal anymore
        return true; 
      }
      else
      {   
        // Load stored config data from EEPROM
        BLYNK_LOG2(BLYNK_F("EEPROMsz:"), EEPROM_SIZE);
        BLYNK_LOG2(BLYNK_F("EEPROM Length():"), EEPROM.length());
        
        EEPROM_get();
        
        // Verify ChkSum
        calChecksum = calcChecksum();

        BLYNK_LOG4(BLYNK_F("CCSum=0x"), String(calChecksum, HEX),
                   BLYNK_F(",RCSum=0x"), String(Blynk8266_WF_config.checkSum, HEX));
        
#if USE_DYNAMIC_PARAMETERS        
        // Load stored dynamic data from LittleFS
        dynamicDataValid = checkDynamicData();
#endif           
                      
        // If checksum = 0 => simulated EEPROM has been cleared (by uploading new FW, etc) => force to CP
        // If bad checksum = 0 => force to CP
        if ( (calChecksum != 0) && (calChecksum == Blynk8266_WF_config.checkSum) )
        {
          if (dynamicDataValid)
          {
  #if USE_DYNAMIC_PARAMETERS        
            EEPROM_getDynamicData();

            
    #if (BLYNK_WM_DEBUG > 2)
            BLYNK_LOG1(BLYNK_F("Valid Stored Dynamic Data"));
    #endif
  #endif
           
            BLYNK_LOG1(BLYNK_F("======= Start Stored Config Data ======="));
            displayConfigData(Blynk8266_WF_config);
            
            // Don't need Config Portal anymore
            return true;
          }
          else
          {
            // Invalid Stored config data => Config Portal
            BLYNK_LOG1(BLYNK_F("Invalid Stored Dynamic Data. Load default from Sketch"));
            
            // Load Default Config Data from Sketch, better than just "blank"
            loadAndSaveDefaultConfigData();
                             
            // Need Config Portal here as data can be just dummy
            // Even if you don't open CP, you're OK on next boot if your default config data is valid 
            return false;
          }
        } 
      }   
      
      if ( (strncmp(Blynk8266_WF_config.header, BLYNK_BOARD_TYPE, strlen(BLYNK_BOARD_TYPE)) != 0) ||
           (calChecksum != Blynk8266_WF_config.checkSum) || !dynamicDataValid || 
           ( (calChecksum == 0) && (Blynk8266_WF_config.checkSum == 0) ) )
      {
        // Including Credentials CSum
        BLYNK_LOG4(BLYNK_F("InitEEPROM,Sz="), EEPROM_SIZE, BLYNK_F(",DataSz="), totalDataSize);

        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&Blynk8266_WF_config, &defaultConfig, sizeof(Blynk8266_WF_config));
        }
        else
        {
          memset(&Blynk8266_WF_config, 0, sizeof(Blynk8266_WF_config));

#if USE_DYNAMIC_PARAMETERS
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
          }
#endif
              
          // doesn't have any configuration
          strcpy(Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid,       WM_NO_CONFIG);
          strcpy(Blynk8266_WF_config.WiFi_Creds[0].wifi_pw,         WM_NO_CONFIG);
          strcpy(Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid,       WM_NO_CONFIG);
          strcpy(Blynk8266_WF_config.WiFi_Creds[1].wifi_pw,         WM_NO_CONFIG);
          strcpy(Blynk8266_WF_config.blynk_server,                  WM_NO_CONFIG);
          strcpy(Blynk8266_WF_config.blynk_token,                   WM_NO_CONFIG);
          
#if USE_DYNAMIC_PARAMETERS          
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            strncpy(myMenuItems[i].pdata, WM_NO_CONFIG, myMenuItems[i].maxlen);
          }
#endif          
        }
    
        strcpy(Blynk8266_WF_config.header, BLYNK_BOARD_TYPE);
        
#if ( BLYNK_WM_DEBUG > 2) && USE_DYNAMIC_PARAMETERS
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          BLYNK_LOG4(BLYNK_F("g:myMenuItems["), i, BLYNK_F("]="), myMenuItems[i].pdata );
        }
#endif
        
        // Don't need
        Blynk8266_WF_config.checkSum = 0;

        saveConfigData();
        
        return false;  
      }
      else if ( !strncmp(Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid,   WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(Blynk8266_WF_config.WiFi_Creds[0].wifi_pw,     WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid,   WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(Blynk8266_WF_config.WiFi_Creds[1].wifi_pw,     WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(Blynk8266_WF_config.blynk_server,              WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(Blynk8266_WF_config.blynk_token,              WM_NO_CONFIG, strlen(WM_NO_CONFIG) ) )
      {
        // If SSID, PW ="nothing", stay in config mode forever until having config Data.
        return false;
      }
      else
      {
        displayConfigData(Blynk8266_WF_config);
      }

      return true;
    }
    
    //////////////////////////////////////////////

    // New connection logic for ESP32-AT from v1.0.6
    bool connectMultiWiFi(int retry_time)
    {
      int sleep_time  = 250;
      int index       = 0;
      
      // Using to force to use connectWiFi() which resets the ESP. Need  only once after the boot
      // After that, only need joinAP() for faster as resetting the ESP is not necessary
      static bool firstTimeConnect = true;
                 
      static int lastConnectedIndex = 255;

      BLYNK_LOG1(BLYNK_F("ConMultiWifi"));

      if (static_IP != IPAddress(0, 0, 0, 0))
      {
        BLYNK_LOG1(BLYNK_F("UseStatIP"));
        wifi->setStationIp(IPAddressToString(static_IP), IPAddressToString(static_GW), IPAddressToString(static_SN));
      }
    
      if (lastConnectedIndex != 255)
      {
        index = (lastConnectedIndex + 1) % NUM_WIFI_CREDENTIALS;
#if ( BLYNK_WM_DEBUG > 2)                         
        BLYNK_LOG4(BLYNK_F("Using index="), index, BLYNK_F(", lastConnectedIndex="), lastConnectedIndex);
#endif
      }
      else
      {
#if USE_ESP32_AT
        // Fix ESP32-AT multiWiFi auto(re)connection when lost
        // Need only once after reboot
        wifi->restore();
#endif
      }
      
      BLYNK_LOG4(BLYNK_F("con2WF:SSID="), Blynk8266_WF_config.WiFi_Creds[index].wifi_ssid,
                BLYNK_F(",PW="), Blynk8266_WF_config.WiFi_Creds[index].wifi_pw);
             
      while ( !wifi_connected && ( 0 < retry_time ) )
      {
#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG2(BLYNK_F("Remaining retry_time="), retry_time);
#endif

#if USE_ESP32_AT
        // ESP32-AT requires restart everytime !!!
        wifi_connected = connectWiFi(Blynk8266_WF_config.WiFi_Creds[index].wifi_ssid,
                                        Blynk8266_WF_config.WiFi_Creds[index].wifi_pw);
#else
        if (firstTimeConnect)
        {
          wifi_connected = connectWiFi(Blynk8266_WF_config.WiFi_Creds[index].wifi_ssid,
                                        Blynk8266_WF_config.WiFi_Creds[index].wifi_pw);
        }
        else
        {
          wifi_connected = wifi->joinAP(Blynk8266_WF_config.WiFi_Creds[index].wifi_ssid, 
                                        Blynk8266_WF_config.WiFi_Creds[index].wifi_pw);
        }
#endif
             
        // Need restart WiFi at beginning of each cycle 
        if (wifi_connected)
        {
          firstTimeConnect = false;
          
          lastConnectedIndex = index;     
          
#if ( BLYNK_WM_DEBUG > 2)                         
          BLYNK_LOG2(BLYNK_F("WOK, lastConnectedIndex="), lastConnectedIndex);
#endif
          
          break;
        }
        else
        {
          delay(sleep_time);
          retry_time--;
        }         
      }

#if ( BLYNK_WM_DEBUG > 2)             
      if (retry_time <= 0)
      {      
        BLYNK_LOG4(BLYNK_F("Failed using index="), index, BLYNK_F(", retry_time="), retry_time);             
      }  
#endif        

      if (wifi_connected)
      {
        BLYNK_LOG1(BLYNK_F("con2WF:OK"));
        displayWiFiData();
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("con2WF:failed"));  
        // Can't connect, so try another index next time. Faking this index is OK and lost
        lastConnectedIndex = index;  
      }

      return wifi_connected;  
    }
    
    //////////////////////////////////////////////
    
    #define MAX_HTML_SIZE       2048      // 2K
    
    // NEW
    void createHTML(String& root_html_template)
    {
      String pitem;
           
      root_html_template = String(ESP_AT_HTML_HEAD)  + ESP_AT_FLDSET_START;

#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(ESP_AT_HTML_PARAM);

        pitem.replace("{b}", myMenuItems[i].displayName);
        pitem.replace("{v}", myMenuItems[i].id);
        pitem.replace("{i}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
#endif
      
      root_html_template += String(ESP_AT_FLDSET_END) + ESP_AT_HTML_BUTTON + ESP_AT_HTML_SCRIPT;     

#if USE_DYNAMIC_PARAMETERS           
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(ESP_AT_HTML_SCRIPT_ITEM);
        
        pitem.replace("{d}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
#endif
      
      root_html_template += String(ESP_AT_HTML_SCRIPT_END) + ESP_AT_HTML_END;
            
      return;     
    }
    
    //////////////////////////////////////////////

    void handleRequest()
    {
      if (server)
      {
        String key    = server->arg("key");
        String value  = server->arg("value");

        static int number_items_Updated = 0;

        if (key == "" && value == "")
        {
          String result = String("");
          createHTML(result);

#if ( BLYNK_WM_DEBUG > 2)
          BLYNK_LOG1(BLYNK_F("h:repl"));
#endif

          // Reset configTimeout to stay here until finished.
          configTimeout = 0;
          
          result.replace("[[id]]",     Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid);
          result.replace("[[pw]]",     Blynk8266_WF_config.WiFi_Creds[0].wifi_pw);
          result.replace("[[id1]]",    Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid);
          result.replace("[[pw1]]",    Blynk8266_WF_config.WiFi_Creds[1].wifi_pw);
          result.replace("[[sv]]",     Blynk8266_WF_config.blynk_server);
          result.replace("[[tk]]",     Blynk8266_WF_config.blynk_token);
          
#if USE_DYNAMIC_PARAMETERS
          if (!menuItemUpdated)
          {
            // Don't need to free
            menuItemUpdated = new bool[NUM_MENU_ITEMS];
          }
          
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            String toChange = String("[[") + myMenuItems[i].id + "]]";
            result.replace(toChange, myMenuItems[i].pdata);
            
            // To flag item is not yet updated
            menuItemUpdated[i] = false;
            
  #if ( BLYNK_WM_DEBUG > 2)                 
            BLYNK_LOG4(BLYNK_F("h1:myMenuItems["), i, BLYNK_F("]="), myMenuItems[i].pdata )
  #endif            
          }
#endif
          
          // Check if HTML size is larger than 2K, warn that WebServer won't work
          // because of notorious 2K buffer limitation of ESP8266-AT. 
          uint16_t HTML_page_size = result.length();
          
          BLYNK_LOG2(BLYNK_F("h:HTML page size:"), HTML_page_size);
          
          if (HTML_page_size > MAX_HTML_SIZE)
          {
            BLYNK_LOG1(BLYNK_F("h:HTML page larger than 2K. Config Portal not work. Reduce dynamic params"));
          }   

          server->send(200, "text/html", result);

          return;
        }

        if (number_items_Updated == 0)
        {
          memset(&Blynk8266_WF_config, 0, sizeof(Blynk8266_WF_config));
          strcpy(Blynk8266_WF_config.header, BLYNK_BOARD_TYPE);
        }

        static bool id_Updated  = false;
        static bool pw_Updated  = false;
        static bool id1_Updated = false;
        static bool pw1_Updated = false;
        static bool sv_Updated  = false;
        static bool tk_Updated  = false;
          
        if (!id_Updated && (key == String("id")))
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl id"));
#endif
          id_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid) - 1)
            strcpy(Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid, value.c_str());
          else
            strncpy(Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid, value.c_str(), sizeof(Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid) - 1);
        }
        else if (!pw_Updated && (key == String("pw")))
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl pw"));
#endif
          pw_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.WiFi_Creds[0].wifi_pw) - 1)
            strcpy(Blynk8266_WF_config.WiFi_Creds[0].wifi_pw, value.c_str());
          else
            strncpy(Blynk8266_WF_config.WiFi_Creds[0].wifi_pw, value.c_str(), sizeof(Blynk8266_WF_config.WiFi_Creds[0].wifi_pw) - 1);
        }
        else if (!id1_Updated && (key == String("id1")))
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl id1"));
#endif
          id1_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid) - 1)
            strcpy(Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid, value.c_str());
          else
            strncpy(Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid, value.c_str(), sizeof(Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid) - 1);
        }
        else if (!pw1_Updated && (key == String("pw1")))
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl pw1"));
#endif
          pw1_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.WiFi_Creds[1].wifi_pw) - 1)
            strcpy(Blynk8266_WF_config.WiFi_Creds[1].wifi_pw, value.c_str());
          else
            strncpy(Blynk8266_WF_config.WiFi_Creds[1].wifi_pw, value.c_str(), sizeof(Blynk8266_WF_config.WiFi_Creds[1].wifi_pw) - 1);
        }
        else if (!sv_Updated && (key == String("sv")))
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl sv"));
#endif
          sv_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.blynk_server) - 1)
            strcpy(Blynk8266_WF_config.blynk_server, value.c_str());
          else
            strncpy(Blynk8266_WF_config.blynk_server, value.c_str(), sizeof(Blynk8266_WF_config.blynk_server) - 1);
        }
        //else if (key == "tk")
        else if (!tk_Updated && (key == String("tk")))
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl tk"));
#endif
          tk_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.blynk_token) - 1)
            strcpy(Blynk8266_WF_config.blynk_token, value.c_str());
          else
            strncpy(Blynk8266_WF_config.blynk_token, value.c_str(), sizeof(Blynk8266_WF_config.blynk_token) - 1);
        }
  
#if USE_DYNAMIC_PARAMETERS        
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          if ( !menuItemUpdated[i] && (key == myMenuItems[i].id) )
          {
            BLYNK_LOG4(BLYNK_F("h:"), myMenuItems[i].id, BLYNK_F("="), value.c_str() );
            
            menuItemUpdated[i] = true;
            
            number_items_Updated++;

            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);

            if ((int) strlen(value.c_str()) < myMenuItems[i].maxlen)
              strcpy(myMenuItems[i].pdata, value.c_str());
            else
              strncpy(myMenuItems[i].pdata, value.c_str(), myMenuItems[i].maxlen);
          }
        }
#endif

        //#if ( BLYNK_WM_DEBUG > 2)   
        BLYNK_LOG2(F("h:items updated ="), number_items_Updated);
        BLYNK_LOG4(F("h:key ="), key, ", value =", value);
        //#endif

        server->send(200, "text/html", "OK");

#if USE_DYNAMIC_PARAMETERS        
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS + NUM_MENU_ITEMS)
#else
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
#endif 
        {
          BLYNK_LOG1(BLYNK_F("h:UpdEEPROM"));

          saveConfigData();
          
          // Done with CP, Clear CP Flag here if forced
          if (isForcedConfigPortal)
            clearForcedCP();

          BLYNK_LOG1(BLYNK_F("h:Rst"));

          // TO DO : what command to reset
          // Delay then reset the board after save data
          delay(1000);
          resetFunc();  //call reset
        }
      }   // if (server)
    }
    
    //////////////////////////////////////////////

    void startConfigurationMode()
    {
#define CONFIG_TIMEOUT			60000L

      // initialize ESP module
#if USE_ESP32_AT
          wifi->restore();
#endif
      
      WiFi.init(wifi->getUart());      
      WiFi.configAP(portal_apIP);

      if ( (portal_ssid == "") || portal_pass == "" )
      {
        String randomNum = String(random(0xFFFFFF), HEX);
        randomNum.toUpperCase();

        portal_ssid = "STM32_" + randomNum;
        portal_pass = "MySTM32_" + randomNum;
      }

      BLYNK_LOG6(BLYNK_F("stConf:SSID="), portal_ssid, BLYNK_F(",PW="), portal_pass, BLYNK_F(",IP="), portal_apIP);

      // start access point, AP only, channel 10     
      uint16_t channel;
     
      // Use random channel if  AP_channel == 0     
      if (AP_channel == 0)
        channel = (millis() % MAX_WIFI_CHANNEL) + 1;
      else
        channel = AP_channel;

      BLYNK_LOG4(BLYNK_F("SSID="), portal_ssid, BLYNK_F(",PW="), portal_pass);
      BLYNK_LOG4(BLYNK_F("IP="), portal_apIP, BLYNK_F(",CH="), channel);
     
      WiFi.beginAP(portal_ssid.c_str(), channel, portal_pass.c_str(), ENC_TYPE_WPA2_PSK, true);

      if (!server)
      {
        server = new ESP8266_AT_WebServer;
      }

      // Don't know if it's working or not. Can we use ESP8266_Lib wifi TCP server for this ??

      //See https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type?rq=1

      if (server)
      {
        server->on("/", [this]() { handleRequest(); });
        server->begin();
      }

      // If there is no saved config Data, stay in config mode forever until having config Data.
      // or SSID, PW, Server,Token ="nothing"
      if (hadConfigData)
        configTimeout = millis() + CONFIG_TIMEOUT;
      else
        configTimeout = 0;

      configuration_mode = true;
    }

};


static BlynkTransportShieldEsp8266 _blynkTransport;
BlynkWifi Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif
