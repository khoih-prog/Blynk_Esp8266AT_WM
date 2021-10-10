/****************************************************************************************************************************
  BlynkSimpleShieldEsp8266_Teensy_WM_Single.h
  For Teensy boards using ESP8266 WiFi Shields

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

#ifndef BlynkSimpleShieldEsp8266_Teensy_WM_Single_h
#define BlynkSimpleShieldEsp8266_Teensy_WM_Single_h

#if defined(CORE_TEENSY)
  #if defined(BLYNK_ESP8266_AT_USE_TEENSY)
    #undef BLYNK_ESP8266_AT_USE_TEENSY
  #endif
  #define BLYNK_ESP8266_AT_USE_TEENSY      true
  #warning Use Teensy architecture from Blynk_Esp8266AT_WM
#else
  #error This code is intended to run on the Teensy platform! Please check your Tools->Board setting.
#endif

#if !( (TEENSYDUINO==150) ||  (TEENSYDUINO==151) )
  //#error This code is intended to run only on the Teensy code v1.51 ! Please check your Teensy core.
#endif

#define BLYNK_ESP8266AT_WM_VERSION    "Blynk_Esp8266AT_WM v1.3.1"

//////////////////////////////////////////////
// From v1.3.0 to display correct BLYNK_INFO_DEVICE

#define BLYNK_USE_128_VPINS

#if defined(BLYNK_INFO_DEVICE)
  #undef BLYNK_INFO_DEVICE
#endif
#define BLYNK_BUFFERS_SIZE    4096

#if defined(BLYNK_INFO_DEVICE)
  #undef BLYNK_INFO_DEVICE
#endif

#if defined(BOARD_NAME)
  #define BLYNK_INFO_DEVICE   BOARD_NAME
#elif defined(BOARD_TYPE)
  #define BLYNK_INFO_DEVICE   BOARD_TYPE
#else
  #define BLYNK_INFO_DEVICE   "Teensy"
#endif

//////////////////////////////////////////////

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

#ifndef SIMPLE_SHIELD_ESP8266_DEBUG
  #define SIMPLE_SHIELD_ESP8266_DEBUG       0
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

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    4

#define BLYNK_SERVER_HARDWARE_PORT    8080

#define SSID_MAX_LEN      32
//From v1.0.5, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

#define HEADER_MAX_LEN      16
#define SERVER_MAX_LEN      32
#define TOKEN_MAX_LEN       36

typedef struct Configuration
{
  char header         [HEADER_MAX_LEN];
  char wifi_ssid      [SSID_MAX_LEN];
  char wifi_pw        [PASS_MAX_LEN];
  char blynk_server   [SERVER_MAX_LEN];
  char blynk_token    [TOKEN_MAX_LEN];
  int  checkSum;
} Blynk_WF_Configuration;


// Currently CONFIG_DATA_SIZE  =   184
uint16_t CONFIG_DATA_SIZE = sizeof(Blynk_WF_Configuration);

#define root_html_template "\
<!DOCTYPE html><html><head><title>Teensy_WM</title><style>.em{padding-bottom:0px;}div,input{padding:5px;font-size:1em;}input{width:95%;}\
body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}\
</style></head><div style=\"text-align:left;display:inline-block;min-width:260px;\">\
<fieldset><div><label>SSID</label><input value=\"[[id]]\"id=\"id\"><div></div></div><div><label>PWD</label><input value=\"[[pw]]\"id=\"pw\"><div></div></div></fieldset>\
<fieldset><div><label>Server</label><input value=\"[[sv]]\"id=\"sv\"><div></div></div>\
<div><label>Token</label><input value=\"[[tk]]\"id=\"tk\"><div></div></div></fieldset>\
<button onclick=\"sv()\">Save</button></div><script id=\"jsbin-javascript\">\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+val;request.open('GET',url,false);request.send(null);}\
function sv(){udVal('id',document.getElementById('id').value);udVal('pw',document.getElementById('pw').value);udVal('sv',document.getElementById('sv').value);\
udVal('tk',document.getElementById('tk').value);alert('Updated');}</script></html>"

//////////////////////////////////////////////

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

//////////////////////////////////////////////

class BlynkTransportShieldEsp8266
{
    static void onData(uint8_t mux_id, uint32_t len, void* ptr) 
    {
      ((BlynkTransportShieldEsp8266*)ptr)->onData(mux_id, len);
    }
    
    //////////////////////////////////////////////

    void onData(uint8_t mux_id, uint32_t len) 
    {
      if (mux_id != BLYNK_ESP8266_MUX) 
      {
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
      
      while (len) 
      {
        if (client->getUart()->available()) 
        {
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
    
    //////////////////////////////////////////////

  public:
    BlynkTransportShieldEsp8266()
      : client(NULL)
      , status(false)
      , domain(NULL)
      , port(0)
    {}
    
    //////////////////////////////////////////////

    void setEsp8266(ESP8266* esp8266) 
    {
      client = esp8266;
      client->setOnData(onData, this);
    }
    
    //////////////////////////////////////////////

    //TODO: IPAddress

    void begin(const char* d,  uint16_t p) 
    {
      domain = d;
      port = p;
    }
    
    //////////////////////////////////////////////

    bool connect() 
    {
      if (!domain || !port)
        return false;
      status = client->createTCP(BLYNK_ESP8266_MUX, domain, port);
      return status;
    }
    
    //////////////////////////////////////////////

    void disconnect() 
    {
      status = false;
      buffer.clear();
      client->releaseTCP(BLYNK_ESP8266_MUX);
    }
    
    //////////////////////////////////////////////

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
    
    //////////////////////////////////////////////

    size_t write(const void* buf, size_t len) 
    {
      if (client->send(BLYNK_ESP8266_MUX, (const uint8_t*)buf, len)) 
      {
        return len;
      }
      
      return 0;
    }
    
    //////////////////////////////////////////////

    bool connected() 
    {
      return status;
    }
    
    //////////////////////////////////////////////

    int available()
    {
      client->run();
#if (SIMPLE_SHIELD_ESP8266_DEBUG > 2)
      BLYNK_LOG2("Still:", buffer.size());
#endif
      return buffer.size();
    }
    
    //////////////////////////////////////////////

  private:
    ESP8266* client;
    bool status;

    //KH
#ifdef CORE_TEENSY
  #if defined(__IMXRT1062__)
    // For Teensy 4.1/4.0
    BlynkFifo<uint8_t, 4096> buffer;
  #warning Board Teensy 4.0 uses 4k FIFO buffer
  #elif ( defined(__MKL26Z64__) || defined(ARDUINO_ARCH_AVR) )
    // For Teensy LC and 2.0
    BlynkFifo<uint8_t, 512> buffer;
  #warning Teensy LC and 2.0 uses 512bytes FIFO buffer
  #else
    // For Teensy 3.x
    BlynkFifo<uint8_t, 2048> buffer;
  #warning Teensy 3.x uses 2k FIFO buffer
  #endif
#else
    // For other AVR Mega
    BlynkFifo<uint8_t, 256> buffer;
  #warning Not Teensy board => uses 256bytes FIFO buffer
#endif

    const char* domain;
    uint16_t    port;
};

//////////////////////////////////////////////

class BlynkWifi
  : public BlynkProtocol<BlynkTransportShieldEsp8266>
{
    typedef BlynkProtocol<BlynkTransportShieldEsp8266> Base;
    
  public:
    BlynkWifi(BlynkTransportShieldEsp8266& transp)
      : Base(transp)
      , wifi(NULL)
    {}
    
    //////////////////////////////////////////////

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
    
    //////////////////////////////////////////////

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
    
    //////////////////////////////////////////////

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
    
    //////////////////////////////////////////////

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
    
    //////////////////////////////////////////////

    void config(ESP8266& esp8266)
    {
      wifi = &esp8266;
      this->conn.setEsp8266(wifi);
      WiFiInit();
    }
    
    //////////////////////////////////////////////

    void begin(ESP8266& esp8266/*, const char *iHostname = ""*/)
    {
#define RETRY_TIMES_CONNECT_WIFI			3

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
      
      hadConfigData = getConfigData();
      
      isForcedConfigPortal = isForcedCP();

      //// New DRD ////
      //  noConfigPortal when getConfigData() OK and no DRD'ed
      if ( hadConfigData && noConfigPortal && (!isForcedConfigPortal) )
      //// New DRD //// 
      {
        hadConfigData = true;

        config(esp8266, Blynk8266_WF_config.blynk_token, Blynk8266_WF_config.blynk_server, BLYNK_SERVER_HARDWARE_PORT);

        if (connectToWifi(RETRY_TIMES_CONNECT_WIFI))
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
      
      //// New DRD ////
      // Call the double reset detector loop method every so often,
      // so that it can recognise when the timeout expires.
      // You can also call drd.stop() when you wish to no longer
      // consider the next reset as a double reset.
      drd->loop();
      //// New DRD ////

      // Lost connection in running. Give chance to reconfig.
      if ( !wifi_connected /*WiFi.status() != WL_CONNECTED*/ || !connected() )
      {
        // If configTimeout but user hasn't connected to configWeb => try to reconnect WiFi / Blynk.
        // But if user has connected to configWeb, stay there until done, then reset hardware
        if ( configuration_mode && ( configTimeout == 0 ||  millis() < configTimeout ) )
        {
          retryTimes = 0;

          if (server)
          {         
            server->handleClient();
          }

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
          if ( !wifi_connected /*WiFi.status() != WL_CONNECTED*/ )
          {
            BLYNK_LOG1(BLYNK_F("r:Wlost.ReconW+B"));
            if (connectToWifi(RETRY_TIMES_RECONNECT_WIFI))
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
            BLYNK_LOG1(BLYNK_F("r:Blost.TryB"));
            if (connect())
            {
              BLYNK_LOG1(BLYNK_F("r:BOK"));
            }
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

    //////////////////////////////////////////////

    void setConfigPortalIP(IPAddress portalIP = IPAddress(192, 168, 4, 1))
    {
      portal_apIP = portalIP;
    }
    
    //////////////////////////////////////////////
    
    #define MIN_WIFI_CHANNEL      1
    #define MAX_WIFI_CHANNEL      11    // Channel 12, 13 is flaky, because of bad number 13 ;-)

    //////////////////////////////////////////////
    
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
    
    //////////////////////////////////////////////

    void setConfigPortal(String ssid = "", String pass = "")
    {
      portal_ssid = ssid;
      portal_pass = pass;
    }
    
    //////////////////////////////////////////////

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
    
    //////////////////////////////////////////////

    String getServerName()
    {
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WF_config.blynk_server));
    }
    
    //////////////////////////////////////////////

    String getToken()
    {
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WF_config.blynk_token));
    }
    
    //////////////////////////////////////////////

    int getHWPort()
    {
      if (!hadConfigData)
        getConfigData();

      return (BLYNK_SERVER_HARDWARE_PORT);
    }
    
    //////////////////////////////////////////////

    Blynk_WF_Configuration* getFullConfigData(Blynk_WF_Configuration *configData)
    {
      if (!hadConfigData)
        getConfigData();

      // Check if NULL pointer
      if (configData)
        memcpy(configData, &Blynk8266_WF_config, sizeof(Blynk_WF_Configuration));

      return (configData);
    }
    
    //////////////////////////////////////////////

    String getLocalIP(void)
    {
      uint16_t indexNextLine;

      ipAddress = wifi->getLocalIP();
      ipAddress.replace("+CIFSR:STAIP,\"", "");
      ipAddress.replace("\"", "");

      indexNextLine = ipAddress.indexOf("\n");
      ipAddress = ipAddress.substring(0, indexNextLine);

      return ipAddress;
    }
    
    //////////////////////////////////////////////

    void clearConfigData()
    {
      memset(&Blynk8266_WF_config, 0, sizeof(Blynk8266_WF_config));
      saveConfigData();
    }
    
    //////////////////////////////////////////////
    
    // Forced CP => Flag = 0xBEEFBEEF. Else => No forced CP
    // Flag to be stored at (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE) 
    // to avoid corruption to current data
    //#define FORCED_CONFIG_PORTAL_FLAG_DATA              ( (uint32_t) 0xDEADBEEF)
    //#define FORCED_PERS_CONFIG_PORTAL_FLAG_DATA         ( (uint32_t) 0xBEEFDEAD)
    
    const uint32_t FORCED_CONFIG_PORTAL_FLAG_DATA       = 0xDEADBEEF;
    const uint32_t FORCED_PERS_CONFIG_PORTAL_FLAG_DATA  = 0xBEEFDEAD;
    
    #define FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE     4
    
    //////////////////////////////////////////////
    
    void resetAndEnterConfigPortal()
    {
      persForcedConfigPortal = false;
      
      setForcedCP(false);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }
    
    //////////////////////////////////////////////
    
    // This will keep CP forever, until you successfully enter CP, and Save data to clear the flag.
    void resetAndEnterConfigPortalPersistent()
    {
      persForcedConfigPortal = true;
      
      setForcedCP(true);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }
    
    //////////////////////////////////////////////
    
    void resetFunc()
    {
#if defined(__IMXRT1062__)     
      SCB_AIRCR = 0x05FA0004; //write value for restart for Teensy 4.x
#else
      #define RESTART_ADDR       0xE000ED0C
      #define READ_RESTART()     (*(volatile uint32_t *)RESTART_ADDR)
      #define WRITE_RESTART(val) ((*(volatile uint32_t *)RESTART_ADDR) = (val))
      
      WRITE_RESTART(0x5FA0004);
#endif
    }
    
    //////////////////////////////////////////////

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
    
    //////////////////////////////////////////////

    void displayConfigData(void)
    {
      BLYNK_LOG6(BLYNK_F("Hdr="),  Blynk8266_WF_config.header, BLYNK_F(",SSID="), Blynk8266_WF_config.wifi_ssid,
                 BLYNK_F(",PW="),  Blynk8266_WF_config.wifi_pw);
      BLYNK_LOG6(BLYNK_F("Svr="),  Blynk8266_WF_config.blynk_server, BLYNK_F(",Prt="), BLYNK_SERVER_HARDWARE_PORT,
                 BLYNK_F(",Tok="), Blynk8266_WF_config.blynk_token);
    }
    
    //////////////////////////////////////////////

    void displayWiFiData(void)
    {
      BLYNK_LOG2(BLYNK_F("IP="), getLocalIP());
    }
    
    //////////////////////////////////////////////

#define BLYNK_BOARD_TYPE   "SHD_ESP8266"
#define NO_CONFIG           "blank"

    //#define EEPROM_SIZE       E2END
    //#define EEPROM_SIZE       512

    //KH
    // Teensy 4.0 :  EEPROM_SIZE = 3824 = (255 * 15) - 1, why 1080 ???
    // Teensy++2.0, 3.5 and 3.6 : EEPROM_SIZE = 4096
    // Teensy++1.0, 3.0, 3.1 and 3.2 : EEPROM_SIZE = 2048
    // Teensy2.0 : EEPROM_SIZE = 1024
    // Teensy1.0 : EEPROM_SIZE = 512
    // Teensy LC : EEPROM_SIZE = 128

    /*
      Teensy 4.0 => EEPROM_SIZE = 3824 = (255 * 15) - 1
      #define FLASH_SECTORS  15
      #if E2END > (255*FLASH_SECTORS-1)
      #error "E2END is set larger than the maximum possible EEPROM size"
      #endif
      ======================================================
      Teensy3.x
      #if defined(__MK20DX128__)      //Teensy 3.0
      #define EEPROM_MAX  2048
      #elif defined(__MK20DX256__)    //Teensy 3.1 and 3.2
      #define EEPROM_MAX  2048
      #elif defined(__MK64FX512__)    //Teensy 3.5
      #define EEPROM_MAX  4096
      #elif defined(__MK66FX1M0__)    //Teensy 3.6
      #define EEPROM_MAX  4096
      #elif defined(__MKL26Z64__)     //Teensy LC
      #define EEPROM_MAX  255
      #endif
      ======================================================
      Teensy 2.x
      Teensy 2.0
      #if defined(__AVR_ATmega32U4__)     //Teensy 2.0
      #elif defined(__AVR_AT90USB162__)   //Teensy 1.0
      #elif defined(__AVR_AT90USB646__)   //Teensy++ 1.0
      #elif defined(__AVR_AT90USB1286__)  //Teensy++ 2.0
    */

#ifndef EEPROM_SIZE
  #define EEPROM_SIZE     1024
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
  #if (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > EEPROM_SIZE)
    #error EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > EEPROM_SIZE. Please adjust.
  #endif
#endif

// Stating positon to store Blynk8266_WM_config
#define CONFIG_EEPROM_START    (EEPROM_START + DRD_FLAG_DATA_SIZE)

    //////////////////////////////////////////////
    
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
    
    void NULLTerminateConfig()
    {
      //#define HEADER_MAX_LEN      16
      //#define SERVER_MAX_LEN      32
      //#define TOKEN_MAX_LEN       36
      
      // NULL Terminating to be sure
      Blynk8266_WF_config.header      [HEADER_MAX_LEN - 1]  = 0;
      Blynk8266_WF_config.wifi_ssid   [SSID_MAX_LEN - 1]    = 0;
      Blynk8266_WF_config.wifi_pw     [PASS_MAX_LEN - 1]    = 0;
      Blynk8266_WF_config.blynk_server[SERVER_MAX_LEN - 1]  = 0;
      Blynk8266_WF_config.blynk_token [TOKEN_MAX_LEN - 1]   = 0;
    }
    
    //////////////////////////////////////////////

    bool getConfigData()
    {
      EEPROM.get(CONFIG_EEPROM_START, Blynk8266_WF_config);
      NULLTerminateConfig();
      
      hadConfigData = false;

      int calChecksum = calcChecksum();

      BLYNK_LOG4(BLYNK_F("CCSum="), calChecksum, BLYNK_F(",RCSum="), Blynk8266_WF_config.checkSum);

      if ( (strncmp(Blynk8266_WF_config.header, BLYNK_BOARD_TYPE, strlen(BLYNK_BOARD_TYPE)) != 0) ||
           (calChecksum != Blynk8266_WF_config.checkSum) || ( (calChecksum == 0) && (Blynk8266_WF_config.checkSum == 0) ) )
      {
        memset(&Blynk8266_WF_config, 0, sizeof(Blynk8266_WF_config));

        //EEPROM.put(CONFIG_EEPROM_START, Blynk8266_WF_config);

        BLYNK_LOG2(BLYNK_F("InitEEPROM,sz="), EEPROM.length());
        // doesn't have any configuration
        strcpy(Blynk8266_WF_config.header,           BLYNK_BOARD_TYPE);
        strcpy(Blynk8266_WF_config.wifi_ssid,        NO_CONFIG);
        strcpy(Blynk8266_WF_config.wifi_pw,          NO_CONFIG);
        strcpy(Blynk8266_WF_config.blynk_server,     NO_CONFIG);
        strcpy(Blynk8266_WF_config.blynk_token,      NO_CONFIG);
        // Don't need
        Blynk8266_WF_config.checkSum = 0;

        EEPROM.put(CONFIG_EEPROM_START, Blynk8266_WF_config);

        return false;
      }
      else if ( !strncmp(Blynk8266_WF_config.wifi_ssid,       NO_CONFIG, strlen(NO_CONFIG))   ||
                !strncmp(Blynk8266_WF_config.wifi_pw,         NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WF_config.blynk_server,    NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WF_config.blynk_token,     NO_CONFIG, strlen(NO_CONFIG) ) )
      {
        // If SSID, PW, Server,Token ="nothing", stay in config mode forever until having config Data.
        return false;
      }
      else
      {
        displayConfigData();
      }

      return true;
    }
    
    //////////////////////////////////////////////

    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      Blynk8266_WF_config.checkSum = calChecksum;
      BLYNK_LOG4(BLYNK_F("SaveEEPROM,sz="), EEPROM.length(), BLYNK_F(",CSum="), calChecksum);

      EEPROM.put(CONFIG_EEPROM_START, Blynk8266_WF_config);
    }
    
    //////////////////////////////////////////////

    // New connection logic for ESP32-AT from v1.0.6
    bool connectToWifi(int retry_time)
    {
      int sleep_time  = 250;
      
      // Using to force to use connectWiFi() which resets the ESP. Need  only once after the boot
      // After that, only need joinAP() for faster as resetting the ESP is not necessary
      static bool firstTimeConnect = true;
                 
      BLYNK_LOG1(BLYNK_F("Con2Wifi"));

      if (static_IP != IPAddress(0, 0, 0, 0))
      {
        BLYNK_LOG1(BLYNK_F("UseStatIP"));
        wifi->setStationIp(IPAddressToString(static_IP), IPAddressToString(static_GW), IPAddressToString(static_SN));
      }
    
#if USE_ESP32_AT
      if (firstTimeConnect)
      {
        // Fix ESP32-AT multiWiFi auto(re)connection when lost
        // Need only once after reboot
        wifi->restore();
      }
#endif
      
      BLYNK_LOG4(BLYNK_F("con2WF:SSID="), Blynk8266_WF_config.wifi_ssid, BLYNK_F(",PW="), Blynk8266_WF_config.wifi_pw);
             
      while ( !wifi_connected && ( 0 < retry_time ) )
      {
#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG2(BLYNK_F("Remaining retry_time="), retry_time);
#endif

#if USE_ESP32_AT
        // ESP32-AT requires restart everytime !!!
        wifi_connected = connectWiFi(Blynk8266_WF_config.wifi_ssid, Blynk8266_WF_config.wifi_pw);
#else
        if (firstTimeConnect)
        {
          wifi_connected = connectWiFi(Blynk8266_WF_config.wifi_ssid, Blynk8266_WF_config.wifi_pw);
        }
        else
        {
          wifi_connected = wifi->joinAP(Blynk8266_WF_config.wifi_ssid, Blynk8266_WF_config.wifi_pw);
        }
#endif
             
        // Need restart WiFi at beginning of each cycle 
        if (wifi_connected)
        {
          firstTimeConnect = false;
          
          break;
        }
        else
        {
          delay(sleep_time);
          retry_time--;
        }         
      }  

      if (wifi_connected)
      {
        BLYNK_LOG1(BLYNK_F("con2WF:OK"));
        displayWiFiData();
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("con2WF:failed"));  
      }

      return wifi_connected;  
    }
    
    //////////////////////////////////////////////
    
    void createHTML(String& inString)
    {     
      inString = root_html_template;
      
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
#if 1
          String result = String("");
          createHTML(result);
#else        
          String result = root_html_template;
#endif

          BLYNK_LOG1(BLYNK_F("h:repl"));

          // Reset configTimeout to stay here until finished.
          configTimeout = 0;
          
          if (hadConfigData)
          {
            result.replace("[[id]]",     Blynk8266_WF_config.wifi_ssid);
            result.replace("[[pw]]",     Blynk8266_WF_config.wifi_pw);
            result.replace("[[sv]]",     Blynk8266_WF_config.blynk_server);
            result.replace("[[tk]]",     Blynk8266_WF_config.blynk_token);
          }
          else
          {            
            // Better than garbage
            result.replace("[[id]]",  "");
            result.replace("[[pw]]",  "");
            result.replace("[[sv]]",  "blynk_server");
            result.replace("[[tk]]",  "blynk_token");
          }

          server->send(200, "text/html", result);

          return;
        }
               
        static bool id_Updated  = false;
        static bool pw_Updated  = false;
        static bool sv_Updated  = false;
        static bool tk_Updated  = false;

        if (number_items_Updated == 0)
        {
          memset(&Blynk8266_WF_config, 0, sizeof(Blynk8266_WF_config));
          strcpy(Blynk8266_WF_config.header, BLYNK_BOARD_TYPE);
        }

        if (!id_Updated && (key == String("id")))
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl id"));
#endif        

          id_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.wifi_ssid) - 1)
            strcpy(Blynk8266_WF_config.wifi_ssid, value.c_str());
          else
            strncpy(Blynk8266_WF_config.wifi_ssid, value.c_str(), sizeof(Blynk8266_WF_config.wifi_ssid) - 1);
        }
        else if (!pw_Updated && (key == String("pw")))
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:repl pw"));
#endif
          pw_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WF_config.wifi_pw) - 1)
            strcpy(Blynk8266_WF_config.wifi_pw, value.c_str());
          else
            strncpy(Blynk8266_WF_config.wifi_pw, value.c_str(), sizeof(Blynk8266_WF_config.wifi_pw) - 1);
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
        
        //#if ( BLYNK_WM_DEBUG > 2)   
        BLYNK_LOG2(F("h:items updated ="), number_items_Updated);
        BLYNK_LOG4(F("h:key ="), key, ", value =", value);
        //#endif

        server->send(200, "text/html", "OK");

        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
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
    
#ifndef CONFIG_TIMEOUT
  #warning Default CONFIG_TIMEOUT = 60s
  #define CONFIG_TIMEOUT			60000L
#endif

    //////////////////////////////////////////////
    
    void startConfigurationMode()
    {
      // initialize ESP module
#if USE_ESP32_AT
          wifi->restore();
#endif

      // initialize ESP module
      WiFi.init(wifi->getUart());
      WiFi.configAP(portal_apIP);

      if ( (portal_ssid == "") || portal_pass == "" )
      {
#if defined(__IMXRT1062__)      
        String hardwareID = String(HW_OCOTP_MAC0, HEX);  
#else
        // To use hardware ID in future version
        String hardwareID = String(random(0xFFFFFF), HEX);
#endif
        hardwareID.toUpperCase();
        
        portal_ssid = "Teensy_" + hardwareID;
        portal_pass = "MyTeensy_" + hardwareID;
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

//////////////////////////////////////////////

static BlynkTransportShieldEsp8266 _blynkTransport;
BlynkWifi Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif    // BlynkSimpleShieldEsp8266_Teensy_WM_Single_h
