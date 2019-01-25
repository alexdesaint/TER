#ifndef ChronometreTempsDeVols_hpp
#define ChronometreTempsDeVols_hpp

#include <array>
#include <cinttypes>

#include <Arduino.h>

typedef struct Mesure_T {
  uint32_t tempsAbsence = 0;
  uint32_t tempsPresence = 0;

  uint32_t getElapsedTime() { return tempsPresence - tempsAbsence; }

  void reset() {
    tempsAbsence = 0;
    tempsPresence = 0;
  }

  String toString() {
    return "[" + String(tempsAbsence / 1000000.f) + ": " +
           String(tempsPresence / 1000000.f) + "]";
  }
} Mesure;

class ChronometreTempsDeVols {
private:
  // Seuil pour le rebond
  uint32_t seuilRebond = 100000;

  uint32_t lastTime = 0, lastValidFlyTime = 0;

  bool modeMesure = false;

  bool indicateur = false;

  bool mesureVolValide = false, mesureSolValide;

  std::array<Mesure, 10> tabTemps;

  std::array<uint32_t, 10> lastRecord;

  int indiceTabTemps = 0;

public:
  uint32_t getLastValidFlyTime();

  std::array<uint32_t, 10> getTabTemps();

  int getIndice();

  bool getIndicateur();

  bool absencePersonne();

  void presencePersonne();

  void lancerMesure();
};

#endif
