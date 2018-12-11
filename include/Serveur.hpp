#ifndef Serveur_hpp
#define Serveur_hpp

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
//#include <EEPROM.h>
//#include <WiFiClientSecure.h>

#include "pageWebVide.hpp"
#include "HTMLgenerator.hpp"


class Serveur {
  char* ssid;
  int cpt = 0;
  //String page = MAIN_page_vide;

  const byte DNS_PORT = 53;
  DNSServer dnsServer;

  //void operator=(const Serveur &);

public:
  int getCpt();
  void InitServeur(String id);
  void modifyMeasurements(std::list<std::array<uint32_t, 10>> temps);
  void useServeur();
};

#endif /* end of include guard: Ecran_hpp */