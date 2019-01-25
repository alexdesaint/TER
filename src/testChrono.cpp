/******************************* Test Chronometre *******************************/
#ifdef testChrono
#include <Arduino.h>

#include "ModeMesure.hpp"

void printTab(std::array<uint32_t, 10> tabTemps)
{
	String print;
	for (uint32 m : tabTemps)
	{
		print += String(m) + ", ";
	}
	Serial.println(print);
}

void setup()
{
	Serial.begin(9600);

	ModeMesure modeMesure;

	Serial.println("");

	for (int i = 0; i < 50; i++)
	{
		modeMesure.absencePersonne();

		delay(500);

		Serial.printf("Saut %i ", i);

		if(i == 10) {
			modeMesure.lancerMesure();
			Serial.print("LancerMesure ");
		}

		if (modeMesure.presencePersonne()) {
			Serial.println("True");
			printTab(modeMesure.getTabTemps());
		}

		delay(500);
	}
}

void loop()
{
	
}

#endif
