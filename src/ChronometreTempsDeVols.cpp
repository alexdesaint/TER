#include "ChronometreTempsDeVols.hpp"

#include <Arduino.h>
#include <user_interface.h>

uint32_t ChronometreTempsDeVols::getLastValidFlyTime() {
  return lastValidFlyTime;
}

std::array<uint32_t, 10> ChronometreTempsDeVols::getTabTemps() {
  return lastRecord;
}

int ChronometreTempsDeVols::getIndice() { return indiceTabTemps; }

void ChronometreTempsDeVols::lancerMesure() { modeMesure = true; }

bool ChronometreTempsDeVols::getIndicateur() { return indicateur; }

bool ChronometreTempsDeVols::absencePersonne() {
  uint32_t now = system_get_time();
  uint32_t elapsedTime = now - lastTime;
  lastTime = now;
  bool mesureValide = elapsedTime > seuilRebond, finMesure = false;

  if (mesureValide) { // si la dernière mesure est valide

    if (mesureSolValide && mesureVolValide) {
      mesureSolValide = false;
      mesureVolValide = false;
      indicateur = !indicateur;

      lastValidFlyTime = tabTemps[indiceTabTemps].getElapsedTime();

      if (modeMesure)
        indiceTabTemps++;

      if (indiceTabTemps == 10) { // fin des mesure : stokage et reset

        for (unsigned int i = 0; i < lastRecord.size(); i++)
          lastRecord[i] = tabTemps[i].getElapsedTime();

        modeMesure = false;
        indiceTabTemps = 0;
        finMesure = true;
      }
    }

    mesureSolValide = true;
    tabTemps[indiceTabTemps].tempsAbsence = now;

    Serial.println("Temps Sol Valide");
  } else {
    mesureVolValide = false;
  }

  return finMesure;
}

void ChronometreTempsDeVols::presencePersonne() {
  uint32_t now = system_get_time();
  uint32_t elapsedTime = now - lastTime;
  lastTime = now;

  // si le temps de vol est valide
  if (elapsedTime > seuilRebond) {
    tabTemps[indiceTabTemps].tempsPresence = now;
    mesureVolValide = true;

    Serial.println("Temps Vol Valide");
  }

  /*String print;
  for (Mesure m : tabTemps) {
    print += m.toString();
  }
  Serial.println(print);*/
}
