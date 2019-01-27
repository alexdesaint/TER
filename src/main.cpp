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

TableauDesMesures rwtab;

void boutonPress()
{
  modeMesure.lancerMesure();
  enMesure = true;
}

void laser1Change()
{
  if (digitalRead(D6))
  {
    modeMesure.absencePersonne();
  }
  else
  {
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