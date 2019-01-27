#include <Arduino.h>

/******************************* test Serial *******************************/
#ifdef testSerial

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello World!");
}

void loop()
{
}

#endif

/******************************* test ecran *******************************/
#ifdef testEcran

#include "Ecran.hpp"

void setup()
{
  Serial.begin(9600);
  Ecran e;
  e.test();
}

void loop()
{
}
#endif

/******************************* test serveur *******************************/
#ifdef testServeur

#include "Serveur.hpp"

Serveur s;

void setup()
{
  std::list<std::array<uint32_t, 10>> dataTest = {{10, 10, 10, 10, 10, 70, 70, 70, 70, 70}};

  Serial.begin(9600);
  s.InitServeur("tempsDeVol");
  s.modifyMeasurements(dataTest);
}

void loop()
{
  s.useServeur();
}
#endif

/*********************** test Scann I2C *************************/
#ifdef testI2Cscann

#include <Wire.h>        // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#include "Ecran.hpp"

Ecran e;
void setup()
{
  Serial.begin(9600);
  e.init();
  e.scanI2C();
}

void loop()
{
  e.init();
  e.scanI2C();
  // clear ecran
  e.clear();

  // test de l'ecran
  e.test();
  delay(5000); // attente de 5sec

  // ecriture du string
  e.clear();
  e.write("alex t moch");
  delay(5000);
}
#endif

/*********************** test LED *************************/
#ifdef testLED

void setup()
{
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
}

void loop()
{
  digitalWrite(D0, HIGH);
  delay(1000);
  digitalWrite(D0, LOW);
  delay(1000);
}

#endif

/******************************* test Bouton *******************************/
#ifdef testBouton

bool boutonOld;
unsigned int num = 0;

void ISR()
{
  Serial.println("Press");
}

void setup()
{
  Serial.begin(9600);
  pinMode(D5, INPUT);
  attachInterrupt(digitalPinToInterrupt(D5), ISR, FALLING);
}

void loop()
{
}
#endif

/******************************* test capteur *******************************/
#ifdef testCapteur

void setup()
{
  Serial.begin(9600);
  pinMode(D6, INPUT);
  pinMode(D8, INPUT);
}

void loop()
{
  int capt1 = digitalRead(D6);
  int capt2 = digitalRead(D8);
  if (capt1 > 0)
    Serial.println("D6");
  else
    Serial.println("\n");
  if (capt2 > 0)
    Serial.println("D8");
  else
    Serial.println("\n");
}
#endif

/******************************* test integration façon machine a etat 1 *******************************/
//le chrono devant fonctionner en continu, ça marche pas
#ifdef testIntegration1

//serveur
#include "Serveur.hpp"
Serveur s;

//chrono
#include "ModeMesure.hpp"
#include <Wire.h>    //We need the wire library for the I2C display
#define OLED_RESET 4 //display reset is on digital 4 but not used

#include <cinttypes>
#include <array>

bool capteurLaser, bouton;
ModeMesure modemesure;

//a quoi sert ses 2 variable?
bool boolBouton, boolCapteur;

int capt1, capt2;

int i;

//machine a etat
int etat = 0;

//variable front laser
//bool capteurLaserPrec;
//int compteurFront;

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello World!\n");

  s.InitServeur("tempsDeVol");

  modemesure.init();
  boolBouton = false;
  boolCapteur = false;
  capt1 = 0;
  capt2 = 0;
  pinMode(D6, INPUT);
  pinMode(D8, INPUT);
}

void loop()
{

  switch (etat)
  {
  case 0:
    s.useServeur();

    //detection capteur façon momo
    /*if(digitalRead(D6)>0) 
      bouton=true ;
    else 
      bouton = false ;

    if(bouton == true){*/
    if (digitalRead(D6) > 0)
    {
      etat = 1;
      //capteurLaserPrec = false;
      //compteurFront=0;
    }
    break;

  case 1:

    //Detection bouton pour capt1 et detection presence personne capt2
    capt1 = digitalRead(D6);
    capt2 = digitalRead(D8);
    if (capt1 > 0)
      bouton = true;
    else
      bouton = false;

    if (capt2 > 0)
    {
      capteurLaser = true;
      //Serial.println(modemesure.getIndice());

      if (modemesure.getIndice() >= 10)
      { //nbr de saut

        std::array<uint64_t, 10> tab = modemesure.getTabTemps();

        for (int i = 0; i < modemesure.getIndice(); i++)
        {
          int p = (int)tab[i];
          Serial.println(p);
        }

        Serial.println("\n");
        //s.modifyMeasurements(tab);
        modemesure.cleanTab();

        etat = 0;
      }
    }
    else
      capteurLaser = false;

    if (bouton == true)
    {
      modemesure.lancerMesure();
    }

    if (capteurLaser == true)
    {
      boolBouton = modemesure.presencePersonne();
    }

    if (capteurLaser == false)
    {
      modemesure.absencePersonne();
    }

    //partie front mais on ne va pas l'utiliser et garder la partie de momo sans
    //je laisse ça ici si on compte faire des modif

    /*if(capteurLaser!=capteurLaserPrec && capteurLaser==true){
      compteurFront = compteurFront+1;
      Serial.println(compteurFront);

      if(compteurFront>=11){ //nbr de saut
        std::array<uint64_t, 10> tab = modemesure.getTabTemps();

      // Test de la fonction getTabtemps en parcourant tout le tableau
        for(int i=0 ; i < modemesure.getIndice() ; i++){
          int p = (int) tab[i];
          Serial.println(p);
        }
        //s.modifyMeasurements(tab);
        modemesure.cleanTab();

        etat=0;
      }
    }
    capteurLaserPrec = capteurLaser;*/
    break;

  default:
    // statements
    Serial.println("error");
    break;
  }
}
#endif

/******************************* test integration tout d'affilé 2 *******************************/
#ifdef testIntegration2

//serveur
#include "Serveur.hpp"
Serveur s;

//chrono
#include "ModeMesure.hpp"
#include <Wire.h>    //We need the wire library for the I2C display
#define OLED_RESET 4 //display reset is on digital 4 but not used

#include <cinttypes>
#include <array>

bool capteurLaser, bouton, boolCapteurLaserFront;
ModeMesure modemesure;

//a quoi sert ses 2 variable?
bool boolBouton, boolCapteur;

int capt1, capt2;

int i;

//variable supp de test
bool chronoEnCour;
std::list<std::array<uint32_t, 10>> tableauChrono;

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello World!\n");

  s.InitServeur("tempsDeVol");

  modemesure.init();
  boolBouton = false;
  boolCapteur = false;
  boolCapteurLaserFront = false;

  capt1 = 0;
  capt2 = 0;
  pinMode(D6, INPUT);
  pinMode(D8, INPUT);
  pinMode(D0, OUTPUT);

  chronoEnCour = false;

  tableauChrono.clear();
}

void loop()
{

  if (!chronoEnCour)
    s.useServeur();

  //Detection bouton pour capt1 et detection presence personne capt2
  capt1 = digitalRead(D6);
  capt2 = digitalRead(D8);

  if (capt1 > 0)
    bouton = true;
  else
    bouton = false;

  if (capt2 == 0)
  {
    //Serial.println("Partie capt2 test");

    capteurLaser = true;
    //Serial.println(modemesure.getIndice());

    if (modemesure.getIndice() >= 10 && chronoEnCour)
    { //nbr de saut

      std::array<uint32_t, 10> tab = modemesure.getTabTemps();

      for (int i = 0; i < modemesure.getIndice(); i++)
      {
        int p = (int)tab[i];
        Serial.println(p);
      }

      Serial.println("\n");
      tableauChrono.push_back(tab);
      s.modifyMeasurements(tableauChrono);
      modemesure.cleanTab();

      chronoEnCour = false;
    }
  }
  else
    capteurLaser = false;

  if (bouton == true)
  {
    modemesure.lancerMesure();
    chronoEnCour = true;
    //Serial.println("Partie Bouton");
  }

  if ((capteurLaser == true) && (boolCapteurLaserFront == false))
  {
    boolCapteurLaserFront = true;
    boolBouton = modemesure.presencePersonne();
    //Serial.println("Partie BoolCapteurLaserFront presence personne");
  }

  if ((capteurLaser == false) && (boolCapteurLaserFront == true))
  {
    boolCapteurLaserFront = false;
    modemesure.absencePersonne();
    //Serial.println("Partie BoolCapteurLaserFront absence personne");
  }

  // Pour LA LED
  if (boolCapteurLaserFront == true)
    digitalWrite(D0, HIGH);
  else
    digitalWrite(D0, LOW);
}
#endif

/******************************* Test Chronometre avec front *******************************/
#ifdef testChronoFront
#include "ModeMesure.hpp"
#include <Wire.h>    //We need the wire library for the I2C display
#define OLED_RESET 4 //display reset is on digital 4 but not used

#include <cinttypes>
#include <array>

bool capteurLaser, bouton;
ModeMesure modemesure;

//a quoi sert ses 4 variable?
bool boolBouton, boolCapteur;
int cpt, cpt2;

int i;

//variable front
bool capteurLaserPrec, boutonPrec;

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello World!");
  modemesure.init();
  boolBouton = false;
  boolCapteur = false;
  cpt = 0;
  cpt2 = 0;
  pinMode(D6, INPUT);
  pinMode(D8, INPUT);

  capteurLaserPrec = false;
  boutonPrec = false;
}

void loop()
{

  //Detection bouton pour capt1 et detection presence personne capt2
  int capt1 = digitalRead(D6);
  int capt2 = digitalRead(D8);

  if (capt1 > 0)
    bouton = true;
  else
    bouton = false;

  if (capt2 > 0)
    capteurLaser = true;
  else
    capteurLaser = false;

  //front montant du capteur
  if (capteurLaserPrec != capteurLaser && capteurLaser == true)
  {
  }

  //front descendant du capteur
  if (capteurLaserPrec != capteurLaser && capteurLaser == false)
  {
  }

  //front montant du bouton
  if (boutonPrec != bouton && bouton == true)
  {
  }

  //front descendant du bouton
  if (boutonPrec != bouton && bouton == false)
  {
  }

  capteurLaserPrec = capteurLaser;
  boutonPrec = bouton;
}

#endif

/******************************* test RWtab *******************************/
#ifdef testRWtab

#include "RWtab.hpp"
#include "EEPROM.h"

RWtab rwtab;
void setup()
{
  Serial.begin(9600);
  EEPROM.begin(1000);
  Serial.print("Hello World!");
}

void loop()
{

  if (Serial.available())
  {
    char data = Serial.read();
    if (data == 'k')
    {
      uint32_t tab[10];
      for (int i = 0; i < 10; i++)
        tab[i] = (i + 1) * 10;

      rwtab.remplirTableau(tab);
      Serial.println("true K");
      rwtab.afficher();
    }

    if (data == 'l')
    {
      rwtab.writeAll();
      Serial.println("false l");
      //Serial.println(rwtab.read(0));
      rwtab.afficher();
    }
    if (data == 'p')
    {
      rwtab.afficher();
    }

    if (data == 'j')
    {
      rwtab.clearAll();
      Serial.println("false j");
      rwtab.readAll();
      rwtab.afficher();
    }

    if (data == 'o')
    {
      rwtab.clearAll();
      Serial.println("false o");
      rwtab.writeAll();
      rwtab.afficher();
    }

    if (data == 'y')
    {
      uint32_t tab1[20][10];
      rwtab.getTabFilo(tab1);
      Serial.println("affichage tableau fifo");
      for (int i = 0; i < 20; i++)
      {
        for (int j = 0; j < 10; j++)
        {

          Serial.print(tab1[i][j]);
          Serial.print(" ");
        }
        Serial.println(" ");
      }
    }
  }
}
#endif

/******************************* test TableauDesMesures2 *******************************/
#ifdef testTableauDesMesures2

#include "RWtab.hpp"
#include "EEPROM.h"

void print(std::list<std::array<uint32_t, 10>> data)
{
  for (auto i : data)
  {
    for (auto j : i)
      Serial.println(j + " ");
    Serial.println("");
  }
  Serial.println("");
}

RWtab rwtab;
void setup()
{
  Serial.begin(9600);
  Serial.println("");
  Serial.println("test TableauDesMesures");
  rwtab.readAll();
  print(rwtab.getTabLifo());
}

void loop()
{
  if (Serial.available())
  {
    char data = Serial.read();
    if (data == 'a')
    {
      std::array<uint32_t, 10> tab;
      for (int i = 0; i < 10; i++)
        tab[i] = (i + 1) * 10;

      rwtab.remplirTableau(tab);
      rwtab.writeAll();
      print(rwtab.getTabLifo());
    }

    if (data == 'c')
    {
      rwtab.clearAll();
      rwtab.writeAll();
      print(rwtab.getTabLifo());
    }
  }
}
#endif

/******************************* test Memoire *******************************/
#ifdef testMemoire

#include "RWtab.hpp"
#include <EEPROM.h>
RWtab rwtab;
void setup()
{
  Serial.begin(9600);
  EEPROM.begin(512);
}

void loop()
{
  int val = 10;
  if (Serial.available())
  {
    char data = Serial.read();
    if (data == 'k')
    {
      EEPROM.write(0, val);
    }

    if (data == 'l')
    {
      EEPROM.write(0, val + 20);
    }

    if (data == 'j')
    {
      int value = EEPROM.read(0);
      Serial.print(value, DEC);
      Serial.println();
    }
  }
}
#endif