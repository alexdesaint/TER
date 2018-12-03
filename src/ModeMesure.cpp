#include "ModeMesure.hpp"
#include <SPI.h>
#include <Wire.h>

void ModeMesure::init(){
this->indiceTabTemps = 0 ;
this->boolPause = false;
this->boolMode1 = false ;
this->boolMode2 = false ;

}

uint64_t ModeMesure::lectureTemps(){
    return this->time_us / 1000;
}

void ModeMesure::mode1(bool capteurLaser){
    if(boolMode1 = false){
    this->timestart = micros();
    this->timePauseStart = micros();
    this->timePauseEnd = micros();
    this->timefinished = micros();
    this->boolMode1 = true ;
    this->boolMode2 = false ;
    this->time_us = 0;

    }


    if(capteurLaser == true){
        this->boolPause = true; 
        // On remet tout a 0 on le fait dans ce cas , mais normalement on doit pas appuyer dans le bouton quand on est dans cette
        // situation la 
        this->timestart = micros();
        this->timePauseStart = micros();
        this->timePauseEnd = micros();
        this->timefinished = micros();
        this->time_us = 0;

    }

    if((capteurLaser == false) && (this->boolPause == true)){
        this->boolPause = false;
        // On remet tout a 0 et si on appui dans le bouton on passe au mode 2 avec ces initialization
        this->timestart = micros();
        this->timePauseStart = micros();
        this->timePauseEnd = micros();
        this->timefinished = micros();
        this->time_us = 0;
    }

    
}

bool ModeMesure::mode2(bool capteurLaser){
// Init du mode2 seulement ce fait une foit quand on rentre
    if(boolMode2 = false){
    this->totalTempsPause= 0 ;
   // this->timestart = micros();
    //this->timePauseStart = micros();
    //this->timePauseEnd = micros();
    //this->timefinished = micros();
    this->boolMode2 = true ;
    this->boolMode1 = false ;
    this->indiceTabTemps = 0 ;
    }

if( this->indiceTabTemps < 10 ){
    // On detecte qu'on a touché le trampolin on lance le timer pour le temps de pause
        if(capteurLaser == true && this->boolPause == false){
            this->boolPause = true; 
            this->timePauseStart = micros();
            this->timefinished = micros();

            // On calcule le temps de vols de chaque figure et on la stock dans un tableau
            tabTemps[this->indiceTabTemps] = (this->timefinished - this->timePauseEnd) ;
            this->indiceTabTemps ++ ;

            // On compte le temps de vol total
            this->time_us =  (this->timefinished - this->timestart) - totalTempsPause ;
        }

    // On detecte qu'on a sortir du trampolin on compte le temps ecoulé de pause
        if((capteurLaser == false) && (this->boolPause == true)){
            this->boolPause = false;
            this->timePauseEnd = micros();

            // On calcule le temps total pendant qu'on est dans le tapis
            this->totalTempsPause = totalTempsPause + (this->timePauseEnd - this->timePauseStart);
        
        }

    return true ;


}
else
    return false ;


}




