#include "ModeMesure.hpp"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>


void ModeMesure::init(){
this->indiceTabTemps = 0 ;
this->boolPause = false;
this->boolMode1 = false ;
this->boolMode2 = false ;

}

int ModeMesure::getIndice(){

    return this->indiceTabTemps ;
}

uint32_t ModeMesure::lectureTemps(){
    return this->time_us / 1000;
}


void ModeMesure::absencePersonne(){
    boolPresencePersonne = false ;
    if((boolPresencePersonne == false) && (this->boolPause == true) && (this->boolLancerMesure == false)){
        this->boolPause = false;
        // On remet tout a 0 et si on appui dans le bouton on passe au mode 2 avec ces initialization
        this->timestart = micros();
        this->timePauseStart = micros();
        this->timePauseEnd = micros();
        this->timefinished = micros();
        this->totalTempsPause = 0 ;
        this->time_us = 0;
        this->indiceTabTemps = 0 ;

    }

if( this->indiceTabTemps < 10 && boolLancerMesure == true ){
    // On detecte qu'on a sortir du trampolin on compte le temps ecoulé de pause
        if((boolPresencePersonne == false) && (this->boolPause == true) && (boolLancerMesure == true) ){
            this->boolPause = false;
            this->timePauseEnd = micros();

            // On calcule le temps total pendant qu'on est dans le tapis
            this->totalTempsPause = totalTempsPause + (this->timePauseEnd - this->timePauseStart);
        
        }

     this->boolLancerMesure = true ;
}
else
   this->boolLancerMesure = false ;




}

bool ModeMesure::presencePersonne(){
    this->boolPresencePersonne = true ;
    int mode ;

    if((boolMode1 = false) && (this->boolLancerMesure == false )){
        this->timestart = micros();
        this->timePauseStart = micros();
        this->timePauseEnd = micros();
        this->timefinished = micros();
        this->totalTempsPause = 0 ;
        this->boolMode1 = true ;
        this->boolMode2 = false ;
        this->time_us = 0;
        this->indiceTabTemps = 0 ;
        mode = 1 ;
        Serial.println("mode 1");



    }

    // Init du mode2 seulement ce fait une foit quand on rentre
    if( (boolMode2 = false) && (boolLancerMesure == true )){
        this->totalTempsPause= 0 ;
        // this->timestart = micros();
        //this->timePauseStart = micros();
        //this->timePauseEnd = micros();
        //this->timefinished = micros();
        this->boolMode2 = true ;
        this->boolMode1 = false ;
        this->indiceTabTemps = 0 ;
        mode = 2 ;
        Serial.println("mode 2");

    }

    if((boolPresencePersonne == true) && (this->boolLancerMesure == false)){
        this->boolPause = true; 
        // On remet tout a 0 on le fait dans ce cas , mais normalement on doit pas appuyer dans le bouton quand on est dans cette
        // situation la 
        this->timestart = micros();
        this->timePauseStart = micros();
        this->timePauseEnd = micros();
        this->timefinished = micros();
        this->time_us = 0;
    }



    if( this->indiceTabTemps < 10 && boolLancerMesure == true ){
    // On detecte qu'on a touché le trampolin on lance le timer pour le temps de pause
        if(boolPresencePersonne == true && this->boolPause == false && boolLancerMesure == true ){
            this->boolPause = true; 
            this->timePauseStart = micros();
            this->timefinished = micros();

            //Code anti rebond avec un seuil
            if( ((this->timefinished - this->timePauseEnd)/1000) > this->seuilRebond ){
                // On calcule le temps de vols de chaque figure et on la stock dans un tableau
                tabTemps[this->indiceTabTemps] = (uint32_t) (this->timefinished - this->timePauseEnd)/1000 ;
                this->indiceTabTemps ++ ;
                Serial.println( (uint32_t) (this->timefinished - this->timePauseEnd)/1000);
            }

            // On compte le temps de vol total
            this->time_us =  (this->timefinished - this->timestart) - this->totalTempsPause ;
        }
        this->boolEntrainDeMesurer = true ;

    }
    else{
        this->boolEntrainDeMesurer = false ;
        this->boolLancerMesure = false ;
        //this->indiceTabTemps=0 ;
    }

return this->boolEntrainDeMesurer ; 

}




std::array<uint32_t, 10> ModeMesure::getTabTemps(){

    return this->tabTemps ;
}


void ModeMesure::lancerMesure(){
    this->boolLancerMesure = true ;

}

void ModeMesure::cleanTab(){
    for(int i = 0 ; i < 10 ; i++)
        this->tabTemps[i] = 0 ;
}



