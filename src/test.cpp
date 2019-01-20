#include <Arduino.h>


/******************************* Test Chronometre *******************************/
#ifdef testChrono
#include "ModeMesure.hpp"
#include <Wire.h>                               //We need the wire library for the I2C display
#define OLED_RESET 4                            //display reset is on digital 4 but not used

#include <cinttypes>
#include <array>

bool capteurLaser , bouton ;
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
  pinMode(D6,INPUT);
  pinMode(D8,INPUT);

}

void loop() {


  if(bouton == true){
    modemesure.lancerMesure();
  }

  if(capteurLaser == true ){
    boolBouton =modemesure.presencePersonne();

  }

  if(capteurLaser == false){

    modemesure.absencePersonne();
  }
  //Detection bouton pour capt1 et detection presence personne capt2
  int capt1 = digitalRead(D6);
  int capt2 = digitalRead(D8);
  if(capt1>0) 
    bouton=true ;
  else 
    bouton = false ;
  if(capt2>0) 
  {
    capteurLaser = true ;
    std::array<uint32_t, 10> tab = modemesure.getTabTemps();

    // Test de la fonction getTabtemps en parcourant tout le tableau
    for(int i=0 ; i < modemesure.getIndice() ; i++){
    
      int p = (int) tab[i];
      Serial.println(p);


      // Test de la fonction clean tab ; A tester apres avoir recuperer le tableau
      if(i == 7){
        modemesure.cleanTab();
      }

    }

  }
  else 
    capteurLaser = false ;





/*// Simulation capteurs

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
*/

// en milliseconde Affichage du temps total
  //i = (int) modemesure.lectureTemps();
  //Serial.println(i);



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
  std::list<std::array<uint32_t, 10>> dataTest = { {10, 10, 10, 10, 10, 70, 70, 70, 70, 70} };

  Serial.begin(9600);
  s.InitServeur("tempsDeVol");
  s.modifyMeasurements(dataTest) ;
}

void loop() {
  s.useServeur();
}
#endif


/*********************** test maraboutage*************************/
#ifdef testEcran2

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

/******************************* test capteur *******************************/
#ifdef testCapteur


void setup() {
  Serial.begin(9600);
  pinMode(D6,INPUT);
  pinMode(D8,INPUT);
}

void loop() {
  int capt1 = digitalRead(D6);
  int capt2 = digitalRead(D8);
  if(capt1>0) Serial.println("D6");
  else Serial.println("\n");
  if(capt2>0) Serial.println("D8");
  else Serial.println("\n");

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
#include <Wire.h>                               //We need the wire library for the I2C display
#define OLED_RESET 4                            //display reset is on digital 4 but not used

#include <cinttypes>
#include <array>

bool capteurLaser , bouton ;
ModeMesure modemesure ;

//a quoi sert ses 2 variable?
bool boolBouton , boolCapteur ;

int capt1 , capt2 ;

int i ;

//machine a etat
int etat = 0;

//variable front laser
//bool capteurLaserPrec;
//int compteurFront;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello World!\n");

  s.InitServeur("tempsDeVol");

  modemesure.init();
  boolBouton = false ; 
  boolCapteur= false ; 
  capt1 = 0 ;
  capt2 = 0 ;
  pinMode(D6,INPUT);
  pinMode(D8,INPUT);
}

void loop() {

  switch (etat) {
  case 0:
    s.useServeur();

    //detection capteur façon momo
    /*if(digitalRead(D6)>0) 
      bouton=true ;
    else 
      bouton = false ;

    if(bouton == true){*/
    if(digitalRead(D6)>0){
      etat=1;
      //capteurLaserPrec = false;
      //compteurFront=0;
    }
    break;

  case 1:

    //Detection bouton pour capt1 et detection presence personne capt2
    capt1 = digitalRead(D6);
    capt2 = digitalRead(D8);
    if(capt1>0) 
      bouton=true ;
    else 
      bouton = false ;

    if(capt2>0) 
    {
      capteurLaser = true ;
      //Serial.println(modemesure.getIndice());

      if(modemesure.getIndice()>=10){ //nbr de saut

        std::array<uint64_t, 10> tab = modemesure.getTabTemps();

        for(int i=0 ; i < modemesure.getIndice() ; i++){
          int p = (int) tab[i];
          Serial.println(p);
        }

        Serial.println("\n");
        //s.modifyMeasurements(tab);
        modemesure.cleanTab();

        etat = 0;
      }
    }
    else
      capteurLaser = false ;


    if(bouton == true){
      modemesure.lancerMesure();
    }

    if(capteurLaser == true ){
      boolBouton =modemesure.presencePersonne();
    }

    if(capteurLaser == false){
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
#include <Wire.h>                               //We need the wire library for the I2C display
#define OLED_RESET 4                            //display reset is on digital 4 but not used

#include <cinttypes>
#include <array>

bool capteurLaser , bouton , boolCapteurLaserFront ;
ModeMesure modemesure ;

//a quoi sert ses 2 variable?
bool boolBouton , boolCapteur ;

int capt1 , capt2 ;

int i ;

//variable supp de test
bool chronoEnCour;
std::list<std::array<uint32_t, 10>> tableauChrono;


void setup() {
  Serial.begin(9600);
  Serial.println("Hello World!\n");

  s.InitServeur("tempsDeVol");

  modemesure.init();
  boolBouton = false ; 
  boolCapteur= false ; 
  boolCapteurLaserFront = false ;

  capt1 = 0 ;
  capt2 = 0 ;
  pinMode(D6,INPUT);
  pinMode(D8,INPUT);
  pinMode(D0, OUTPUT);

  chronoEnCour = false;

  tableauChrono.clear();

}

void loop() {

  if(!chronoEnCour) 
    s.useServeur();

  //Detection bouton pour capt1 et detection presence personne capt2
  capt1 = digitalRead(D6);
  capt2 = digitalRead(D8);

  if(capt1>0) 
    bouton=true ;
  else 
    bouton = false ;

  if(capt2==0) 
  {
    //Serial.println("Partie capt2 test");

    capteurLaser = true ;
    //Serial.println(modemesure.getIndice());

    if(modemesure.getIndice()>=10 && chronoEnCour){ //nbr de saut

      std::array<uint32_t, 10> tab = modemesure.getTabTemps();

      for(int i=0 ; i < modemesure.getIndice() ; i++){
        int p = (int) tab[i];
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
    capteurLaser = false ;

  if(bouton == true){
    modemesure.lancerMesure();
    chronoEnCour=true;
    //Serial.println("Partie Bouton");
  }

  if((capteurLaser == true) && (boolCapteurLaserFront == false ) ){
    boolCapteurLaserFront = true ;
    boolBouton =modemesure.presencePersonne();
    //Serial.println("Partie BoolCapteurLaserFront presence personne");

  }

  if( (capteurLaser == false ) && (boolCapteurLaserFront == true)){
    boolCapteurLaserFront = false; 
    modemesure.absencePersonne();
    //Serial.println("Partie BoolCapteurLaserFront absence personne");

  }


// Pour LA LED
  if(boolCapteurLaserFront==true)
    digitalWrite(D0, HIGH);
  else
    digitalWrite(D0, LOW);


  
}
#endif

/******************************* Test Chronometre avec front *******************************/
#ifdef testChronoFront
#include "ModeMesure.hpp"
#include <Wire.h>                               //We need the wire library for the I2C display
#define OLED_RESET 4                            //display reset is on digital 4 but not used

#include <cinttypes>
#include <array>

bool capteurLaser , bouton ;
ModeMesure modemesure ;

//a quoi sert ses 4 variable?
bool boolBouton , boolCapteur ;
int cpt , cpt2;

int i ;

//variable front 
bool capteurLaserPrec , boutonPrec ;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello World!");
  modemesure.init();
  boolBouton = false ; 
  boolCapteur= false ; 
  cpt = 0 ;
  cpt2 = 0 ;
  pinMode(D6,INPUT);
  pinMode(D8,INPUT);

  capteurLaserPrec = false;
  boutonPrec = false;

}

void loop() {

  //Detection bouton pour capt1 et detection presence personne capt2
  int capt1 = digitalRead(D6);
  int capt2 = digitalRead(D8);

  if(capt1>0) 
    bouton=true ;
  else 
    bouton = false ;

  if(capt2>0) 
    capteurLaser = true ;
  else 
    capteurLaser = false ;

  //front montant du capteur
  if(capteurLaserPrec!=capteurLaser && capteurLaser==true){

  }

  //front descendant du capteur
  if(capteurLaserPrec!=capteurLaser && capteurLaser==false){

  }

  //front montant du bouton
  if(boutonPrec!=bouton && bouton==true){

  }

  //front descendant du bouton
  if(boutonPrec!=bouton && bouton==false){

  }




  capteurLaserPrec = capteurLaser;
  boutonPrec = bouton;
}

#endif

/******************************* test RWtab *******************************/
#ifdef testRWtab

#include "RWtab.hpp"

RWtab rwtab ;
void setup() {
  Serial.begin(9600);
  uint32_t tab[10];
  for(int i=0 ; i<10 ; i++)
    tab[i] = (i+1)*10 ;

  uint32_t i1 = (uint32_t) &tab[0] ;
  uint32_t i2 = (uint32_t) &tab[1] ;
  uint32_t i3 = (uint32_t) &tab[3] ;
  Serial.println(i1);
  Serial.println(i2);
  Serial.println(i3);

  

  rwtab.remplirTableau(tab);

}

void loop() {
  if(Serial.available()){
    char data = Serial.read();
    if(data =='k'){
      Serial.println("true K");
      rwtab.afficher();
    }


    if(data =='l'){
      rwtab.erase();
      rwtab.write();
      Serial.println("false l");
      Serial.println(rwtab.read());
    }

    if(data =='j'){

      Serial.println("false j");
      Serial.println(rwtab.read());
    }


    

  }
}
#endif