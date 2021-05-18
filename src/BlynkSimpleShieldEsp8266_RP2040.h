/****************************************************************************************************************************
  BlynkSimpleShieldEsp8266_RP2040.h
  For ESP8266 AT-command shields

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

  Version: 1.3.0

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
 *****************************************************************************************************************************/

#ifndef BlynkSimpleShieldEsp8266_RP2040_h
#define BlynkSimpleShieldEsp8266_RP2040_h

#if ( defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || defined(ARDUINO_GENERIC_RP2040) )
  #if defined(BLYNK_ESP8266_AT_USE_RP2040)
    #undef BLYNK_ESP8266_AT_USE_RP2040
  #endif
  #define BLYNK_ESP8266_AT_USE_RP2040      true
  #warning Use RP2040 architecture from Blynk_Esp8266AT_WM
#else
  #error This code is intended to run only on the RP2040-based boards ! Please check your Tools->Board setting.
#endif

#define BLYNK_ESP8266AT_WM_VERSION    "Blynk_Esp8266AT_WM v1.3.0"

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
#elif defined(ARDUINO_ARCH_MBED)
  #define BLYNK_INFO_DEVICE   "MBED RP2040"
#else
  #define BLYNK_INFO_DEVICE   "RP2040"
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

#define SIMPLE_SHIELD_ESP8266_DEBUG       0

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
#if (BLYNK_ESP8266_AT_USE_RP2040)
    // For all RP2040
    BlynkFifo<uint8_t, 4096> buffer;
#warning Board RP2040 uses 4k FIFO buffer
#else
    // For other unknown RP2040
    //BlynkFifo<uint8_t,256> buffer;
    BlynkFifo<uint8_t, 512> buffer;
#warning Not known RP2040 board => uses 512bytes FIFO buffer
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
  
    //////////////////////////////////////////////
    
    BlynkWifi(BlynkTransportShieldEsp8266& transp)
      : Base(transp)
      , wifi(NULL)
    {}
    
    //////////////////////////////////////////////

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
    
    //////////////////////////////////////////////

    bool connectWiFi(const char* ssid, const char* pass)
    {
      BLYNK_LOG2(BLYNK_F("Con2:"), ssid);

      WiFiInit();

      if (wifi->joinAP(ssid, pass))
      {
        getLocalIP();
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("FailW"));
        return false;
      }

      BLYNK_LOG1(BLYNK_F("WOK"));

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
      connectWiFi(ssid, pass);
      while (this->connect() != true) {}
    }
    
    //////////////////////////////////////////////

  String getLocalIP(void)
    {
      // Check to use getStationIp()
#if 1
      ipAddress = wifi->getStationIp();
#else
      ipAddress = wifi->getLocalIP().replace("+CIFSR:STAIP,\"", "");
      ipAddress = ipAddress.replace("\"", "");

#endif

      BLYNK_LOG2(BLYNK_F("IP = "), ipAddress);
      return ipAddress;
    }
    
    //////////////////////////////////////////////

  private:
    ESP8266* wifi;
    String ipAddress = "0.0.0.0";
};

//////////////////////////////////////////////

static BlynkTransportShieldEsp8266 _blynkTransport;
BlynkWifi Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif    //BlynkSimpleShieldEsp8266_RP2040_h
