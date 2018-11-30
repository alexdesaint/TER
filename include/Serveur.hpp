#ifndef Serveur_hpp
#define Serveur_hpp

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
//#include <ESP8266mDNS.h>
//#include <EEPROM.h>

class Serveur {
  const char* ssid = "TempsDeVol";
  const byte DNS_PORT = 53;
  DNSServer dnsServer;

public:
  String getPage();
  void test();
  void useServeur();
};

#endif /* end of include guard: Ecran_hpp */