#ifdef MAIN
// arduino lib
#include <Arduino.h>

// program include
#include "Ecran.hpp"
#include "ChronometreTempsDeVols.hpp"
#include "Serveur.hpp"

// std include
#include <array>
#include <list> 
#include <cinttypes>

ChronometreTempsDeVols modeMesure;
Ecran ecran;
Serveur serveur;
int cpt = 0;
int tempsVol=0;

std::list<std::array<uint32_t, 10>> data;

void boutonPress() { modeMesure.lancerMesure(); }

void laser1Change() {
  if (digitalRead(D6)) {
    if(modeMesure.absencePersonne()) {
      data.push_back(modeMesure.getTabTemps());
      serveur.modifyMeasurements(data);
    }
    
    digitalWrite(D0, modeMesure.getIndicateur());
    //ecran.write(String(modeMesure.getLastValidFlyTime()/1000));
    tempsVol = modeMesure.getLastValidFlyTime()/1000;
    cpt++;
  } else {
    modeMesure.presencePersonne();
  } 
}

void setup() {
  // system init
  Serial.begin(9600);
  ecran.init();
  serveur.InitServeur("TempsDeVol");
  serveur.modifyMeasurements(data);
  ecran.write("début");

  // LED
  pinMode(D0, OUTPUT);

  // Interruption bouton
  pinMode(D5, INPUT);
  attachInterrupt(digitalPinToInterrupt(D5), boutonPress, FALLING);

  // Interruption laser
  pinMode(D6, INPUT);
  attachInterrupt(digitalPinToInterrupt(D6), laser1Change, CHANGE);
  
}

void loop() {
  serveur.useServeur();
  ecran.write("Saut "+ String(cpt) + " " + String(tempsVol));
}
#endif