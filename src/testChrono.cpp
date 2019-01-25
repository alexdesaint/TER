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
	Serial.println("Test 1 -- pas de rebond");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();
		Serial.print("{AP ");

		delay(50 * (i%3 + 1)); int totDelay = 50 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 2 -- un rebond a absencePersonne");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();
		Serial.print("{AP ");

		//Rebond
		delay(5); int totDelay = 5;
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5); totDelay += 5;
		modeMesure.absencePersonne();
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 3 -- un GLITCH");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();
		Serial.print("{AP ");

		
		delay(40); int totDelay = 40;

		//GLITCH
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5); totDelay += 5;
		modeMesure.absencePersonne();
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 4 -- un rebond a presencePersonne");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();
		Serial.print("{AP ");

		delay(40 * (i%3 + 1)); int totDelay = 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		//Rebond
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		modeMesure.absencePersonne();
		delay(5);
		//

		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 5 -- un rebond a absencePersonne et a presencePersonne");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();
		Serial.print("{AP ");

		//Rebond
		delay(5); int totDelay = 5;
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5); totDelay += 5;
		modeMesure.absencePersonne();
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		//Rebond
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		modeMesure.absencePersonne();
		delay(5);
		//

		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 6 -- un double rebond a absencePersonne et a presencePersonne");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();
		Serial.print("{AP ");

		//Rebond
		delay(5); int totDelay = 5;
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5); totDelay += 5;
		modeMesure.absencePersonne();
		//
		//Rebond
		delay(5); totDelay += 5;
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5); totDelay += 5;
		modeMesure.absencePersonne();
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		//Rebond
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		modeMesure.absencePersonne();
		delay(5);
		//
		//Rebond
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		modeMesure.absencePersonne();
		delay(5);
		//

		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 6 -- un double rebond a absencePersonne et a presencePersonne et double GLITCH");

	for (int i = 0; i < 30; i++) {
		modeMesure.absencePersonne();
		Serial.print("{AP ");

		//Rebond
		delay(5); int totDelay = 5;
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5); totDelay += 5;
		modeMesure.absencePersonne();
		//
		//Rebond
		delay(5); totDelay += 5;
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5); totDelay += 5;
		modeMesure.absencePersonne();
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		//GLITCH
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5); totDelay += 5;
		modeMesure.absencePersonne();
		//
		//GLITCH
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5); totDelay += 5;
		modeMesure.absencePersonne();
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		//Rebond
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		modeMesure.absencePersonne();
		delay(5);
		//
		//Rebond
		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		modeMesure.absencePersonne();
		delay(5);
		//

		if(modeMesure.presencePersonne()) printTab(modeMesure.getTabTemps());

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}
}

void loop() {
	
}

#endif

/******************************* Test Chronometre2 *******************************/
#ifdef testChrono2
#include <Arduino.h>

#include "ChronometreTempsDeVols.hpp"

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

	ChronometreTempsDeVols modeMesure(30);

	Serial.println("");
	Serial.println("Test 1 -- pas de rebond");

	for (int i = 0; i < 30; i++) {
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		Serial.print("{AP ");

		delay(50 * (i%3 + 1)); int totDelay = 50 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		modeMesure.presencePersonne();

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 2 -- un rebond a absencePersonne");

	for (int i = 0; i < 30; i++) {
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		Serial.print("{AP ");

		//Rebond
		delay(5); int totDelay = 5;
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		modeMesure.presencePersonne();

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 3 -- GLITCH");

	for (int i = 0; i < 30; i++) {
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		Serial.print("{AP ");

		
		delay(40); int totDelay = 40;

		//GLITCH
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		modeMesure.presencePersonne();

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 4 -- un rebond a presencePersonne");

	for (int i = 0; i < 30; i++) {
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		Serial.print("{AP ");

		delay(40 * (i%3 + 1)); int totDelay = 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		//Rebond
		modeMesure.presencePersonne();
		delay(5);
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		//

		modeMesure.presencePersonne();

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 5 -- un rebond a absencePersonne et a presencePersonne et double ");

	for (int i = 0; i < 30; i++) {
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		Serial.print("{AP ");

		//Rebond
		delay(5); int totDelay = 5;
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		//Rebond
		modeMesure.presencePersonne();
		delay(5);
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		//

		modeMesure.presencePersonne();

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 6 -- double rebond a absencePersonne");

	for (int i = 0; i < 30; i++) {
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		Serial.print("{AP ");

		//Rebond
		delay(5); int totDelay = 5;
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//
		//Rebond
		delay(5); totDelay += 5;
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		modeMesure.presencePersonne();

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 7 -- double GLITCH");

	for (int i = 0; i < 30; i++) {
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		Serial.print("{AP ");

		
		delay(40); int totDelay = 40;

		//GLITCH
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//
		//GLITCH
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		modeMesure.presencePersonne();

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 8 -- double rebond a presencePersonne");

	for (int i = 0; i < 30; i++) {
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		Serial.print("{AP ");

		delay(40 * (i%3 + 1)); int totDelay = 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		//Rebond
		modeMesure.presencePersonne();
		delay(5);
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		//
		//Rebond
		modeMesure.presencePersonne();
		delay(5);
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		//

		modeMesure.presencePersonne();

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}

	/************************************************************************/

	Serial.println("");
	Serial.println("Test 9 -- tripe rebond a absencePersonne et a presencePersonne et triple GLITCH");

	for (int i = 0; i < 30; i++) {
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		Serial.print("{AP ");

		//Rebond
		delay(5); int totDelay = 5;
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//
		//Rebond
		delay(5); totDelay += 5;
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//
		//Rebond
		delay(5); totDelay += 5;
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		//GLITCH
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//
		//GLITCH
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//
		//GLITCH
		modeMesure.presencePersonne();
		delay(5); totDelay += 5;
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		//

		delay(40 * (i%3 + 1)); totDelay += 40 * (i%3 + 1);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LM ");
		}

		//Rebond
		modeMesure.presencePersonne();
		delay(5);
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		//
		//Rebond
		modeMesure.presencePersonne();
		delay(5);
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		//
		//Rebond
		modeMesure.presencePersonne();
		delay(5);
		if(modeMesure.absencePersonne()) printTab(modeMesure.getTabTemps());
		delay(5);
		//

		modeMesure.presencePersonne();

		Serial.printf("PP %i, %i:%u", modeMesure.getIndice(), totDelay,modeMesure.getTime()/1000);

		Serial.println("}");

		delay(50);
	}
}

void loop() {
	
}

#endif
