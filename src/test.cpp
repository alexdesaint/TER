#include <Arduino.h>

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
