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

ChronometreTempsDeVols modeMesure(300);
Ecran ecran;
Serveur serveur;
uint32_t nbSaut = 0;
uint32_t tempsVol = 0;
uint32_t tempsTotal = 0;
bool enMesure = false;

std::list<std::array<uint32_t, 10>> data;

void boutonPress()
{
  modeMesure.lancerMesure();
  enMesure = true;
}

void laser1Change()
{
  if (digitalRead(D6))
  {
    if (modeMesure.absencePersonne())
    {
      enMesure = false;
      auto tabTemps = modeMesure.getTabTemps();

      tempsTotal = 0;

      for (uint32_t i : tabTemps)
        tempsTotal += i;

      data.push_back(tabTemps);

      serveur.modifyMeasurements(data);
    }

    digitalWrite(D0, modeMesure.getIndicateur());
    tempsVol = modeMesure.getTime();
    nbSaut = modeMesure.getIndice();
  }
  else
  {
    modeMesure.presencePersonne();
  }
}

void setup()
{
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

void loop()
{
  serveur.useServeur();
  if (enMesure)
    ecran.write("Saut " + String(nbSaut + 1) + "\n" + String(tempsVol / 1000000.f));
  else
    ecran.write("Points " + String(tempsTotal / 1000000.f) + "\n" + String(tempsVol / 1000000.f) + "s");
}

#endif

#ifdef MAIN2
// arduino lib
#include <Arduino.h>

// program include
#include "Ecran.hpp"
#include "ModeMesure.hpp"
#include "Serveur.hpp"
#include "TableauDesMesures.hpp"

ModeMesure modeMesure;
Ecran ecran;
Serveur serveur;
int nbSaut = 0;
int tempsVol = 0;
int tempsTotal = 0;
bool enMesure = false;

bool presensePersonne = false;
bool c1 = true, c2 = true, c3 = true;

TableauDesMesures rwtab;

void boutonPress()
{
  modeMesure.lancerMesure();
  enMesure = true;
}

void traitementCapteur() {
  if((!c1 || !c2 || !c3) && !presensePersonne) {
    if (modeMesure.presencePersonne())
    {
      enMesure = false;
      auto tabTemps = modeMesure.getTabTemps();

      tempsTotal = 0;

      for (uint32_t i : tabTemps)
        tempsTotal += i;

      rwtab.remplirTableau(tabTemps);
      rwtab.writeAll();

      serveur.modifyMeasurements(rwtab.getTab());
    }
    Serial.println("PP");
    presensePersonne = true;
  }

  if(c1 && c2 && c3 && presensePersonne) {
    Serial.println("AP");
    modeMesure.absencePersonne();
    presensePersonne = false;
  }
}

void laser1Change()
{
  if (digitalRead(D6)) {
    c1 = true;
    traitementCapteur();
    Serial.println("l1 t");
  }  
  else {
    c1 = false;
    traitementCapteur();
    Serial.println("l1 f");
  }
    

  digitalWrite(D0, modeMesure.getIndicateur());
  tempsVol = modeMesure.getTime();
  nbSaut = modeMesure.getIndice();
}

void laser2Change()
{
  if (digitalRead(D7)) {
    c2 = true;
    traitementCapteur();
    Serial.println("l2 t");
  }  
  else {
    c2 = false;
    traitementCapteur();
    Serial.println("l2 f");
  }
    

  digitalWrite(D0, modeMesure.getIndicateur());
  tempsVol = modeMesure.getTime();
  nbSaut = modeMesure.getIndice();
}

void laser3Change()
{
  if (digitalRead(D8)) {
    c3 = true;
    traitementCapteur();
    Serial.println("l3 t");
  }  
  else {
    c3 = false;
    traitementCapteur();
    Serial.println("l3 f");
  }
    

  digitalWrite(D0, modeMesure.getIndicateur());
  tempsVol = modeMesure.getTime();
  nbSaut = modeMesure.getIndice();
}

void setup()
{
  // system init
  Serial.begin(9600);
  ecran.init();
  serveur.InitServeur("TempsDeVol");
  rwtab.readAll();
  serveur.modifyMeasurements(rwtab.getTab());

  // LED
  pinMode(D0, OUTPUT);

  // Interruption bouton
  pinMode(D5, INPUT);
  attachInterrupt(digitalPinToInterrupt(D5), boutonPress, FALLING);

  // Interruption laser
  pinMode(D6, INPUT);
  attachInterrupt(digitalPinToInterrupt(D6), laser1Change, CHANGE);

  pinMode(D7, INPUT);
  attachInterrupt(digitalPinToInterrupt(D7), laser2Change, CHANGE);

  pinMode(D8, INPUT);
  attachInterrupt(digitalPinToInterrupt(D8), laser3Change, CHANGE);
}

void loop()
{
  serveur.useServeur();
  if (enMesure){
    if(nbSaut == 0)
      ecran.write("Saut 1");
    else
      ecran.write("Saut " + String(nbSaut) + "\n" + String(tempsVol / 1000000.f));
  }else
    ecran.write("Score " + String(tempsTotal / 1000000.f) + "\n" + String(tempsVol / 1000000.f) + "s");
}

#endif