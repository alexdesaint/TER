#include "RWtab.hpp"
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>

#define ADRESSE 0
//#define CONFIG_ADRESS (CONFIG_SECTOR*4096)
//#define CONFIG_ADRESS1 CONFIG_ADRESS+8


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
        EEPROM.write(ADRESSE+10*index+i,tabToutesMesures[index][i]);
    }
}
    EEPROM.commit();

}

uint32_t RWtab::read(int index){

    if(index>=0 && index<20){
        for(int i=0 ; i<10 ;i++){
            this->tabToutesMesures[index][i] = EEPROM.read(ADRESSE+10*index+i);
        }
    }

    //tabRead[0]=EEPROM.read(0);

    return 0;

}

void RWtab::readAll(){
    for(int j=0 ; j<20 ;j++){
        for(int i=0 ; i<10 ;i++){
            this->tabToutesMesures[j][i] = EEPROM.read(ADRESSE+10*j+i);
        }
    }


}

void RWtab::writeAll(){
    for(int j=0 ; j<20 ;j++){
        for(int i=0 ; i<10 ;i++){
            EEPROM.write(ADRESSE+10*j+i,this->tabToutesMesures[j][i]);
        }
    }
    EEPROM.commit();

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


