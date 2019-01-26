#ifndef ModeMesure_hpp
#define ModeMesure_hpp

#include <cinttypes>
#include <array>

class ModeMesure {
private:
  //Seuil pour le rebond
  uint32_t seuilRebond ;
  uint32_t seuilInterferance;
  // TIme start ,finished et total serve pour calculer le temps de vols
  uint32_t timestart, timefinished,  timetotal ;
  // TimePauseStart and end sont les temps pendant que on est entrain de toucher le trampolin
  uint32_t timePauseStart , timePauseEnd ;
  // Le temps de vol
  uint32_t time_us , totalTempsPause , lastFlyTime;

  uint32_t lastTime ;




  // Bool pause , mode 1 et mode 2 sont les boolean qui servent a savoir si on est respectivement dans la pause , mode 1 ou mode 2
  bool boolPause , boolMode1 , boolMode2 ; 
  bool boolInterference = false ;
  bool presenceTrampolin = false ;
  bool boolPresencePersonne = false ;
  bool boolBouton = false ; 
  bool boolLancerMesure = false ; 
  bool boolFinMesure = false ;


  std::array<uint32_t, 10> tabTemps ;
  int indiceTabTemps;


public:
  ModeMesure(int seuil=300 , int seuilInter=100);
  uint32_t lectureTemps();

  void init();

  std::array<uint32_t, 10> getTabTemps() ;

  void absencePersonne();

  bool presencePersonne();

  void presenceBouton();

  void lancerMesure();

  int getIndice();

  void cleanTab();

  uint32_t getTime();
  
  bool getIndicateur();
};

#endif /* end of include guard:ModeMesure_hpp */
