#include "RWtab.hpp"
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>

using namespace std;

#define ADRESSE 0
//#define CONFIG_ADRESS (CONFIG_SECTOR*4096)
//#define CONFIG_ADRESS1 CONFIG_ADRESS+8

//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to address + 3.
void RWtab::EEPROMWritelong(int address, uint32_t value)
{
    //Decomposition from a long to 4 bytes by using bitshift.
    //One = Most significant -> Four = Least significant byte
    uint8_t four = (value & 0xFF);
    uint8_t three = ((value >> 8) & 0xFF);
    uint8_t two = ((value >> 16) & 0xFF);
    uint8_t one = ((value >> 24) & 0xFF);

    //Write the 4 bytes into the eeprom memory.
    EEPROM.write(address, four);
    EEPROM.write(address + 1, three);
    EEPROM.write(address + 2, two);
    EEPROM.write(address + 3, one);
}

uint32_t RWtab::EEPROMReadlong(int address)
{
    //Read the 4 bytes from the eeprom memory.
    uint8_t four = EEPROM.read(address);
    uint8_t three = EEPROM.read(address + 1);
    uint8_t two = EEPROM.read(address + 2);
    uint8_t one = EEPROM.read(address + 3);

    //Return the recomposed long by using bitshift.
    return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

void RWtab::readAll()
{
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            this->tabToutesMesures[j][i] = EEPROMReadlong(ADRESSE + (10 * j + i) * 4);
        }
    }

    this->index_write = EEPROMReadlong(ADRESSE + (10 * 20 + 10) * 4);
}

void RWtab::writeAll()
{
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            EEPROMWritelong(ADRESSE + (10 * j + i) * 4, this->tabToutesMesures[j][i]);
        }
    }

    EEPROMWritelong(ADRESSE + (10 * 20 + 10) * 4, this->index_write);

    EEPROM.commit();
}

void RWtab::remplirTableau(array<uint32_t, 10> tab)
{
    Serial.println(this->index_write);

    this->tabToutesMesures[this->index_write] = tab;

    this->index_write++;

    if (this->nbValue < 20)
        this->nbValue++;

    if (this->index_write == 20)
        this->index_write = 0;
}

void RWtab::afficher()
{
    for (int j = this->index_write - 1; j >= 0; j--)
    {
        for (uint32_t i : this->tabToutesMesures[j])
            Serial.print(i + " ");
        
        Serial.println("");
    }

    for (int j = 19; j >= this->index_write; j--)
    {

        for (uint32_t i : this->tabToutesMesures[j])
            Serial.print(i + " ");

        Serial.println(" ");
    }

    Serial.print("Index write = ");
    Serial.println(this->index_write);
}

void RWtab::clearAll()
{
    this->index_write = 0;
    this->nbValue = 0;
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            this->tabToutesMesures[j][i] = 0;
        }
        Serial.println(" ");
    }
}

void RWtab::getTabFilo(uint32_t tab[20][10])
{

    int index = this->index_write;
    int index_tab = 0;

    for (int j = index - 1; j >= 0; j--)
    {
        for (int i = 0; i < 10; i++)
        {
            tab[index_tab][i] = this->tabToutesMesures[j][i];
        }
        index_tab++;

        if (index_tab > 20)
            Serial.print("Erreur FATALE !!! ");
    }
    for (int j = 19; j >= index; j--)
    {

        for (int i = 0; i < 10; i++)
        {
            tab[index_tab][i] = this->tabToutesMesures[j][i];
        }
        index_tab++;
        if (index_tab > 20)
            Serial.print("Erreur FATALE !!! ");
    }
}

std::list<std::array<uint32_t, 10>> RWtab::getTabLifo()
{

    std::list<std::array<uint32_t, 10>> data;

    int index = this->index_write;
    int index_tab = 0;

    std::array<uint32_t, 10> tab;

    for (int j = index - 1; j >= 0; j--)
    {
        data.push_back(this->tabToutesMesures[j]);

        index_tab++;
        if (index_tab > 20)
            Serial.print("Erreur FATALE !!! ");
    }
    for (int j = (nbValue - index_write); j >= index; j--)
    {
        data.push_back(this->tabToutesMesures[j]);
        index_tab++;
        if (index_tab > 20)
            Serial.print("Erreur FATALE !!! ");
    }

    return data;
}
