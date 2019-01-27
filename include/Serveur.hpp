#ifndef Serveur_hpp
#define Serveur_hpp

#include <Arduino.h>
#include <array>
#include <list> 

class Serveur {
  const char* ssid;
  const byte DNS_PORT = 53;

public:
  void InitServeur(String id);
  void modifyMeasurements(std::list<std::array<uint32_t, 10>> temps);
  void useServeur();
};

#endif /* end of include guard: Ecran_hpp */