/****************************************************************************************************************************
   BlynkSimpleShieldEsp8266_nRF52_WM.h
   For nRF52 boards using ESP8266 WiFi Shields

   Blynk_Esp8266AT_WM is a library for the Mega, Teensy, SAM DUE and SAMD boards (https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
   to enable easy configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk

   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
   Licensed under MIT license
   Version: 1.0.7

   Original Blynk Library author:
   @file       BlynkSimpleShieldEsp8266.h
   @author     Volodymyr Shymanskyy
   @license    This project is released under the MIT License (MIT)
   @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
   @date       Jun 2015
   @brief

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

#ifndef BlynkSimpleShieldEsp8266_nRF52_WM_h
#define BlynkSimpleShieldEsp8266_nRF52_WM_h

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
      defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
#if defined(BLYNK_ESP8266_AT_USE_nRF528XX)
#undef BLYNK_ESP8266_AT_USE_nRF528XX
#endif
#define BLYNK_ESP8266_AT_USE_nRF528XX      true
#warning Use nFR52 architecture from Blynk_Esp8266AT_WM
#endif

#if ( defined(ESP8266) || defined(ESP32) || defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA) || !(BLYNK_ESP8266_AT_USE_nRF528XX) )
#error This code is intended to run on the nRF52 platform! Please check your Tools->Board setting.
#endif

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

//Use LittleFS for nRF52
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

using namespace Adafruit_LittleFS_Namespace;
File file(InternalFS);

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

///NEW
extern uint16_t NUM_MENU_ITEMS;
extern MenuItem myMenuItems [];

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
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 4 )
////////////////

typedef struct Configuration
{
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char blynk_server   [32];
  char blynk_token    [36];
  int  blynk_port;
  char board_name     [24];
  int  checkSum;
} Blynk_WF_Configuration;

// Currently CONFIG_DATA_SIZE  =   308  = (16 + 96 * 2 + 32 + 4 + 36 + 24 + 4)
uint16_t CONFIG_DATA_SIZE = sizeof(Blynk_WF_Configuration);

///New from v1.0.5
extern bool LOAD_DEFAULT_CONFIG_DATA;
extern Blynk_WF_Configuration defaultConfig;

// -- HTML page fragments
const char ESP_AT_HTML_HEAD[]     /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>nRF52_WM</title><style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style></head><div style=\"text-align:left;display:inline-block;min-width:260px;\">\
<fieldset><div><label>WiFi SSID</label><input value=\"[[id]]\"id=\"id\"><div></div></div>\
<div><label>PWD</label><input value=\"[[pw]]\"id=\"pw\"><div></div></div>\
<div><label>WiFi SSID1</label><input value=\"[[id1]]\"id=\"id1\"><div></div></div>\
<div><label>PWD1</label><input value=\"[[pw1]]\"id=\"pw1\"><div></div></div></fieldset>\
<fieldset><div><label>Server</label><input value=\"[[sv]]\"id=\"sv\"><div></div></div>\
<div><label>Token</label><input value=\"[[tk]]\"id=\"tk\"><div></div></div>\
<div><label>Port</label><input type=\"number\"value=\"[[pt]]\"id=\"pt\"><div></div></div></fieldset>\
<fieldset><div><label>BrdName</label><input value=\"[[nm]]\"id=\"nm\"><div></div></div></fieldset>";

const char ESP_AT_FLDSET_START[]  /*PROGMEM*/ = "<fieldset>";
const char ESP_AT_FLDSET_END[]    /*PROGMEM*/ = "</fieldset>";
const char ESP_AT_HTML_PARAM[]    /*PROGMEM*/ = "<div><label>{b}</label><input value='[[{v}]]'id='{i}'><div></div></div>";
const char ESP_AT_HTML_BUTTON[]   /*PROGMEM*/ = "<button onclick=\"sv()\">Save</button></div>";
const char ESP_AT_HTML_SCRIPT[]   /*PROGMEM*/ = "<script id=\"jsbin-javascript\">\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+encodeURIComponent(val);\
request.open('GET',url,false);request.send(null);}\
function sv(){udVal('id',document.getElementById('id').value);udVal('pw',document.getElementById('pw').value);\
udVal('id1',document.getElementById('id1').value);udVal('pw1',document.getElementById('pw1').value);\
udVal('sv',document.getElementById('sv').value);udVal('tk',document.getElementById('tk').value);\
udVal('pt',document.getElementById('pt').value);udVal('nm',document.getElementById('nm').value);";

const char ESP_AT_HTML_SCRIPT_ITEM[]  /*PROGMEM*/ = "udVal('{d}',document.getElementById('{d}').value);";
const char ESP_AT_HTML_SCRIPT_END[]   /*PROGMEM*/ = "alert('Updated');}</script>";
const char ESP_AT_HTML_END[]          /*PROGMEM*/ = "</html>";
///

#define BLYNK_SERVER_HARDWARE_PORT    8080

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
#if (BLYNK_ESP8266_AT_USE_nRF528XX)
    // For all nRF52
    BlynkFifo<uint8_t, 4096> buffer;
#warning Board nRF52 uses 4k FIFO buffer
#else
    // For other unknown nRF52
    //BlynkFifo<uint8_t,256> buffer;
    BlynkFifo<uint8_t, 512> buffer;
#warning Not known nRF52 board => uses 512bytes FIFO buffer
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
      BLYNK_LOG1(BLYNK_F("begin: connectWiFi"));
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

      // Enforce NUM_MENU_ITEMS <= 3
      // Due to notorious 2K buffer limitation of ESO8266-AT shield, the NUM_MENU_ITEMS is limited to max 3
      // to avoid WebServer not working due to HTML data larger than 2K can't be sent successfully
      // The items with index larger than 3 will be ignored
      if (NUM_MENU_ITEMS > 3)
        NUM_MENU_ITEMS = 3;

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
      BLYNK_LOG1(BLYNK_F("======= Start Default Config Data ======="));
      displayConfigData(defaultConfig);
      
      hadConfigData = getConfigData();

      //// New DRD ////
      //  noConfigPortal when getConfigData() OK and no DRD'ed
      if (hadConfigData && noConfigPortal) 
      //// New DRD //// 
      {
        hadConfigData = true;

        config(esp8266, Blynk8266_WF_config.blynk_token, Blynk8266_WF_config.blynk_server, Blynk8266_WF_config.blynk_port);

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
        BLYNK_LOG2(BLYNK_F("b:Stay in CfgPortal:"), noConfigPortal ? BLYNK_F("No CfgDat") : BLYNK_F("DRD"));
        
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
    #define MAX_WIFI_CHANNEL      12    // Channel 13 is flaky, because of bad number 13 ;-)

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

    String getBoardName()
    {
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WF_config.board_name));
    }

    int getHWPort()
    {
      if (!hadConfigData)
        getConfigData();

      return (Blynk8266_WF_config.blynk_port);
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

    String getLocalIP(void)
    {
      uint16_t indexNextLine;

      ipAddress = wifi->getLocalIP();
      ipAddress.replace("+CIFSR:STAIP,\"", "");
      ipAddress.replace("\"", "");
      indexNextLine = ipAddress.indexOf("\n");
      ipAddress = ipAddress.substring(0, indexNextLine);

#if ( BLYNK_WM_DEBUG > 3)
      BLYNK_LOG2(BLYNK_F("getLocalIP: IP = "), ipAddress);
#endif     
      return ipAddress;
    }

    void clearConfigData()
    {
      memset(&Blynk8266_WF_config, 0, sizeof(Blynk8266_WF_config));
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
      }

      saveConfigData();
    }
        
    bool isConfigDataValid(void)
    {
      return hadConfigData;
    }

    void resetFunc()
    {
      delay(1000);
      // Restart for nRF52
      NVIC_SystemReset();
    }

  private:
    ESP8266* wifi;
    String ipAddress = "0.0.0.0";

    ESP8266_AT_WebServer* server;
    bool configuration_mode = false;

    unsigned long configTimeout;
    bool hadConfigData = false;

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
      BLYNK_LOG6(BLYNK_F("Svr="),   configData.blynk_server, BLYNK_F(",Prt="), configData.blynk_port,
                BLYNK_F(",Tok="),   configData.blynk_token);  
      BLYNK_LOG2(BLYNK_F("BName="), configData.board_name);
      
#if ( BLYNK_WM_DEBUG > 2)    
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {
        BLYNK_LOG6("i=", i, ",id=", myMenuItems[i].id, ",data=", myMenuItems[i].pdata);
      }      
#endif 
    }

    void displayWiFiData(void)
    {
      BLYNK_LOG2(BLYNK_F("IP="), getLocalIP());
    }

#define BLYNK_BOARD_TYPE   "SHD_ESP8266"
#define WM_NO_CONFIG       "blank"


    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(Blynk8266_WF_config) - sizeof(Blynk8266_WF_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &Blynk8266_WF_config ) + index);
      }

      return checkSum;
    }
    
    // Use LittleFS/InternalFS for nRF52
#define  CONFIG_FILENAME              ("/wm_config.dat")
#define  CONFIG_FILENAME_BACKUP       ("/wm_config.bak")

#define  CREDENTIALS_FILENAME         ("/wm_cred.dat")
#define  CREDENTIALS_FILENAME_BACKUP  ("/wm_cred.bak")
   
    bool checkDynamicData(void)
    {
      int checkSum = 0;
      int readCheckSum;
      char* readBuffer;
           
      file.open(CREDENTIALS_FILENAME, FILE_O_READ);
      BLYNK_LOG1(BLYNK_F("LoadCredFile "));

      if (!file)
      {
        BLYNK_LOG1(BLYNK_F("failed"));

        // Trying open redundant config file
        file.open(CREDENTIALS_FILENAME_BACKUP, FILE_O_READ);
        BLYNK_LOG1(BLYNK_F("LoadBkUpCredFile "));

        if (!file)
        {
          BLYNK_LOG1(BLYNK_F("failed"));
          return false;
        }
      }
      
      BLYNK_LOG1(BLYNK_F("OK"));
      
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      
      uint16_t maxBufferLength = 0;
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > maxBufferLength)
          maxBufferLength = myMenuItems[i].maxlen;
      }
      
      if (maxBufferLength > 0)
      {
        readBuffer = new char[ maxBufferLength + 1 ];
        
        // check to see NULL => stop and return false
        if (readBuffer == NULL)
        {
          BLYNK_LOG1(BLYNK_F("ChkCrR: Error can't allocate buffer."));
          return false;
        }
#if ( BLYNK_WM_DEBUG > 2)             
        else
        {
          BLYNK_LOG2(BLYNK_F("ChkCrR: Buffer allocated, Sz="), maxBufferLength + 1);
        }  
#endif          
      }
     
      uint16_t offset = 0;
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = readBuffer;

        // Actual size of pdata is [maxlen + 1]
        memset(readBuffer, 0, myMenuItems[i].maxlen + 1);
        
        // Redundant, but to be sure correct position
        file.seek(offset);
        file.read(_pointer, myMenuItems[i].maxlen);
        
        offset += myMenuItems[i].maxlen;

#if ( BLYNK_WM_DEBUG > 2)     
        BLYNK_LOG4(BLYNK_F("ChkCrR:pdata="), readBuffer, BLYNK_F(",len="), myMenuItems[i].maxlen);         
#endif
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }       
      }

      file.read((char *) &readCheckSum, sizeof(readCheckSum));
           
      file.close();
      
      BLYNK_LOG4(BLYNK_F("CrCCsum=0x"), String(checkSum, HEX), BLYNK_F(",CrRCsum=0x"), String(readCheckSum, HEX));
      
      // Free buffer
      if (readBuffer != NULL)
      {
        free(readBuffer);

#if ( BLYNK_WM_DEBUG > 2)    
        BLYNK_LOG1(BLYNK_F("Buffer freed"));
#endif        
      }
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }

    bool loadDynamicData(void)
    {
      int checkSum = 0;
      int readCheckSum;
      totalDataSize = sizeof(Blynk8266_WF_config) + sizeof(readCheckSum);
      
      file.open(CREDENTIALS_FILENAME, FILE_O_READ);
      BLYNK_LOG1(BLYNK_F("LoadCredFile "));

      if (!file)
      {
        BLYNK_LOG1(BLYNK_F("failed"));

        // Trying open redundant config file
        file.open(CREDENTIALS_FILENAME_BACKUP, FILE_O_READ);
        BLYNK_LOG1(BLYNK_F("LoadBkUpCredFile "));

        if (!file)
        {
          BLYNK_LOG1(BLYNK_F("failed"));
          return false;
        }
      }
      
      BLYNK_LOG1(BLYNK_F("OK"));
     
      uint16_t offset = 0;
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;

        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
        
        // Redundant, but to be sure correct position
        file.seek(offset);
        file.read(_pointer, myMenuItems[i].maxlen);
        
        offset += myMenuItems[i].maxlen;        

#if ( BLYNK_WM_DEBUG > 2)    
        BLYNK_LOG4(BLYNK_F("CrR:pdata="), myMenuItems[i].pdata, BLYNK_F(",len="), myMenuItems[i].maxlen);         
#endif
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }       
      }

      file.read((char *) &readCheckSum, sizeof(readCheckSum));     
      
      file.close();
      
      BLYNK_LOG4(BLYNK_F("CrCCsum=0x"), String(checkSum, HEX), BLYNK_F(",CrRCsum=0x"), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }

    void saveDynamicData(void)
    {
      int checkSum = 0;
    
      file.open(CREDENTIALS_FILENAME, FILE_O_WRITE);
      BLYNK_LOG1(BLYNK_F("SaveCredFile "));

      uint16_t offset = 0;
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;

#if ( BLYNK_WM_DEBUG > 2)       
        BLYNK_LOG4(BLYNK_F("CW1:pdata="), myMenuItems[i].pdata, BLYNK_F(",len="), myMenuItems[i].maxlen);
#endif
        
        if (file)
        {
          // Redundant, but to be sure correct position
          file.seek(offset);                   
          file.write((uint8_t*) _pointer, myMenuItems[i].maxlen); 
          
          offset += myMenuItems[i].maxlen;      
        }
        else
        {
          BLYNK_LOG1(BLYNK_F("failed"));
        }        
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;     
         }
      }
      
      if (file)
      {
        file.write((uint8_t*) &checkSum, sizeof(checkSum));     
        file.close();
        BLYNK_LOG1(BLYNK_F("OK"));    
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("failed"));
      }   
           
      BLYNK_LOG2(BLYNK_F("CrWCSum=0x"), String(checkSum, HEX));
      
      // Trying open redundant Auth file
      file.open(CREDENTIALS_FILENAME_BACKUP, FILE_O_WRITE);
      BLYNK_LOG1(BLYNK_F("SaveBkUpCredFile "));

      offset = 0;
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;

#if ( BLYNK_WM_DEBUG > 2)     
        BLYNK_LOG4(BLYNK_F("CW2:pdata="), myMenuItems[i].pdata, BLYNK_F(",len="), myMenuItems[i].maxlen);
#endif
        
        if (file)
        {
          file.seek(offset);                   
          file.write((uint8_t*) _pointer, myMenuItems[i].maxlen); 
          
          // Redundant, but to be sure correct position
          offset += myMenuItems[i].maxlen; 
        }
        else
        {
          BLYNK_LOG1(BLYNK_F("failed"));
        }        
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;     
         }
      }
      
      if (file)
      {
        file.write((uint8_t*) &checkSum, sizeof(checkSum));     
        file.close();
        BLYNK_LOG1(BLYNK_F("OK"));    
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("failed"));
      }   
    }

    void loadConfigData(void)
    {
      BLYNK_LOG1(BLYNK_F("LoadCfgFile "));
      
      // file existed
      file.open(CONFIG_FILENAME, FILE_O_READ);      
      if (!file)
      {
        BLYNK_LOG1(BLYNK_F("failed"));

        // Trying open redundant config file
        file.open(CONFIG_FILENAME_BACKUP, FILE_O_READ);
        BLYNK_LOG1(BLYNK_F("LoadBkUpCfgFile "));

        if (!file)
        {
          BLYNK_LOG1(BLYNK_F("failed"));
          return;
        }
      }
      
      BLYNK_LOG1(BLYNK_F("OK"));
     
      file.seek(0);
      file.read((char *) &Blynk8266_WF_config, sizeof(Blynk8266_WF_config));
      
      file.close();
    }

    void saveConfigData(void)
    {
      BLYNK_LOG1(BLYNK_F("SaveCfgFile "));

      int calChecksum = calcChecksum();
      Blynk8266_WF_config.checkSum = calChecksum;
      BLYNK_LOG2(BLYNK_F("WCSum=0x"), String(calChecksum, HEX));
      
      file.open(CONFIG_FILENAME, FILE_O_WRITE);

      if (file)
      {
        file.seek(0);
        file.write((uint8_t*) &Blynk8266_WF_config, sizeof(Blynk8266_WF_config));
        
        file.close();
        BLYNK_LOG1(BLYNK_F("OK"));
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("failed"));
      }
      
      BLYNK_LOG1(BLYNK_F("SaveBkUpCfgFile "));
      
      // Trying open redundant Auth file
      file.open(CONFIG_FILENAME_BACKUP, FILE_O_WRITE);

      if (file)
      {
        file.seek(0);
        file.write((uint8_t *) &Blynk8266_WF_config, sizeof(Blynk8266_WF_config));
        
        file.close();
        BLYNK_LOG1(BLYNK_F("OK"));
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("failed"));
      }
      
      saveDynamicData();
    }  
    
    void loadAndSaveDefaultConfigData(void)
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

    // Return false if init new EEPROM or SPIFFS. No more need trying to connect. Go directly to config mode
    bool getConfigData()
    {
      bool dynamicDataValid;
      int calChecksum;   
      
      hadConfigData = false;
      
      // Initialize Internal File System
      if (!InternalFS.begin())
      {
        BLYNK_LOG1(F("InternalFS failed"));
        return false;
      }

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
        loadConfigData();
        
        // Load stored default data from EEPROM
       //dynamicDataValid = loadDynamicData();
        dynamicDataValid = checkDynamicData();
        
        // Verify ChkSum        
        calChecksum = calcChecksum();

        BLYNK_LOG4(BLYNK_F("CCSum=0x"), String(calChecksum, HEX),
                   BLYNK_F(",RCSum=0x"), String(Blynk8266_WF_config.checkSum, HEX));
                   
        if (dynamicDataValid)
        {
          loadDynamicData();
          
#if ( BLYNK_WM_DEBUG > 2)      
          BLYNK_LOG1(BLYNK_F("Valid Stored Dynamic Data"));
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

      if ( (strncmp(Blynk8266_WF_config.header, BLYNK_BOARD_TYPE, strlen(BLYNK_BOARD_TYPE)) != 0) ||
           (calChecksum != Blynk8266_WF_config.checkSum) || !dynamicDataValid )
      {
        // Including Credentials CSum
        BLYNK_LOG2(BLYNK_F("InitCfgFile,Sz="), totalDataSize);

        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&Blynk8266_WF_config, &defaultConfig, sizeof(Blynk8266_WF_config));
        }
        else
        {
          memset(&Blynk8266_WF_config, 0, sizeof(Blynk8266_WF_config));

          for (int i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
          }
              
          // doesn't have any configuration
          strcpy(Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid,       WM_NO_CONFIG);
          strcpy(Blynk8266_WF_config.WiFi_Creds[0].wifi_pw,         WM_NO_CONFIG);
          strcpy(Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid,       WM_NO_CONFIG);
          strcpy(Blynk8266_WF_config.WiFi_Creds[1].wifi_pw,         WM_NO_CONFIG);
          strcpy(Blynk8266_WF_config.blynk_server,                  WM_NO_CONFIG);
          strcpy(Blynk8266_WF_config.blynk_token,                   WM_NO_CONFIG);
          Blynk8266_WF_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
          strcpy(Blynk8266_WF_config.board_name,  WM_NO_CONFIG);
          
          for (int i = 0; i < NUM_MENU_ITEMS; i++)
          {
            strncpy(myMenuItems[i].pdata, WM_NO_CONFIG, myMenuItems[i].maxlen);
          }
        }
    
        strcpy(Blynk8266_WF_config.header, BLYNK_BOARD_TYPE);
        
#if ( BLYNK_WM_DEBUG > 2)
        for (int i = 0; i < NUM_MENU_ITEMS; i++)
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
    
    // NEW
    void createHTML(String& root_html_template)
    {
      String pitem;
           
      root_html_template = String(ESP_AT_HTML_HEAD)  + ESP_AT_FLDSET_START;
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(ESP_AT_HTML_PARAM);

        pitem.replace("{b}", myMenuItems[i].displayName);
        pitem.replace("{v}", myMenuItems[i].id);
        pitem.replace("{i}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
      
      root_html_template += String(ESP_AT_FLDSET_END) + ESP_AT_HTML_BUTTON + ESP_AT_HTML_SCRIPT;     
           
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(ESP_AT_HTML_SCRIPT_ITEM);
        
        pitem.replace("{d}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
      
      root_html_template += String(ESP_AT_HTML_SCRIPT_END) + ESP_AT_HTML_END;
            
      return;     
    }

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
          
          if ( Blynk8266_WF_config.board_name[0] != 0 )
          {
            // Or replace only if board_name is valid.  Otherwise, keep intact
            result.replace("nRF52_WM", Blynk8266_WF_config.board_name);
          }

          result.replace("[[id]]",     Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid);
          result.replace("[[pw]]",     Blynk8266_WF_config.WiFi_Creds[0].wifi_pw);
          result.replace("[[id1]]",    Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid);
          result.replace("[[pw1]]",    Blynk8266_WF_config.WiFi_Creds[1].wifi_pw);
          result.replace("[[sv]]",     Blynk8266_WF_config.blynk_server);
          result.replace("[[tk]]",     Blynk8266_WF_config.blynk_token);
          result.replace("[[pt]]",     String(Blynk8266_WF_config.blynk_port));         
          result.replace("[[nm]]",     Blynk8266_WF_config.board_name);
          
          for (int i = 0; i < NUM_MENU_ITEMS; i++)
          {
            String toChange = String("[[") + myMenuItems[i].id + "]]";
            result.replace(toChange, myMenuItems[i].pdata);
          }
          
          // Check if HTML size is larger than 2K, warn that WebServer won't work
          // because of notorious 2K buffer limitation of ESP8266-AT. 
          uint16_t HTML_page_size = result.length();
          
          BLYNK_LOG2(BLYNK_F("h:HTML page size:"), HTML_page_size);
          
          if (HTML_page_size > 2048)
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

        if (key == "id")
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl id"));
#endif
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid) - 1)
            strcpy(Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid, value.c_str());
          else
            strncpy(Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid, value.c_str(), sizeof(Blynk8266_WF_config.WiFi_Creds[0].wifi_ssid) - 1);
        }
        else if (key == "pw")
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl pw"));
#endif
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.WiFi_Creds[0].wifi_pw) - 1)
            strcpy(Blynk8266_WF_config.WiFi_Creds[0].wifi_pw, value.c_str());
          else
            strncpy(Blynk8266_WF_config.WiFi_Creds[0].wifi_pw, value.c_str(), sizeof(Blynk8266_WF_config.WiFi_Creds[0].wifi_pw) - 1);
        }
        else if (key == "id1")
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl id1"));
#endif
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid) - 1)
            strcpy(Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid, value.c_str());
          else
            strncpy(Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid, value.c_str(), sizeof(Blynk8266_WF_config.WiFi_Creds[1].wifi_ssid) - 1);
        }
        else if (key == "pw1")
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl pw1"));
#endif
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.WiFi_Creds[1].wifi_pw) - 1)
            strcpy(Blynk8266_WF_config.WiFi_Creds[1].wifi_pw, value.c_str());
          else
            strncpy(Blynk8266_WF_config.WiFi_Creds[1].wifi_pw, value.c_str(), sizeof(Blynk8266_WF_config.WiFi_Creds[1].wifi_pw) - 1);
        }
        else if (key == "sv")
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl sv"));
#endif
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.blynk_server) - 1)
            strcpy(Blynk8266_WF_config.blynk_server, value.c_str());
          else
            strncpy(Blynk8266_WF_config.blynk_server, value.c_str(), sizeof(Blynk8266_WF_config.blynk_server) - 1);
        }
        else if (key == "tk")
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl tk"));
#endif
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.blynk_token) - 1)
            strcpy(Blynk8266_WF_config.blynk_token, value.c_str());
          else
            strncpy(Blynk8266_WF_config.blynk_token, value.c_str(), sizeof(Blynk8266_WF_config.blynk_token) - 1);
        }
        else if (key == "pt")
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl pt"));
#endif
                    
          number_items_Updated++;
          Blynk8266_WF_config.blynk_port = value.toInt();
        }       
        else if (key == "nm")
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl nm"));
#endif
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.board_name) - 1)
            strcpy(Blynk8266_WF_config.board_name, value.c_str());
          else
            strncpy(Blynk8266_WF_config.board_name, value.c_str(), sizeof(Blynk8266_WF_config.board_name) - 1);
        }
        
        for (int i = 0; i < NUM_MENU_ITEMS; i++)
        {
          if (key == myMenuItems[i].id)
          {
            BLYNK_LOG4(BLYNK_F("h:"), myMenuItems[i].id, BLYNK_F("="), value.c_str() );
            number_items_Updated++;

            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);

            if ((int) strlen(value.c_str()) < myMenuItems[i].maxlen)
              strcpy(myMenuItems[i].pdata, value.c_str());
            else
              strncpy(myMenuItems[i].pdata, value.c_str(), myMenuItems[i].maxlen);
          }
        }

        server->send(200, "text/html", "OK");

        // NEW
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS + NUM_MENU_ITEMS)
        {
          BLYNK_LOG1(BLYNK_F("h:UpdLittleFS"));

          saveConfigData();

          BLYNK_LOG1(BLYNK_F("h:Rst"));

          // TO DO : what command to reset
          // Delay then reset the board after save data
          delay(1000);
          resetFunc();  //call reset
        }
      }   // if (server)
    }

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

        portal_ssid = "nRF52_" + randomNum;
        portal_pass = "MynRF52_" + randomNum;
      }

      BLYNK_LOG6(BLYNK_F("stConf:SSID="), portal_ssid, BLYNK_F(",PW="), portal_pass, BLYNK_F(",IP="), portal_apIP);

      // start access point, AP only, channel 10
           
      uint16_t channel;
     
      // Use random channel if  AP_channel == 0
      //srand(MAX_WIFI_CHANNEL);
      srand((uint16_t) millis());
      
      if (AP_channel == 0)
        channel = (rand() % MAX_WIFI_CHANNEL) + 1;     //random(MAX_WIFI_CHANNEL) + 1;
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

#endif    //BlynkSimpleShieldEsp8266_nRF52_WM_h
