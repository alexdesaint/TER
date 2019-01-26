#include "RWtab.hpp"
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>

#define ADRESSE 2000000
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


void RWtab::init(){
/*
    for(int j=0 ; j<20 ;j++){
        for(int i=0 ; i<10 ;i++){
            this->tabToutesMesures[j][i] = EEPROM.read(ADRESSE+10*j+i);
        }
    }

   */ 

}



void RWtab::write(int index){

if(index>=0 && index<20){
    
    for(int i=0 ; i<10 ;i++){
        EEPROMWritelong(ADRESSE+10*index+i*4,tabToutesMesures[index][i]);
    }
}
    EEPROM.commit();

}

uint32_t RWtab::read(int index){

    if(index>=0 && index<20){
        for(int i=0 ; i<10 ;i++){
            this->tabToutesMesures[index][i] = EEPROMReadlong(ADRESSE+10*index+i*4);
        }
    }

    //tabRead[0]=EEPROM.read(0);

    return 0;

}

void RWtab::readAll(){
    for(int j=0 ; j<20 ;j++){
        for(int i=0 ; i<10 ;i++){
            this->tabToutesMesures[j][i] = EEPROMReadlong(ADRESSE+10*j+i*4);
        }
    }


}

void RWtab::writeAll(){
    for(int j=0 ; j<20 ;j++){
        for(int i=0 ; i<10 ;i++){
            EEPROM.write(ADRESSE+10*j+i*4,this->tabToutesMesures[j][i]);
            EEPROM.commit();
        }
    }
    

}

void RWtab::remplirTableau(uint32_t tab[10]){

    Serial.println("Remplir tableau index");
    Serial.println(this->index_write);

    for(int i=0 ; i<10 ;i++){
        this->tabToutesMesures[this->index_write][i] =tab[i];
    }
    this->index_write++;
    if(this->index_write == 20)
        this->index_write=0;
    

}

void RWtab::removeTab(){
    for(int i=0 ; i<10 ;i++){
        this->tabToutesMesures[this->index_write][i] = 0;
    }
    this->index_remove ++;
    if(this->index_remove == 20)
        this->index_remove=0;
}

void RWtab::afficher(){
    uint32_t index = this->index_write;
    Serial.println("");
    Serial.println("Tab Full ");
    for(int j=0 ; j<20 ;j++){
        if(index ==0){
            index=20;
        }
        for(int i=0 ; i<10 ;i++){
            Serial.print(this->tabToutesMesures[(index-1)-j][i]);
            Serial.print(" ");
        }

        Serial.println(" ");

    }
}

void RWtab::clearAll(){
    this->index_remove=0;
    this->index_write=0;
    for(int j=0 ; j<20 ;j++){
        for(int i=0 ; i<10 ;i++){
            this->tabToutesMesures[j][i] = 0 ;
        }
        Serial.println(" ");

    }

}




