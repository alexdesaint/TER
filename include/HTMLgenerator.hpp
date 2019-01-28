#ifndef HTMLgenerator_hpp
#define HTMLgenerator_hpp

#include <list>
#include <array>
#include <string>

// Besoins sinon problème de conversion en "String" + utilisé dans la class serveur
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>

class HTMLgenerator {
  public:
  static char str[10000];
    static char* getCode(std::list<std::array<uint32_t, 10>> temps);
};

#endif /* end of include guard: HTMLgenerator_hpp */
