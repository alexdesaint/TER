#ifndef Ecran_hpp
#define Ecran_hpp

#include <Arduino.h>

class Ecran {
public:
  void init();
  void clear();
  void write(String str);
};

#endif /* end of include guard: Ecran_hpp */
