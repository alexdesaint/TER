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
int tempsVol = 0;

std::list<std::array<uint32_t, 10>> data;

void boutonPress() { modeMesure.lancerMesure(); }

void laser1Change()
{
  if (digitalRead(D6))
  {
    if (modeMesure.absencePersonne())
    {
      data.push_back(modeMesure.getTabTemps());
      serveur.modifyMeasurements(data);
    }

    digitalWrite(D0, modeMesure.getIndicateur());
    //ecran.write(String(modeMesure.getLastValidFlyTime()/1000));
    tempsVol = modeMesure.getLastValidFlyTime() / 1000;
    cpt++;
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
  ecran.write("Saut " + String(cpt) + " " + String(tempsVol));
}
#endif

#ifdef MAIN2
// arduino lib
#include <Arduino.h>

// program include
#include "Ecran.hpp"
#include "ModeMesure.hpp"
#include "Serveur.hpp"

// std include
#include <array>
#include <list>
#include <cinttypes>

ModeMesure modeMesure;
Ecran ecran;
Serveur serveur;
int cpt = 0;
int tempsVol = 0;
bool mode;

std::list<std::array<uint32_t, 10>> data;

void boutonPress() { modeMesure.lancerMesure(); }

void laser1Change()
{
  if (digitalRead(D6))
  {
    modeMesure.absencePersonne();

    tempsVol = modeMesure.getTime() / 1000;
    /*cpt++;
    mode = true;*/
  }
  else
  {
    if (modeMesure.presencePersonne())
    {
      auto tabTemps = modeMesure.getTabTemps();
      String print;
      for (uint32 m : tabTemps)
      {
        print += String(m) + ", ";
      }
      data.push_back(tabTemps);
      Serial.println(print);
      serveur.modifyMeasurements(data);
      //mode = false;
    }
  }

  digitalWrite(D0, modeMesure.getIndicateur());
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
  ecran.write(String(tempsVol));

  /*if(mode == true)
    ecran.write(String(tempsVol));
  else
  {
    ecran.write("Saut "+String(cpt)+":\n" + String(tempsVol));
  }*/
}
#endif