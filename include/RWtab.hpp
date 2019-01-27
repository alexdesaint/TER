#ifndef RWtab_hpp
#define RWtab_hpp

#include <cinttypes>
#include <array>
#include <list>

class RWtab
{
  private:
    uint32_t index_write, nbValue;
    std::array<uint32_t, 10> tabToutesMesures[20];

    uint32_t EEPROMReadlong(int address);
    void EEPROMWritelong(int address, uint32_t value);

  public:
    RWtab();
    void clearAll();
    void writeAll();
    void readAll();
    void remplirTableau(std::array<uint32_t, 10> tab);
    void afficher();
    void getTabFilo(uint32_t tab[20][10]);

    std::list<std::array<uint32_t, 10>> getTabLifo();
};

#endif
