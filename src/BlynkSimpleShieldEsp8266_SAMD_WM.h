/****************************************************************************************************************************
   BlynkSimpleShieldEsp8266_SAMD_WM.h
   For SAMD boards using ESP8266 WiFi Shields

   Blynk_Esp8266AT_WM is a library for the Mega, Teensy, SAM DUE and SAMD boards (https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
   to enable easy configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk

   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
   Licensed under MIT license
   Version: 1.0.4

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
    1.0.1   K Hoang      17/02/2019  Add checksum, fix bug
    1.0.2   K Hoang      22/02/2019  Add support to SAMD boards
    1.0.3   K Hoang      03/03/2019  Add support to STM32 boards, except STM32F0
    1.0.4   K Hoang      13/03/2019  Add SAM DUE support. Enhance GUI. 
 *****************************************************************************************************************************/

#ifndef BlynkSimpleShieldEsp8266_SAMD_WM_h
#define BlynkSimpleShieldEsp8266_SAMD_WM_h

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) )
#if defined(ESP8266_AT_USE_SAMD)
#undef BLYNK_ESP8266_AT_USE_SAMD
#endif
#define BLYNK_ESP8266_AT_USE_SAMD      true
#endif

#if ( defined(ESP8266) || defined(ESP32) || defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA) || defined(CORE_TEENSY) || !(BLYNK_ESP8266_AT_USE_SAMD) )
#error This code is intended to run on the SAMD platform! Please check your Tools->Board setting.
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
#include <ESP8266_Lib.h>

#include <ESP8266_AT_WebServer.h>

//#include <WString.h>
#include <FlashStorage.h>       //https://github.com/cmaglie/FlashStorage

#define SIMPLE_SHIELD_ESP8266_DEBUG       0

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    6
typedef struct Configuration
{
  char header         [16];
  char wifi_ssid      [32];
  char wifi_pw        [32];
  char blynk_server   [32];
  int  blynk_port;
  char blynk_token    [36];
  char board_name     [24];
  int  checkSum;
} Blynk_WF_Configuration;

FlashStorage(Blynk8266_WM_config_data, Blynk_WF_Configuration);

// Currently CONFIG_DATA_SIZE  =   180
uint16_t CONFIG_DATA_SIZE = sizeof(Blynk_WF_Configuration);

#define root_html_template "\
<!DOCTYPE html><html><head><title>BlynkEspAT_SAMD_WM</title><style>.em{padding-bottom:0px;}div,input{padding:5px;font-size:1em;}input{width:95%;}\
body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}\
</style></head><div style=\"text-align:left;display:inline-block;min-width:260px;\">\
<fieldset><div><label>SSID</label><input value=\"[[id]]\"id=\"id\"><div></div></div><div><label>PWD</label><input value=\"[[pw]]\"id=\"pw\"><div></div></div></fieldset>\
<fieldset><div><label>Server</label><input value=\"[[sv]]\"id=\"sv\"><div></div></div><div><label>Port</label><input type=\"number\"value=\"[[pt]]\"id=\"pt\"><div></div></div>\
<div><label>Token</label><input value=\"[[tk]]\"id=\"tk\"><div></div></div></fieldset>\
<fieldset><div><label>Name</label><input value=\"[[nm]]\"id=\"nm\"><div></div></div></fieldset><button onclick=\"sv()\">Save</button></div><script id=\"jsbin-javascript\">\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+val;request.open('GET',url,false);request.send(null);}\
function sv(){udVal('id',document.getElementById('id').value);udVal('pw',document.getElementById('pw').value);udVal('sv',document.getElementById('sv').value);\
udVal('pt',document.getElementById('pt').value);udVal('tk',document.getElementById('tk').value);udVal('nm',document.getElementById('nm').value);alert('Updated');}</script></html>"

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
      BLYNK_LOG4("Got: ", len, ", Free: ", buffer.free());
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
    //KH
#if (BLYNK_ESP8266_AT_USE_SAMD)
    // For NANO_33_IOT, MKRFox1200, MKRWAN1300, MKRWAN1310, MKRGSM1400, MKRNB1500, MKRVIDOR4000.
    BlynkFifo<uint8_t, 4096> buffer;
#warning Board SAMD uses 4k FIFO buffer
#else
    // For other boards
    //BlynkFifo<uint8_t,256> buffer;
    // For MeGa 2560 or 1280
    BlynkFifo<uint8_t, 512> buffer;
#warning Not SAMD board => uses 512bytes FIFO buffer
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
      if (!wifi->restart()) {
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
#define TIMEOUT_CONNECT_WIFI			30000
      config(esp8266);

      if (getConfigData())
      {
        hadConfigData = true;

        config(esp8266, Blynk8266_WM_config.blynk_token, Blynk8266_WM_config.blynk_server, Blynk8266_WM_config.blynk_port);

        if (connectToWifi(TIMEOUT_CONNECT_WIFI))
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
        BLYNK_LOG1(BLYNK_F("b:Nodat.Stay"));
        // failed to connect to Blynk server, will start configuration mode
        hadConfigData = false;
        startConfigurationMode();
      }
    }

#ifndef TIMEOUT_RECONNECT_WIFI
#define TIMEOUT_RECONNECT_WIFI   10000L
#else
    // Force range of user-defined TIMEOUT_RECONNECT_WIFI between 10-60s
#if (TIMEOUT_RECONNECT_WIFI < 10000L)
#warning TIMEOUT_RECONNECT_WIFI too low. Reseting to 10000
#undef TIMEOUT_RECONNECT_WIFI
#define TIMEOUT_RECONNECT_WIFI   10000L
#elif (TIMEOUT_RECONNECT_WIFI > 60000L)
#warning TIMEOUT_RECONNECT_WIFI too high. Reseting to 60000
#undef TIMEOUT_RECONNECT_WIFI
#define TIMEOUT_RECONNECT_WIFI   60000L
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
      if ( !wifi_connected /*WiFi.status() != WL_CONNECTED*/ || !connected() )
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
          if ( !wifi_connected /*WiFi.status() != WL_CONNECTED*/ )
          {
            BLYNK_LOG1(BLYNK_F("r:Wlost.ReconW+B"));
            if (connectToWifi(TIMEOUT_RECONNECT_WIFI))
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

    void setConfigPortalIP(IPAddress portalIP = IPAddress(192, 168, 4, 1))
    {
      portal_apIP = portalIP;
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

    String getServerName()
    {
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WM_config.blynk_server));
    }

    String getToken()
    {
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WM_config.blynk_token));
    }

    String getBoardName()
    {
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WM_config.board_name));
    }

    int getHWPort()
    {
      if (!hadConfigData)
        getConfigData();

      return (Blynk8266_WM_config.blynk_port);
    }

    Blynk_WF_Configuration* getFullConfigData(Blynk_WF_Configuration *configData)
    {
      if (!hadConfigData)
        getConfigData();

      // Check if NULL pointer
      if (configData)
        memcpy(configData, &Blynk8266_WM_config, sizeof(Blynk_WF_Configuration));

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

      //BLYNK_LOG2(BLYNK_F("getLocalIP: IP = "), ipAddress);
      return ipAddress;
    }

    void clearConfigData()
    {
      memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
      //EEPROM.put(EEPROM_START, BlynkEthernet_WM_config);
      Blynk8266_WM_config_data.write(Blynk8266_WM_config);
    }

    void resetFunc()
    {
      BlynkReset();
    }

  private:
    ESP8266* wifi;
    String ipAddress = "0.0.0.0";

    ESP8266_AT_WebServer* server;
    bool configuration_mode = false;

    unsigned long configTimeout;
    bool hadConfigData = false;

    Blynk_WF_Configuration Blynk8266_WM_config;

    String macAddress = "";
    bool wifi_connected = false;

    // For Config Portal, from Blynk_WM v1.0.5
    IPAddress portal_apIP = IPAddress(192, 168, 4, 1);

    String portal_ssid = "";
    String portal_pass = "";

    // For static IP, from Blynk_WM v1.0.5
    IPAddress static_IP   = IPAddress(0, 0, 0, 0);
    IPAddress static_GW   = IPAddress(0, 0, 0, 0);
    IPAddress static_SN   = IPAddress(255, 255, 255, 0);
    IPAddress static_DNS1 = IPAddress(0, 0, 0, 0);
    IPAddress static_DNS2 = IPAddress(0, 0, 0, 0);

    void displayConfigData(void)
    {
      BLYNK_LOG6(BLYNK_F("Hdr="),  Blynk8266_WM_config.header, BLYNK_F(",SSID="), Blynk8266_WM_config.wifi_ssid,
                 BLYNK_F(",PW="),  Blynk8266_WM_config.wifi_pw);
      BLYNK_LOG6(BLYNK_F("Svr="),  Blynk8266_WM_config.blynk_server, BLYNK_F(",Prt="), Blynk8266_WM_config.blynk_port,
                 BLYNK_F(",Tok="), Blynk8266_WM_config.blynk_token);
      BLYNK_LOG2(BLYNK_F("Board Name = "), Blynk8266_WM_config.board_name);
    }

    void displayWiFiData(void)
    {
      BLYNK_LOG2(BLYNK_F("IP="), getLocalIP());
    }

#define BLYNK_BOARD_TYPE   "SHD_ESP8266"
#define NO_CONFIG           "nothing"


    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(Blynk8266_WM_config) - sizeof(Blynk8266_WM_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &Blynk8266_WM_config ) + index);
      }

      return checkSum;
    }

    bool getConfigData()
    {
      //EEPROM.get(EEPROM_START, Blynk8266_WM_config);
      hadConfigData = false;

      Blynk8266_WM_config = Blynk8266_WM_config_data.read();

      int calChecksum = calcChecksum();

      BLYNK_LOG4(BLYNK_F("CCSum="), calChecksum, BLYNK_F(",RCSum="), Blynk8266_WM_config.checkSum);

      if ( (strncmp(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE, strlen(BLYNK_BOARD_TYPE)) != 0) ||
           (calChecksum != Blynk8266_WM_config.checkSum) )
      {
        memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));

        //EEPROM.put(EEPROM_START, Blynk8266_WM_config);
        //Blynk8266_WM_config_data.write(Blynk8266_WM_config);

        BLYNK_LOG2(BLYNK_F("WriteData2Flash,sz="), sizeof(Blynk8266_WM_config));

        // doesn't have any configuration
        strcpy(Blynk8266_WM_config.header,           BLYNK_BOARD_TYPE);
        strcpy(Blynk8266_WM_config.wifi_ssid,        NO_CONFIG);
        strcpy(Blynk8266_WM_config.wifi_pw,          NO_CONFIG);
        strcpy(Blynk8266_WM_config.blynk_server,     NO_CONFIG);
        Blynk8266_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
        strcpy(Blynk8266_WM_config.blynk_token,      NO_CONFIG);
        strcpy(Blynk8266_WM_config.board_name,       NO_CONFIG);
        // Don't need
        Blynk8266_WM_config.checkSum = 0;

        //EEPROM.put(EEPROM_START, Blynk8266_WM_config);
        Blynk8266_WM_config_data.write(Blynk8266_WM_config);

        return false;
      }
      else if ( !strncmp(Blynk8266_WM_config.wifi_ssid,       NO_CONFIG, strlen(NO_CONFIG))   ||
                !strncmp(Blynk8266_WM_config.wifi_pw,         NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.blynk_server,    NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.blynk_token,     NO_CONFIG, strlen(NO_CONFIG) ) )
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

    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      Blynk8266_WM_config.checkSum = calChecksum;

      BLYNK_LOG4(BLYNK_F("SaveData,sz="), sizeof(Blynk8266_WM_config), BLYNK_F(",CSum="), calChecksum);

      //EEPROM.put(EEPROM_START, Blynk8266_WM_config);
      Blynk8266_WM_config_data.write(Blynk8266_WM_config);
    }

    bool connectToWifi(int timeout)
    {
      int sleep_time = 250;
      unsigned long currMillis = millis();

      BLYNK_LOG1(BLYNK_F("con2WF:start"));

      // New from Blynk_WM v1.0.5
      if (static_IP != IPAddress(0, 0, 0, 0))
      {
        BLYNK_LOG1(BLYNK_F("Use static IP"));
        wifi->setStationIp(IPAddressToString(static_IP), IPAddressToString(static_GW), IPAddressToString(static_SN));
      }

      while ( !wifi_connected && ( 0 < timeout ) && ( (millis() - currMillis) < (unsigned long) timeout )  )
      {
        BLYNK_LOG2(BLYNK_F("con2WF:millis="), millis() - currMillis);

        if (connectWiFi(Blynk8266_WM_config.wifi_ssid, Blynk8266_WM_config.wifi_pw))
        {
          wifi_connected = true;
        }
        else
        {
          delay(sleep_time);
          timeout -= sleep_time;
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

    void handleRequest()
    {
      if (server)
      {
        String key    = server->arg("key");
        String value  = server->arg("value");

        static int number_items_Updated = 0;

        if (key == "" && value == "")
        {
          String result = root_html_template;

          BLYNK_LOG1(BLYNK_F("h:repl"));

          // Reset configTimeout to stay here until finished.
          configTimeout = 0;

          result.replace("[[id]]",     Blynk8266_WM_config.wifi_ssid);
          result.replace("[[pw]]",     Blynk8266_WM_config.wifi_pw);
          result.replace("[[sv]]",     Blynk8266_WM_config.blynk_server);
          result.replace("[[pt]]",      String(Blynk8266_WM_config.blynk_port));
          result.replace("[[tk]]",     Blynk8266_WM_config.blynk_token);
          result.replace("[[nm]]",     Blynk8266_WM_config.board_name);

          server->send(200, "text/html", result);

          return;
        }

        if (number_items_Updated == 0)
        {
          memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
          strcpy(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE);
        }

        if (key == "id")
        {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.wifi_ssid) - 1)
            strcpy(Blynk8266_WM_config.wifi_ssid, value.c_str());
          else
            strncpy(Blynk8266_WM_config.wifi_ssid, value.c_str(), sizeof(Blynk8266_WM_config.wifi_ssid) - 1);
        }
        else if (key == "pw")
        {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.wifi_pw) - 1)
            strcpy(Blynk8266_WM_config.wifi_pw, value.c_str());
          else
            strncpy(Blynk8266_WM_config.wifi_pw, value.c_str(), sizeof(Blynk8266_WM_config.wifi_pw) - 1);
        }

        else if (key == "sv")
        {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.blynk_server) - 1)
            strcpy(Blynk8266_WM_config.blynk_server, value.c_str());
          else
            strncpy(Blynk8266_WM_config.blynk_server, value.c_str(), sizeof(Blynk8266_WM_config.blynk_server) - 1);
        }
        else if (key == "pt")
        {
          number_items_Updated++;
          Blynk8266_WM_config.blynk_port = value.toInt();
        }
        else if (key == "tk")
        {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.blynk_token) - 1)
            strcpy(Blynk8266_WM_config.blynk_token, value.c_str());
          else
            strncpy(Blynk8266_WM_config.blynk_token, value.c_str(), sizeof(Blynk8266_WM_config.blynk_token) - 1);
        }
        else if (key == "nm")
        {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.board_name) - 1)
            strcpy(Blynk8266_WM_config.board_name, value.c_str());
          else
            strncpy(Blynk8266_WM_config.board_name, value.c_str(), sizeof(Blynk8266_WM_config.board_name) - 1);
        }

        server->send(200, "text/html", "OK");

        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
        {
          //BLYNK_LOG1(BLYNK_F("hR: Update EEPROM"));
          BLYNK_LOG1(BLYNK_F("h:UpdFlash"));

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
      WiFi.init(wifi->getUart());
      WiFi.configAP(portal_apIP);

      if ( (portal_ssid == "") || portal_pass == "" )
      {
        String randomNum = String(random(0xFFFFFF), HEX);
        randomNum.toUpperCase();

        portal_ssid = "SAMD_" + randomNum;
        portal_pass = "MySAMD_" + randomNum;
      }

      BLYNK_LOG6(BLYNK_F("stConf:SSID="), portal_ssid, BLYNK_F(",PW="), portal_pass, BLYNK_F(",IP="), portal_apIP);

      // start access point, AP only, channel 10
      int AP_channel = 10;
      WiFi.beginAP(portal_ssid.c_str(), AP_channel, portal_pass.c_str(), ENC_TYPE_WPA2_PSK, true);

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
