#include "ModeMesure.hpp"
#include <SPI.h>
#include <Wire.h>

ModeMesure::ModeMesure(int seuil,int seuilInter){
  this->seuilInterferance = seuilInter;
  this->seuilRebond = seuil ;
}


int ModeMesure::getIndice() { return this->indiceTabTemps; }

void ModeMesure::absencePersonne()
{


  presenceTrampolin = false;
  presenceP = false;

    if ((mode1 = false) && (this->lancerM == false))
  {
    this->timestart = micros();
    this->timePauseStart = micros();
    this->timePauseEnd = micros();
    this->timefinished = micros();
    this->totalTempsPause = 0;
    this->mode1 = true;
    this->mode2 = false;
    this->time_us = 0;
    this->indiceTabTemps = 0;
    Serial.println("mode 1");
    this->boolPause = false;
  }

  if ((presenceP == false) && (this->lancerM == false))
  {
    // On remet tout a 0 on le fait dans ce cas , mais normalement on doit pas
    // appuyer dans le bouton quand on est dans cette situation la
    if((micros()-this->timePauseStart)/1000 > seuilInterferance){
    this->timestart = micros();
    this->timePauseEnd = micros();
    }
  
    this->time_us = 0;
    this->boolPause = false;
    this->indiceTabTemps = 0;

  }

  /*if ((presencePersonne == false) && (this->boolPause == true) &&
      (this->lancerMesure == false))
  {
    this->boolPause = false;
    // On remet tout a 0 et si on appui dans le bouton on passe au mode 2 avec
    // ces initialization
    this->timestart = micros();
    this->timePauseStart = micros();
    this->timePauseEnd = micros();
    this->timefinished = micros();
    this->totalTempsPause = 0;
    this->time_us = 0;
    this->indiceTabTemps = 0;
    this->lastTime = micros() ;
  }*/

  if (this->indiceTabTemps < 11 && lancerM == true)
  {
    // On detecte qu'on a sortir du trampolin on compte le temps ecoulé de pause
    if ((presenceP == false) && (this->boolPause == true) &&
        (lancerM == true))
    {
      
      if((micros()-this->timePauseStart)/1000 > this->seuilInterferance){
        this->timePauseEnd = micros();
        this->boolPause = false;
        this->totalTempsPause =
          totalTempsPause + (this->timePauseEnd - this->timePauseStart);
        this->lastTime = (this->timePauseEnd - this->timePauseStart);
        this->interferance = false ;
      }else
      {
      if(lastFlyTime > seuilRebond){
        this->boolPause = false;
        this->interferance = true ;
        this->lastTime = micros();
      }
        /* code */
      }   
    }

    this->lancerM = true;
  }
  else{
    this->lancerM = false;
    //Serial.print("hoola");
    //Serial.print(indiceTabTemps);
  }
}

bool ModeMesure::presencePersonne()
{
  this->presenceP = true;



  // Init du mode2 seulement ce fait une foit quand on rentre
  if ((mode2 = false) && (lancerM == true))
  {
    this->totalTempsPause = 0;
    // this->timestart = micros();
    // this->timePauseStart = micros();
    // this->timePauseEnd = micros();
    // this->timefinished = micros();
    this->mode2 = true;
    this->mode1 = false;
    this->indiceTabTemps = 0;
    Serial.println("mode 2");
  }

    if ((presenceP == true) && (this->lancerM == false))
  {
    // On remet tout a 0 on le fait dans ce cas , mais normalement on doit pas
    // appuyer dans le bouton quand on est dans cette situation la
    this->timePauseStart = micros();

  }



  if (this->indiceTabTemps < 11 && lancerM == true)
  {
    // On detecte qu'on a touché le trampolin on lance le timer pour le temps de
    // pause
    if (presenceP == true && this->boolPause == false &&
        lancerM == true)
    {
     

      // Code anti rebond avec un seuil
      if ( (((micros() - this->timePauseEnd) / 1000) > this->seuilRebond)  && ((micros()-this->lastTime)/1000 > this->seuilInterferance)  )
      {
        this->boolPause = true;
        this->timePauseStart = micros();
        this->timefinished = micros();
        this->finMesure = false;
        // On calcule le temps de vols de chaque figure et on la stock dans un
        // tableau


        // On traite l'interferance pour ignorer une valeur.
        if(interferance == true && this->indiceTabTemps > 0){
          this->indiceTabTemps--;
          tabTemps[this->indiceTabTemps] = this->timefinished - this->timePauseEnd;
          this->lastFlyTime = this->timefinished - this->timePauseEnd;
          this->indiceTabTemps++;
          interferance = false;

        }else{
          tabTemps[this->indiceTabTemps] = this->timefinished - this->timePauseEnd;
          this->lastFlyTime = this->timefinished - this->timePauseEnd;
          this->indiceTabTemps++;
        }

        if(this->indiceTabTemps>10){
          this->finMesure = true;
          this->lancerM = false;
          this->indiceTabTemps=0;
        }

        //Serial.println((uint32_t)(this->timefinished - this->timePauseEnd));
        presenceTrampolin = true;
      }else
      {
        if(interferance == true){
          this->boolPause = true;
          this->interferance = false ;

        }
        /* code */
      }
      

      // On compte le temps de vol total
      this->time_us =
          (this->timefinished - this->timestart) - this->totalTempsPause;
      
    }
    
  }
  else
  {
    this->lancerM = false;
    this->finMesure = false;
  }

  return this->finMesure;
}

std::array<uint32_t, 10> ModeMesure::getTabTemps() { return this->tabTemps; }

void ModeMesure::lancerMesure() { this->lancerM = true; }


uint32_t ModeMesure::getTime()
{
  return this->lastFlyTime;
}

bool ModeMesure::getIndicateur()
{
  return this->presenceTrampolin;
}