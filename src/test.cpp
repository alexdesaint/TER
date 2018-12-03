#include <Arduino.h>


/******************************* Test Chronometre *******************************/
#ifdef testChrono
#include "ModeMesure.hpp"
#include <Wire.h>                               //We need the wire library for the I2C display
#define OLED_RESET 4                            //display reset is on digital 4 but not used
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

bool capteursLaser , bouton ;
ModeMesure modemesure ;
bool boolBouton , boolCapteur ;

int cpt , cpt2 ;

int i ;


void setup() {
  Serial.begin(9600);
  Serial.println("Hello World!");
  modemesure.init();
  boolBouton = false ; 
  boolCapteur= false ; 
  cpt = 0 ;
  cpt2 = 0 ;

}

void loop() {

  if(bouton == true){
    boolBouton= true ;
  }

  if(bouton == false && boolBouton == true){
    boolBouton = modemesure.mode2(capteursLaser);

  }

  if(boolBouton == false){

    modemesure.mode1(capteursLaser);
  }





// Simulation capteurs

  delay(100);
  cpt ++ ; 

  if(cpt2 == 0)
    bouton = true ;
  else
    bouton = false ;

  if(cpt == 50)
    cpt = 0 ;
    cpt2 ++ ;

  if(cpt2 == 15){
    cpt2 = 0 ;
  }

  if(cpt == 20)
    capteursLaser = true ;

  if(cpt == 35)
     capteursLaser = false ;

// en milliseconde 
  i = (int) modemesure.lectureTemps();
  
  Serial.println(i);

}

#endif

/******************************* test Serial *******************************/
#ifdef testSerial

void setup() {
  Serial.begin(9600);
  Serial.println("Hello World!");
}

void loop() {

}

#endif

/******************************* test ecran *******************************/
#ifdef testEcran

#include "Ecran.hpp"

void setup() {
  Serial.begin(9600);
  Ecran e;
  e.test();
}

void loop() {

}
#endif

/******************************* test serveur *******************************/
#ifdef testServeur

#include "Serveur.hpp"

Serveur s;

void setup() {
  Serial.begin(9600);
  s.InitServeur("tempsDeVol");
}

void loop() {
  s.useServeur();
}
#endif

/*********************** test maraboutage*************************/
#ifdef testEcran

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