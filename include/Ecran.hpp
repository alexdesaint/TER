#ifndef Ecran_hpp
#define Ecran_hpp

class Ecran {
public:
  void init();
  void scanI2C();
  void test();
  void clear();
  void write(String str);
};

#endif /* end of include guard: Ecran_hpp */
