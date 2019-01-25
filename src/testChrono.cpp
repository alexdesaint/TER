/******************************* Test Chronometre *******************************/
#ifdef testChrono
#include <Arduino.h>

#include "ModeMesure.hpp"

void printTab(std::array<uint32_t, 10> tabTemps) {
	String print = "[";
	bool s = true;

	for (uint32 m : tabTemps) {
		if(s)
			s = false;
		else
			print += ", ";
		
		print += String(m);
	}

	print += "]";
	Serial.print(print);
}

void setup() {
	Serial.begin(9600);

	ModeMesure modeMesure(30);

	Serial.println("");

	Serial.println("Test 1 -- pas de rebonds");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();

		delay(50);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LancerMesure ");
		}

		bool pp = modeMesure.presencePersonne();
		
		Serial.printf("Saut %i, %u ", i, modeMesure.getTime());

		if(pp) {
			Serial.print("Fin Mesure : ");
			printTab(modeMesure.getTabTemps());
		}

		Serial.println("");

		delay(50);
	}

	/************************************************************************/

	Serial.println("Test 2 -- un rebonds absencePersonne");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();
		delay(5);

		if(modeMesure.presencePersonne()) {
			Serial.print("Fin Mesure : ");
			printTab(modeMesure.getTabTemps());
		}
		delay(5);

		modeMesure.absencePersonne();
		delay(40);

		Serial.printf("Saut %i, %u ", i, modeMesure.getTime());

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LancerMesure ");
		}

		if(modeMesure.presencePersonne()) {
			Serial.print("Fin Mesure : ");
			printTab(modeMesure.getTabTemps());
		}

		Serial.println("");

		delay(50);
	}

	/************************************************************************/

	Serial.println("Test 3 -- un rebonds en vol");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();
		delay(50);

		if(modeMesure.presencePersonne()) {
			Serial.print("Fin Mesure : ");
			printTab(modeMesure.getTabTemps());
		}
		delay(5);

		modeMesure.absencePersonne();
		delay(50);

		Serial.printf("Saut %i, %u ", i, modeMesure.getTime());

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LancerMesure ");
		}

		if(modeMesure.presencePersonne()) {
			Serial.print("Fin Mesure : ");
			printTab(modeMesure.getTabTemps());
		}

		Serial.println("");

		delay(50);
	}
}

void loop() {
	
}

#endif
