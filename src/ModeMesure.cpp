#include "ModeMesure.hpp"
#include <SPI.h>
#include <Wire.h>

ModeMesure::ModeMesure(int seuil,int seuilInter){
  this->seuilInterferance = seuilInter;
  this->seuilRebond = seuil ;
}

void ModeMesure::init()
{
  this->indiceTabTemps = 0;
  this->boolPause = false;
  this->boolMode1 = false;
  this->boolMode2 = false;
}

int ModeMesure::getIndice() { return this->indiceTabTemps; }

uint32_t ModeMesure::lectureTemps() { return this->time_us; }

void ModeMesure::absencePersonne()
{


  presenceTrampolin = false;
  boolPresencePersonne = false;

    if ((boolMode1 = false) && (this->boolLancerMesure == false))
  {
    this->timestart = micros();
    this->timePauseStart = micros();
    this->timePauseEnd = micros();
    this->timefinished = micros();
    this->totalTempsPause = 0;
    this->boolMode1 = true;
    this->boolMode2 = false;
    this->time_us = 0;
    this->indiceTabTemps = 0;
    Serial.println("mode 1");
    this->boolPause = false;
  }

  if ((boolPresencePersonne == false) && (this->boolLancerMesure == false))
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

  /*if ((boolPresencePersonne == false) && (this->boolPause == true) &&
      (this->boolLancerMesure == false))
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

  if (this->indiceTabTemps < 10 && boolLancerMesure == true)
  {
    // On detecte qu'on a sortir du trampolin on compte le temps ecoulé de pause
    if ((boolPresencePersonne == false) && (this->boolPause == true) &&
        (boolLancerMesure == true))
    {
      
      if((micros()-this->timePauseStart)/1000 > this->seuilInterferance){
        this->timePauseEnd = micros();
        this->boolPause = false;
        this->totalTempsPause =
          totalTempsPause + (this->timePauseEnd - this->timePauseStart);
        this->lastTime = (this->timePauseEnd - this->timePauseStart);
        this->boolInterference = false ;
      }else
      {
      if(lastFlyTime > seuilRebond){
        this->boolPause = false;
        this->boolInterference = true ;
        this->lastTime = micros();
      }
        /* code */
      }   
    }

    this->boolLancerMesure = true;
  }
  else
    this->boolLancerMesure = false;
}

bool ModeMesure::presencePersonne()
{
  this->boolPresencePersonne = true;



  // Init du mode2 seulement ce fait une foit quand on rentre
  if ((boolMode2 = false) && (boolLancerMesure == true))
  {
    this->totalTempsPause = 0;
    // this->timestart = micros();
    // this->timePauseStart = micros();
    // this->timePauseEnd = micros();
    // this->timefinished = micros();
    this->boolMode2 = true;
    this->boolMode1 = false;
    this->indiceTabTemps = 0;
    Serial.println("mode 2");
  }

    if ((boolPresencePersonne == true) && (this->boolLancerMesure == false))
  {
    // On remet tout a 0 on le fait dans ce cas , mais normalement on doit pas
    // appuyer dans le bouton quand on est dans cette situation la
    this->timePauseStart = micros();

  }



  if (this->indiceTabTemps < 10 && boolLancerMesure == true)
  {
    // On detecte qu'on a touché le trampolin on lance le timer pour le temps de
    // pause
    if (boolPresencePersonne == true && this->boolPause == false &&
        boolLancerMesure == true)
    {
     

      // Code anti rebond avec un seuil
      if ( (((micros() - this->timePauseEnd) / 1000) > this->seuilRebond)  && ((micros()-this->lastTime)/1000 > this->seuilInterferance)  )
      {
        this->boolPause = true;
        this->timePauseStart = micros();
        this->timefinished = micros();
        this->boolFinMesure = false;
        // On calcule le temps de vols de chaque figure et on la stock dans un
        // tableau



        if(boolInterference == true && this->indiceTabTemps > 0){
          this->indiceTabTemps--;
          tabTemps[this->indiceTabTemps] = this->timefinished - this->timePauseEnd;
          this->lastFlyTime = this->timefinished - this->timePauseEnd;
          this->indiceTabTemps++;
          boolInterference = false;

        }else{
          tabTemps[this->indiceTabTemps] = this->timefinished - this->timePauseEnd;
          this->lastFlyTime = this->timefinished - this->timePauseEnd;
          this->indiceTabTemps++;
        }

        if(this->indiceTabTemps==10){
          this->boolFinMesure = true;
        }

        //Serial.println((uint32_t)(this->timefinished - this->timePauseEnd));
        presenceTrampolin = true;
      }else
      {
        if(boolInterference == true){
          this->boolPause = true;
          this->boolInterference = false ;

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
    this->boolLancerMesure = false;
    this->boolFinMesure = false;
    // this->indiceTabTemps=0 ;
  }

  return this->boolFinMesure;
}

std::array<uint32_t, 10> ModeMesure::getTabTemps() { return this->tabTemps; }

void ModeMesure::lancerMesure() { this->boolLancerMesure = true; }

void ModeMesure::cleanTab()
{
  for (int i = 0; i < 10; i++)
    this->tabTemps[i] = 0;
}

uint32_t ModeMesure::getTime()
{
  return this->lastFlyTime;
}

bool ModeMesure::getIndicateur()
{
  return this->presenceTrampolin;
}