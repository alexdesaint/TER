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
		
		print += String(m/1000);
	}

	print += "] ";
	Serial.print(print);
}

void setup() {
	Serial.begin(9600);

	ModeMesure modeMesure(30, 30);

	Serial.println("");

	Serial.println("Test 1 -- pas de rebonds");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();
		Serial.print("{A ");

		int totDelay = 0;

		delay(50 * (i%3 + 1));
		totDelay += 50 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());

		Serial.printf("P %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("Test 2 -- un rebonds a absencePersonne");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();
		Serial.print("{A ");

		int totDelay = 0;

		delay(5);
		totDelay += 5;

		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		totDelay += 5;
		modeMesure.absencePersonne();
		delay(40 * (i%3 + 1));
		totDelay += 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());

		Serial.printf("P %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("Test 3 -- un rebonds en vol");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();
		Serial.print("{A ");

		int totDelay = 0;

		delay(50);
		totDelay += 50;

		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		totDelay += 5;

		modeMesure.absencePersonne();
		delay(30 * (i%3 + 1));
		totDelay += 30 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());

		Serial.printf("P %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}
}

void loop() {
	
}

#endif
