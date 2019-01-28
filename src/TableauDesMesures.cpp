#include "TableauDesMesures.hpp"
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>

using namespace std;

//#define CONFIG_ADRESS (CONFIG_SECTOR*4096)
//#define CONFIG_ADRESS1 CONFIG_ADRESS+8

//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to address + 3.
void TableauDesMesures::EEPROMWritelong(int address, uint32_t value)
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

uint32_t TableauDesMesures::EEPROMReadlong(int address)
{
    //Read the 4 bytes from the eeprom memory.
    uint8_t four = EEPROM.read(address);
    uint8_t three = EEPROM.read(address + 1);
    uint8_t two = EEPROM.read(address + 2);
    uint8_t one = EEPROM.read(address + 3);

    //Return the recomposed long by using bitshift.
    return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

TableauDesMesures::TableauDesMesures()
{
    EEPROM.begin(1000);
}

void TableauDesMesures::readAll()
{
    this->index_write = EEPROMReadlong((10 * 20) * 4);
    this->nbValue = EEPROMReadlong((10 * 20 + 1) * 4);

    if(index_write > 19 || nbValue > 20)
        clearAll();

    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            this->tabToutesMesures[j][i] = EEPROMReadlong((10 * j + i) * 4);
        }
    }
}

void TableauDesMesures::writeAll()
{
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            EEPROMWritelong((10 * j + i) * 4, this->tabToutesMesures[j][i]);
        }
    }

    EEPROMWritelong((10 * 20) * 4, this->index_write);
    EEPROMWritelong((10 * 20 + 1) * 4, this->nbValue);

    EEPROM.commit();
}

void TableauDesMesures::remplirTableau(array<uint32_t, 10> tab)
{
    this->tabToutesMesures[this->index_write] = tab;

    this->index_write++;

    if (this->nbValue < 20)
        this->nbValue++;

    if (this->index_write == 20)
        this->index_write = 0;
}

void TableauDesMesures::clearAll()
{
    this->index_write = 0;
    this->nbValue = 0;
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            this->tabToutesMesures[j][i] = 0;
        }
    }
}

std::list<std::array<uint32_t, 10>> TableauDesMesures::getTab()
{

    std::list<std::array<uint32_t, 10>> data;

    int index = this->index_write;
    int index_tab = 0;

    if (index_tab == (int)this->nbValue)
        return data;

    for (int j = index - 1; j >= 0; j--)
    {
        data.push_back(this->tabToutesMesures[j]);
        index_tab++;
        if (index_tab == (int)this->nbValue)
            return data;
        if (index_tab > 20)
            Serial.print("Erreur FATALE !!! ");
    }
    for (int j = 19; j >= index; j--)
    {
        data.push_back(this->tabToutesMesures[j]);
        index_tab++;
        if (index_tab == (int)this->nbValue)
            return data;
        if (index_tab > 20)
            Serial.print("Erreur FATALE !!! ");
    }

    return data;
}
