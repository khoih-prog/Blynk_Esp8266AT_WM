/****************************************************************************************************************************
 * BlynkSimpleShieldEsp8266_WM.h
 * For Teensy boards using ESP8266 WiFi Shields
 *
 * BlynkSimpleShieldEsp8266_WM is a library for the Mega and Teensy boards (https://github.com/esp8266/Arduino)
 * to enable easy configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
 * 
 * Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
 * Licensed under MIT license
 * Version: 1.0.0
 *
 * Original Blynk Library author:
 * @file       BlynkSimpleShieldEsp8266.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jun 2015
 * @brief
 *
 * Version Modified By   Date      Comments
 * ------- -----------  ---------- -----------
 *  1.0.0   K Hoang      28/10/2019 Initial coding
 *****************************************************************************************************************************/

#ifndef BlynkSimpleShieldEsp8266_WM_h
#define BlynkSimpleShieldEsp8266_WM_h

#if ( defined(ESP8266) || defined(ESP32) || defined(CORE_TEENSY) )
#error This code is not intended to run on the ESP8266, ESP32 nor Teensy platform! Please check your Tools->Board setting.
#endif

#if !( defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA) )
#error This code is intended to run on the Mega2560 platform! Please check your Tools->Board setting.
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

//#include <ESP8266WebServer.h>
#include <ESP8266_AT_WebServer.h>
#include <EEPROM.h>

#define SIMPLE_SHIELD_ESP8266_DEBUG       1

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    5
typedef struct Configuration 
{
    char header         [16];
    char wifi_ssid      [32];
    char wifi_pw        [32];
    char blynk_server   [32];
    int  blynk_port;
    char blynk_token    [36];
} Blynk_WF_Configuration;

// Currently CONFIG_DATA_SIZE  =   152
uint16_t CONFIG_DATA_SIZE = sizeof(Blynk_WF_Configuration);

#define root_html_template " \
<!DOCTYPE html> \
<meta name=\"robots\" content=\"noindex\"> \
<html> \
<head> \
<meta charset=\"utf-8\"> \
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \
<title>AVR_WM</title> \
</head> \
<body> \
<div align=\"center\"> \
<table> \
<tbody> \
<tr> \
<th colspan=\"2\">WiFi</th> \
</tr> \
<tr> \
<td>SSID</td> \
<td><input type=\"text\" value=\"[[wf_id]]\" id=\"wf_id\"></td> \
</tr> \
<tr> \
<td>Password</td> \
<td><input type=\"text\" value=\"[[wf_pw]]\" id=\"wf_pw\"></td> \
</tr> \
<tr> \
<th colspan=\"2\">Blynk</th> \
</tr> \
<tr> \
<td>Server</td> \
<td><input type=\"text\" value=\"[[b_svr]]\" id=\"b_svr\"></td> \
</tr> \
<tr> \
<td>Port</td> \
<td><input type=\"text\" value=\"[[b_pt]]\" id=\"b_pt\"></td> \
</tr> \
<tr> \
<td>Token</td> \
<td><input type=\"text\" value=\"[[b_tok]]\" id=\"b_tok\"></td> \
</tr> \
<tr> \
<td colspan=\"2\" align=\"center\"> \
<button onclick=\"save()\">Save</button> \
</td> \
</tr> \
</tbody> \
</table> \
</div> \
<script id=\"jsbin-javascript\"> \
function udVal(key, value) { \
var request = new XMLHttpRequest(); \
var url = '/?key=' + key + '&value=' + value; \
console.log('call ' + url + '...'); \
request.open('GET', url, false); \
request.send(null); \
} \
function save() { \
udVal('wf_id', document.getElementById('wf_id').value); \
udVal('wf_pw', document.getElementById('wf_pw').value); \
udVal('b_svr', document.getElementById('b_svr').value); \
udVal('b_pt', document.getElementById('b_pt').value); \
udVal('b_tok', document.getElementById('b_tok').value); \
alert('Updated. Reset'); \
} \
</script> \
</body> \
</html>"

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
            BLYNK_LOG4("Got: ", len, ", Free: ", buffer.free());
          #endif
          BLYNK_LOG1(BLYNK_F("Buf OVF"));
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
          BLYNK_LOG2(BLYNK_F("onData Buflen "), len );
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
          BLYNK_LOG4("read: Datalen: ", len, " Buf: ", buffer.size());
        #endif
        
        while ((buffer.size() < len) && (BlynkMillis() - start < 1500)) 
        {
            // Actually call ESP8266 run/rx_empty (read and locate +IPD, know data len, 
            // then call onData() to get len bytes of data to buffer => BlynkProtocol::ProcessInput()
            client->run();
        }
        //KH Mod
        #if 0
        // Check to see if got sequence [14|0D|0A]+IPD,<id>,<len>:<data> => discard until end of <data>
        
        /*static*/ uint8_t tempBuff[128];
        if (len < sizeof(tempBuff))
        {
          buffer.get(tempBuff, len);
          //tempBuff[len] = 0;
        }
        
        char testString1[5] = { 0x0D, 0x0A, '+', 'I', 0};
        char testString2[6] = { '+', 'I', 'P', 'D', ',', 0 };
        char testString3[3] = { 'P', 'D', 0 };
        char testString4[3] = { 0x0D, 0x0A, 0 };
        
        /*static*/ uint8_t localBuff[128];
        /*static*/ unsigned int localLength;
        /*static*/ unsigned int copyLength;
        
        /*+IPD,<id>,<len>:<data>*/
        if ( strstr((char*) tempBuff, testString1) /*|| strstr((char*) tempBuff, testString2) || strstr((char*) tempBuff, testString3)*/ )
        {
          //Got +I, next => PD,<id>,<len>:<data>
          //                012  3 4  5  6  7
          BLYNK_LOG2("read: Bad sequence a ", (char*) tempBuff);
          // Read and discard more
          if (buffer.size() < sizeof(tempBuff))
          {
            buffer.get(tempBuff, buffer.size());
            
            if ( (tempBuff[0] == 'P') && (tempBuff[1] == 'D') && (tempBuff[2] == ',') /*&& (tempBuff[3] == '1') && (tempBuff[4] == ',')*/ )
            {
              BLYNK_LOG2("read: Bad sequence2 ", (char*) tempBuff);
              localLength = tempBuff[5];
              copyLength = localLength < sizeof(localBuff)? localLength : sizeof(localBuff);
              memcpy(localBuff, tempBuff + 7, copyLength );
              memcpy(tempBuff, localBuff, copyLength);
              BLYNK_LOG2("read: Bad sequence3 ", (char*) tempBuff);
              return copyLength;
            }
          }
          
          return 0;
        }
        else if ( strstr((char*) tempBuff, testString2) /*|| strstr((char*) tempBuff, testString3)*/ )
        {
          //Got +IPD, next => <id>,<len>:<data>
          //                    0 1  2  3  4
          BLYNK_LOG2("read: Bad sequence b ", (char*) tempBuff);
          // Read and discard more
          if (buffer.size() < sizeof(tempBuff))
          {
            buffer.get(tempBuff, buffer.size());
            
            if ( (tempBuff[1] == ',') && (tempBuff[3] == ':') )
            {
              BLYNK_LOG2("read: Bad sequence4 ", (char*) tempBuff);
              localLength = tempBuff[2];
              copyLength = localLength < sizeof(localBuff)? localLength : sizeof(localBuff);
              memcpy(localBuff, tempBuff + 4, copyLength );
              memcpy(tempBuff, localBuff, copyLength);
              BLYNK_LOG2("read: Bad sequence5 ", (char*) tempBuff);
              return copyLength;
            }
          }
          
          return 0;
        }     
        else if ( strstr((char*) tempBuff, testString4) /*|| strstr((char*) tempBuff, testString3)*/ )
        {
          //Got X X X 0x0D, 0x0A, next +IPD, just discard this 5 bytes
          //    0 1 2  3     4
          BLYNK_LOG2("read: Bad sequence c ", (char*) tempBuff);
          // Read and discard more
          if (buffer.size() < sizeof(tempBuff))
          {
            buffer.get(tempBuff, buffer.size());
            
            //if ( (tempBuff[1] == ',') && (tempBuff[3] == ':') )
            {
              //BLYNK_LOG2("read: Bad sequence4 ", (char*) tempBuff);
              //localLength = tempBuff[2];
              //copyLength = localLength < sizeof(localBuff)? localLength : sizeof(localBuff);
              memcpy(localBuff, tempBuff + 5, sizeof(tempBuff) - 5 );
              memcpy(tempBuff, localBuff, sizeof(tempBuff) - 5);
              BLYNK_LOG2("read: Bad sequence5 ", (char*) tempBuff);
              return 0;
            }
          }
          
          return 0;
        }                
        else
        {
          memcpy(buf, tempBuff, len);
          return len;
        }
        
        #else
        //All data got in FIFO buffer, copy to destination buf and return len
        return buffer.get((uint8_t*)buf, len);
        #endif
    }
    
    size_t write(const void* buf, size_t len) {
        if (client->send(BLYNK_ESP8266_MUX, (const uint8_t*)buf, len)) {
            return len;
        }
        return 0;
    }

    bool connected() { return status; }

    int available() 
    {
        client->run();
        #if (SIMPLE_SHIELD_ESP8266_DEBUG > 2)
          BLYNK_LOG2("Still: ", buffer.size());
        #endif
        return buffer.size();
    }

private:
    ESP8266* client;
    bool status;
    
    //KH   
    #if ( defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA) )
      // For other AVR Mega
      BlynkFifo<uint8_t,256> buffer;
      #warning Mega board => uses 256bytes FIFO buffer    
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
             BLYNK_LOG1(BLYNK_F("ESP not responding"));
             //TODO: BLYNK_LOG_TROUBLE(BLYNK_F("esp8266-not-responding"));
             return false;
        }
        if (!wifi->setEcho(0)) 
        {
            BLYNK_LOG1(BLYNK_F("Fail Echo"));
            return false;
        }
        
        String ver = wifi->ESP8266::getVersion();
        BLYNK_LOG1(ver);
                   
        // KH
        BlynkDelay(500);
        
        if (!wifi->enableMUX()) 
        {
            BLYNK_LOG1(BLYNK_F("Fail MUX"));
            return false;
        }
        
        if (!wifi->setOprToStation()) 
        {
            BLYNK_LOG1(BLYNK_F("Fail STA mode"));
            return false;
        }
                      
        return true;
    }
    
    bool connectWiFi(const char* ssid, const char* pass)
    {
        BLYNK_LOG2(BLYNK_F("Con2 "), ssid);
        
        WiFiInit();
   
        // In STA mode, get and store unique macAddress for later use
        if (macAddress.length() == 0)
        {          
          macAddress = wifi->getStationMac();
          macAddress.replace("+CIPSTAMAC:\"", "");
          macAddress.replace("\"", "");
          BLYNK_LOG2(BLYNK_F("Mac = "), macAddress);     
        }
                
        if (wifi->joinAP(ssid, pass)) 
        {
            displayWiFiData();
        } 
        else 
        {
            BLYNK_LOG1(BLYNK_F("Fail WiFi"));
            return false;
        }
        
        BLYNK_LOG1(BLYNK_F("WiFi OK"));
        
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
        while(this->connect() != true) {}
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
    
        #if 0
        if (iHostname[0] == 0)
				{
				  String _hostname = "ESP8266-" + macAddress;

					_hostname.toUpperCase();

					getRFC952_hostname(_hostname.c_str());		
					
				}
				else
				{
					// Prepare and store the hostname only not NULL
					getRFC952_hostname(iHostname);
				}
				
				BLYNK_LOG2(BLYNK_F("RFC925 Hostname = "), RFC952_hostname);
				
				#endif
				        
        if (getConfigData())
        {
          hadConfigData = true;
          
          config(esp8266, Blynk8266_WM_config.blynk_token, Blynk8266_WM_config.blynk_server, Blynk8266_WM_config.blynk_port);

          if (connectToWifi(TIMEOUT_CONNECT_WIFI)) 
          {
            BLYNK_LOG1(BLYNK_F("bg: W OK. Try B"));
            
            int i = 0;
            while ( (i++ < 10) && !this->connect() )
            {
            }
            
            if  (connected())
            {
              BLYNK_LOG1(BLYNK_F("bg: W+B OK"));
            }
            else 
            {
              BLYNK_LOG1(BLYNK_F("bg: W OK, B not"));
              // failed to connect to Blynk server, will start configuration mode
              startConfigurationMode();
            }
          } 
          else 
          {
              BLYNK_LOG1(BLYNK_F("bg: Fail W+B"));
              // failed to connect to Blynk server, will start configuration mode       
              startConfigurationMode();
          }   
        }
        else
        {
            BLYNK_LOG1(BLYNK_F("bg: No configdat. Stay in Portal"));
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
		          BLYNK_LOG2(BLYNK_F("run: W lost & config T-Out. Connect W+B. Retry# : "), retryTimes);
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
				    BLYNK_LOG1(BLYNK_F("run: W lost. Reconnect W+B"));
				    if (connectToWifi(TIMEOUT_RECONNECT_WIFI)) 
				    {             
				      BLYNK_LOG1(BLYNK_F("run: W OK. Try B"));
				      
				      if (connect())
				      {
					      BLYNK_LOG1(BLYNK_F("run: W+BB OK"));
					    }
				    }
			    }
			    else
			    {
				    BLYNK_LOG1(BLYNK_F("run: B lost. Try B"));
				    if (connect()) 
				    {
					    BLYNK_LOG1(BLYNK_F("run: B OK"));
				    }
			    }
					
			    //BLYNK_LOG1(BLYNK_F("run: Lost connection => configMode"));
			    //startConfigurationMode();
        }
      }
      else if (configuration_mode)
      {
      	configuration_mode = false;
      	BLYNK_LOG1(BLYNK_F("run: got W+B back"));
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
    
    void resetFunc()
    {
      asm volatile ("  jmp 0");
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
    boolean wifi_connected = false;
    
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

		#define RFC952_HOSTNAME_MAXLEN      24
		char RFC952_hostname[RFC952_HOSTNAME_MAXLEN + 1];

		char* getRFC952_hostname(const char* iHostname)
		{ 
			memset(RFC952_hostname, 0, sizeof(RFC952_hostname));
			
			size_t len = ( RFC952_HOSTNAME_MAXLEN < strlen(iHostname) ) ? RFC952_HOSTNAME_MAXLEN : strlen(iHostname);
			
			size_t j = 0;
			
			for (size_t i = 0; i < len - 1; i++)
			{
				if ( isalnum(iHostname[i]) || iHostname[i] == '-' )
				{
				  RFC952_hostname[j] = iHostname[i];
				  j++;
				}  
			}
			// no '-' as last char
			if ( isalnum(iHostname[len - 1]) || (iHostname[len - 1] != '-') )
				RFC952_hostname[j] = iHostname[len - 1];

			return RFC952_hostname;
		}
    
		void displayConfigData(void)
		{
		    BLYNK_LOG6(BLYNK_F("Hdr = "), Blynk8266_WM_config.header, BLYNK_F(", SSID = "), Blynk8266_WM_config.wifi_ssid, 
                   BLYNK_F(", PW = "),   Blynk8266_WM_config.wifi_pw);
        BLYNK_LOG6(BLYNK_F("Svr = "), Blynk8266_WM_config.blynk_server, BLYNK_F(", Port = "), Blynk8266_WM_config.blynk_port, 
                   BLYNK_F(", Tok = "),  Blynk8266_WM_config.blynk_token);     
		}  
		
    void displayWiFiData(void)
		{
        BLYNK_LOG2(BLYNK_F("IP = "), getLocalIP());
    }
    
    
#define BLYNK_BOARD_TYPE   "SHD_ESP8266"
#define NO_CONFIG           "nothing"



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
  #define EEPROM_START     0
#else
  #if (EEPROM_START + CONFIG_DATA_SIZE > EEPROM_SIZE)
    #error EPROM_START + CONFIG_DATA_SIZE > EEPROM_SIZE. Please adjust.
  #endif
#endif
              
    bool getConfigData()
    {
      EEPROM.get(EEPROM_START, Blynk8266_WM_config);

      if (strncmp(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE, strlen(BLYNK_BOARD_TYPE)) != 0) 
      {
          memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
          
          EEPROM.put(EEPROM_START, Blynk8266_WM_config);
                                   
          BLYNK_LOG2(BLYNK_F("Init EEPROM sz="), EEPROM.length());          
          // doesn't have any configuration
          strcpy(Blynk8266_WM_config.header,           BLYNK_BOARD_TYPE);
          strcpy(Blynk8266_WM_config.wifi_ssid,        NO_CONFIG);
          strcpy(Blynk8266_WM_config.wifi_pw,          NO_CONFIG);
          strcpy(Blynk8266_WM_config.blynk_server,     NO_CONFIG);
          Blynk8266_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
          strcpy(Blynk8266_WM_config.blynk_token,      NO_CONFIG);

          EEPROM.put(EEPROM_START, Blynk8266_WM_config);

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
      BLYNK_LOG2(BLYNK_F("Save EEPROM, size = "), EEPROM.length());
      EEPROM.put(EEPROM_START, Blynk8266_WM_config);
    }
		
    boolean connectToWifi(int timeout)
    {
      int sleep_time = 250;

	    BLYNK_LOG1(BLYNK_F("con2WF: start"));
	    
	    // New from Blynk_WM v1.0.5
      if (static_IP != IPAddress(0, 0, 0, 0))
      {
        BLYNK_LOG1(BLYNK_F("Use static IP"));
        wifi->setStationIp(IPAddressToString(static_IP), IPAddressToString(static_GW), IPAddressToString(static_SN));       
      }
	
      while ( !wifi_connected && ( 0 < timeout ) )
      {
          BLYNK_LOG1(BLYNK_F("con2W: Try con2W"));
          
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
		    BLYNK_LOG1(BLYNK_F("con2W: OK"));
		    displayWiFiData();
		  }
	    else
	    {
		    BLYNK_LOG1(BLYNK_F("con2W: fail"));
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

            BLYNK_LOG1(BLYNK_F("hR: repl result"));
            
            // Reset configTimeout to stay here until finished.
            configTimeout = 0;

            result.replace("[[wf_id]]",     Blynk8266_WM_config.wifi_ssid);
            result.replace("[[wf_pw]]",     Blynk8266_WM_config.wifi_pw);
            result.replace("[[b_svr]]",     Blynk8266_WM_config.blynk_server);
            result.replace("[[b_pt]]",      String(Blynk8266_WM_config.blynk_port));
            result.replace("[[b_tok]]",     Blynk8266_WM_config.blynk_token);

            server->send(200, "text/html", result);
            BLYNK_LOG1(BLYNK_F("hR: sent"));

            return;
        }
        
        if (number_items_Updated == 0)
        {
          memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
          strcpy(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE);
        }
        
        if (key == "wf_id")
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.wifi_ssid) -1)
              strcpy(Blynk8266_WM_config.wifi_ssid, value.c_str());
            else
              strncpy(Blynk8266_WM_config.wifi_ssid, value.c_str(), sizeof(Blynk8266_WM_config.wifi_ssid) -1);    
        }
        else if (key == "wf_pw") 
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.wifi_pw) -1)
              strcpy(Blynk8266_WM_config.wifi_pw, value.c_str());
            else
              strncpy(Blynk8266_WM_config.wifi_pw, value.c_str(), sizeof(Blynk8266_WM_config.wifi_pw) -1);    
        }

        else if (key == "b_svr") 
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.blynk_server) -1)
              strcpy(Blynk8266_WM_config.blynk_server, value.c_str());
            else
              strncpy(Blynk8266_WM_config.blynk_server, value.c_str(), sizeof(Blynk8266_WM_config.blynk_server) -1);      
        }
        else if (key == "b_pt") 
        {
            number_items_Updated++;
            Blynk8266_WM_config.blynk_port = value.toInt();
        }
        else if (key == "b_tok") 
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.blynk_token) -1)
              strcpy(Blynk8266_WM_config.blynk_token, value.c_str());
            else
              strncpy(Blynk8266_WM_config.blynk_token, value.c_str(), sizeof(Blynk8266_WM_config.blynk_token) -1);    
        }

        server->send(200, "text/html", "OK");
        
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
        {
          BLYNK_LOG1(BLYNK_F("hR: Upd EEPROM"));

          saveConfigData();

          BLYNK_LOG1(BLYNK_F("hR: Rst"));
          
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
        
        portal_ssid = "Mega_" + randomNum;
        portal_pass = "MyMega_" + randomNum;
      }
           	    
      BLYNK_LOG6(BLYNK_F("stConf: SSID = "), portal_ssid, BLYNK_F(", PW = "), portal_pass, BLYNK_F(", IP = "), portal_apIP);

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
        server->on("/", [this](){ handleRequest(); });
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
