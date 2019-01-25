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
}

void loop()
{
	ModeMesure modeMesure;

	modeMesure.lancerMesure();

	for (int i = 0; i < 50; i++)
	{
		modeMesure.absencePersonne();

		delay(500);

		if (modeMesure.presencePersonne())
			Serial.println("True");
		else
			Serial.println("False");

		delay(500);
	}

	while(true){}
}

#endif
