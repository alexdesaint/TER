#include "RWtab.hpp"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <EEPROM.h>

#define CONFIG_SECTOR (0x80-6)
//#define CONFIG_ADRESS (CONFIG_SECTOR*4096)
//#define CONFIG_ADRESS1 CONFIG_ADRESS+8


void RWtab::init(){

    

}


void RWtab::write(int index){

if(index>=0 && index<20){
    for(int i=0 ; i<10 ;i++){
        EEPROM.write(10*index+i,tabToutesMesures[index][i]);
    }
}
    EEPROM.commit();

}

uint32_t RWtab::read(int index){

    if(index>=0 && index<20){
        for(int i=0 ; i<10 ;i++){
            this->tabToutesMesures[index][i] = EEPROM.read(10*index+i);
        }
    }

    //tabRead[0]=EEPROM.read(0);

    return 0;

}

void RWtab::readAll(){
    for(int j=0 ; j<20 ;j++){
        for(int i=0 ; i<10 ;i++){
            this->tabToutesMesures[j][i] = EEPROM.read(10*j+i);
        }
    }


}

void RWtab::writeAll(){
    for(int j=0 ; j<20 ;j++){
        for(int i=0 ; i<10 ;i++){
            EEPROM.write(10*j+i,this->tabToutesMesures[j][i]);
        }
    }
        EEPROM.commit();

}

void RWtab::remplirTableau(uint32_t tab[10],int index){
    if(index>=0 && index<20){
        for(int i=0 ; i<10 ;i++){
            this->tabToutesMesures[index][i] =tab[i];

        }
    }

}

void RWtab::afficher(){
    Serial.println("");
    Serial.println("Tab Full ");
    for(int j=0 ; j<20 ;j++){
        for(int i=0 ; i<10 ;i++){
            Serial.print(this->tabToutesMesures[j][i]);
            Serial.print(" ");
        }
        Serial.println(" ");

    }
}

void RWtab::clearAll(){
    for(int j=0 ; j<20 ;j++){
        for(int i=0 ; i<10 ;i++){
            this->tabToutesMesures[j][i] = 0 ;

        }
        Serial.println(" ");

    }

}


