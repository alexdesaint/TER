#ifndef Serveur_hpp
#define Serveur_hpp

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
//#include <EEPROM.h>
#include <WiFiClientSecure.h>

class Serveur {
  char* ssid;

  const char* ssid2 = "SFR_9098";
  const char* password = "75xssy3mrv26wgcv8vze";   

  const byte DNS_PORT = 53;
  DNSServer dnsServer;

  //void operator=(const Serveur &);

public:
  void InitServeur(String id);
  String getPage();
  void test();
  void useServeur();
};

#endif /* end of include guard: Ecran_hpp */