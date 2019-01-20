#include "RWtab.hpp"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#define CONFIG_SECTOR (0x80-4)
#define CONFIG_ADRESS (CONFIG_SECTOR*4096)
#define CONFIG_ADRESS1 CONFIG_ADRESS+8


void RWtab::init(){

    

}

void RWtab::erase(){
    SPIEraseSector(CONFIG_SECTOR);
}

void RWtab::write(){
    SPIWrite(CONFIG_ADRESS,(uint32_t*)&tabTest[0],sizeof(uint32_t));
    SPIWrite(CONFIG_ADRESS+4,(uint32_t*)&tabTest[3],sizeof(uint32_t));

}

uint32_t RWtab::read(){
    SPIRead(CONFIG_ADRESS,(uint32_t*)&tabRead[0],sizeof(uint32_t));
    SPIRead(CONFIG_ADRESS+4,(uint32_t*)&tabRead[1],sizeof(uint32_t));

    Serial.println(tabRead[0]);
    Serial.println(tabRead[1]);

    //for(int i=0 ; i<10 ;i++){
    //    Serial.println(tabRead[i]);
    //}

    return 0;

}

void RWtab::remplirTableau(uint32_t tab[10]){
    for(int i=0 ; i<10 ;i++){
        this->tabTest[i] =tab[i];
        this->tabRead[i] =0 ;
    }
}

void RWtab::afficher(){
    Serial.println("");
    Serial.print("Tab Test ");
    for(int i=0 ; i<10 ;i++){
        Serial.print(this->tabTest[i]);
        Serial.print(" ");
    }
    Serial.println("");
    Serial.print("Tab Read ");
    for(int i=0 ; i<10 ;i++){
        Serial.print(this->tabRead[i]);
        Serial.print(" ");
    }

}